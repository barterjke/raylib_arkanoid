#pragma once

class Game {
    vector<tuple<bool, Color, vec2>> walls;
    vec2 platform_pos;
    vec2 ball_pos;
    vec2 ball_dir;
    bool win;
    float score;
    float best_score = 0;
    int current_background_ind;
    float horizontalMovement;
    int lives;
public:
    int get_lives() const {
        return lives;
    }

    void spawn_ball() {
        auto platform_texture = ctx.resources.platform_texture;
        ball_pos = {platform_pos.x + platform_texture.width / 2, platform_pos.y - platform_texture.height};
        ball_dir = {0, 0};
    }

    void load(bool next_level = false) {
        if (!next_level) {
            win = false;
            lives = 3;
            score = 0;
        }
        platform_pos = vec2(SCREEN_WIDTH / 2 - ctx.resources.platform_texture.width / 2, SCREEN_HEIGHT - 100);
        spawn_ball();
        walls = {};
        current_background_ind = rand() % ctx.resources.backgrounds.size();
        auto wall_texture = ctx.resources.wall_texture;
        for (auto i = 3; i < 15; i++) {
            auto color = random_color();
            // rand() is not the best RNG, but it suits our simple needs
            for (auto j = 10; j < 20; j++) {
                walls.emplace_back(true, color,
                                   vec2(SIDE_OFFSET + i * (wall_texture.width),
                                        TOP_OFFSET + SIDE_OFFSET + j * wall_texture.height));
            }
        }
    }

    void handle_input() {
        horizontalMovement = 0;
        auto scale = ctx.data.platform_speed * GetFrameTime();
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
            horizontalMovement = scale;
            if (platform_pos.x + ctx.resources.platform_texture.width < SCREEN_WIDTH - SIDE_OFFSET) {
                platform_pos.x += scale;
                if (ball_dir == vec2(0, 0)) {
                    ball_pos.x += scale;
                }
                //check if ball is inside then also move it
            }
        }
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
            horizontalMovement = -scale;
            if (platform_pos.x > SIDE_OFFSET) {
                platform_pos.x -= scale;
                if (ball_dir == vec2(0, 0)) {
                    ball_pos.x -= scale;
                }
            }
        }
        if ((IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) && ball_dir == vec2(0, 0)) {
            ball_dir.y = -1;
        }
        if (IsKeyPressed(KEY_ESCAPE)) ctx.window_type = ctx.MENU_WINDOW;
        if (IsKeyPressed(KEY_R)) {
            load();
        }
    }

    void update_collision(vec2 prev_position) {
        if (ball_pos.x < SIDE_OFFSET || ball_pos.x > SCREEN_WIDTH - SIDE_OFFSET) {
            ball_pos.x = ball_pos.x < SIDE_OFFSET ? SIDE_OFFSET + ctx.data.ball_radius : SCREEN_WIDTH - SIDE_OFFSET - ctx.data.ball_radius;
            // push it outside the wall
            ball_dir.x *= -1;
            ball_dir = glm::normalize(ball_dir);
        }
        if (ball_pos.y < TOP_OFFSET + SIDE_OFFSET) {
            ball_dir.y *= -1;
            ball_dir = glm::normalize(ball_dir);
        }
        if (ball_pos.y > SCREEN_HEIGHT + ctx.data.ball_radius) {
            lives--;
            if (lives != 0) {
                spawn_ball();
            }
        }
        auto ball_radius = ctx.data.ball_radius;
        AABB ball_obj{ball_pos - vec2(ball_radius, ball_radius), vec2(ball_radius * 2, ball_radius * 2)};
        bool no_walls = true;
        for (auto &[is_present, _, pos]: walls) {
            if (!is_present) continue;
            no_walls = false;
            AABB wall_obj{pos, vec2(ctx.resources.wall_texture.width, ctx.resources.wall_texture.height)};
            auto [type, intersection] = check_box_line_collision(wall_obj, prev_position, ball_pos);
            if (type == NONE) {
                continue;
            }
            PlaySoundMulti(ctx.resources.hit_sound);
            if (type == VERTICAL) {
                ball_dir.y *= -1;
                ball_dir.x += (rand() % 10 - 5) / 30.0f; // apply random shift on ball dir
                ball_dir = glm::normalize(ball_dir);
            }
            if (type == HORIZONTAL) {
                ball_dir.x *= -1;
                ball_dir.y += (rand() % 10 - 5) / 30.0f;
                ball_dir = glm::normalize(ball_dir);
            }
            score += 1;
            best_score = score > best_score ? score : best_score;
            is_present = false;
            return;
        }
        if (no_walls) {
            win = true;
            load(true);
        }
        AABB platform_obj{platform_pos,
                          vec2(ctx.resources.platform_texture.width, ctx.resources.platform_texture.height)};
        if (check_collision(ball_obj, platform_obj)) {
            PlaySoundMulti(ctx.resources.hit_sound);
            if (horizontalMovement != 0){ // move ball along with platform
                ball_pos.x += horizontalMovement;
            }
            ball_dir.y *= -1;
            if (abs(ball_dir.y) < 0.2) {
                ball_dir.y = 0.5f * glm::sign(ball_dir.y);
            }
            ball_dir.x -=
                    ((platform_obj.position.x + platform_obj.size.x / 2) - ball_pos.x) / (platform_obj.size.x);
            // simulate velocity change
            ball_dir = glm::normalize(ball_dir);
            return;
        }
    }

    void update() {
        handle_input();
        if (lives != 0) {
            auto prev_pos = ball_pos;
            ball_pos += ball_dir * ctx.data.ball_speed * GetFrameTime();
            update_collision(prev_pos);
        }
        draw();
    }

    void draw_info() {
        stringstream ss;
        ss << "SCORE " << score;
        DrawText(ss.str().c_str(), 10, 10, 34, BLACK);
        ss.str("");
        ss << "BEST SCORE " << best_score;
        DrawText(ss.str().c_str(), 300, 10, 34, BLACK);
        ss.str("");
        ss << "LIVES " << lives;
        DrawText(ss.str().c_str(), 730, 10, 34, BLACK);
        const char *tip = R"f(use ARROW KEYS <> or AD to move
press UP or UP to push the ball
press R to restart
press ESC to pause)f";
        const Vector2 text_size = MeasureTextEx(GetFontDefault(), tip, 20, 1);
        DrawText(tip, SCREEN_WIDTH / 2 - text_size.x / 2, SCREEN_HEIGHT / 2 + 100, 20, WHITE);
    }

    void draw() {
        DrawTexture(ctx.resources.backgrounds[current_background_ind], 0, TOP_OFFSET, Color{255, 255, 255, 170});
        DrawCircle(ball_pos.x, ball_pos.y, ctx.data.ball_radius, YELLOW);
        DrawTexture(ctx.resources.platform_texture, platform_pos.x, platform_pos.y, WHITE);
        for (auto &[is_present, color, pos]: walls) {
            if (is_present) DrawTexture(ctx.resources.wall_texture, pos.x, pos.y, color);
        }
        draw_info();
        if (lives == 0) {
            if (win) {
                stringstream ss;
                ss << "GOOD GAME\nYOUR SCORE " << score;
                auto text = ss.str().c_str();
                const Vector2 text_size = MeasureTextEx(GetFontDefault(), text, 50, 1);
                DrawText(text, SCREEN_WIDTH / 2 - text_size.x / 2, SCREEN_HEIGHT / 2 - 200, 50, WHITE);
                return;
            }
            const Vector2 text_size = MeasureTextEx(GetFontDefault(), "GAME OVER", 50, 1);
            DrawText("GAME OVER", SCREEN_WIDTH / 2 - text_size.x / 2, SCREEN_HEIGHT / 2, 50, WHITE);
        }
    }
} game;
