#pragma once

class Menu {
    int option = 0;
    vector<string> options;
    vector<string> main_menu_options = {"play", "settings", "exit"};
    vector<string> settings_options = {"volume", "apply and back"};

public:
    Menu() {
        options = main_menu_options;
    }

    void handle_input() {
        if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
            option = (option + 1) % options.size();
            PlaySoundMulti(ctx.resources.select_sound);
        }
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
            option = option == 0 ? options.size() - 1 : option - 1;
            PlaySoundMulti(ctx.resources.select_sound);
        }

        if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D) || IsKeyPressed(KEY_ENTER)) {
            auto option_text = options[option];
            PlaySoundMulti(ctx.resources.select_sound);
            if (option_text == "play") {
                ctx.window_type = ctx.GAME_WINDOW;
                if (game.get_lives() == 0){
                    game.load();
                }
            } else if (option_text == "settings") {
                options = settings_options;
                option = 0;
            } else if (option_text == "volume") {
                ctx.resources.volume = (ctx.resources.volume == 10) ? 0 : ctx.resources.volume + 1;
                SetMusicVolume(ctx.resources.music, ctx.resources.volume / 10.0f);
                SetSoundVolume(ctx.resources.hit_sound, ctx.resources.volume / 10.0f);
                SetSoundVolume(ctx.resources.select_sound, ctx.resources.volume / 10.0f);
            } else if (option_text == "apply and back") {
                options = main_menu_options;
                option = 0;
            } else if (option_text == "exit") {
                ctx.exited = true;
            } else throw std::invalid_argument(option_text);
        }
        if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
            PlaySoundMulti(ctx.resources.select_sound);
            auto option_text = options[option];
            if (option_text == "volume") {
                ctx.resources.volume = (ctx.resources.volume == 0) ? 10 : ctx.resources.volume - 1;
                SetMusicVolume(ctx.resources.music, ctx.resources.volume / 10.0f);
                SetSoundVolume(ctx.resources.hit_sound, ctx.resources.volume / 10.0f);
                SetSoundVolume(ctx.resources.select_sound, ctx.resources.volume / 10.0f);
            }
        }
    }

    void update() {
        handle_input();
        auto logo = ctx.resources.logo;
        DrawTexture(logo, SCREEN_WIDTH / 2 - logo.width / 2, 100, WHITE);

        auto ind = 0;
        const Vector2 text_size = MeasureTextEx(GetFontDefault(), "apply and back", 40, 1);
        for (auto text: options) {
            if (text == "volume") {
                stringstream ss;
                ss << text << " < " << ctx.resources.volume << " > ";
                text = ss.str();
            }
            DrawText(text.c_str(), SCREEN_WIDTH / 2 - text_size.x / 2, SCREEN_HEIGHT / 2 + 100 * ind, 40,
                     option == ind ? RED : BLACK);
            ind++;
        }
    }
} menu;
