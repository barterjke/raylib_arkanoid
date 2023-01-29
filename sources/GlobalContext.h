#pragma once
struct GlobalContext {
    bool exited = false;
    struct DataManager {
        const float platform_speed = 650.0f;
        const float ball_speed = 650.0f; // 750
        const float ball_radius = 10.0f;
    } data;

    struct ResourceManager {
        vector<Texture> backgrounds = {};
        Texture platform_texture, wall_texture, logo;
        Sound hit_sound, select_sound;
        Music music;
        unsigned int volume = 5;

        void load() {
            for (auto i = 1; i <= 5; i++) {
                stringstream ss;
                ss << ASSETS_PATH << "sprites/Background_" << i << ".png";
                auto background = LoadTexture(ss.str().c_str());
                scale_texture(background, 4);
                backgrounds.push_back(background);
            }

            logo = LoadTexture(ASSETS_PATH"sprites/Arkanoid-logo.png");
            scale_texture(logo, 0.3);

            platform_texture = LoadTexture(ASSETS_PATH"sprites/Platform.png");
            scale_texture(platform_texture, 3);
            wall_texture = LoadTexture(ASSETS_PATH"sprites/WhiteWall.png");
            scale_texture(wall_texture, 3);

            hit_sound = LoadSound(ASSETS_PATH"sounds/hit.wav");
            select_sound = LoadSound(ASSETS_PATH"sounds/menu_select.wav");
            music = LoadMusicStream(ASSETS_PATH"sounds/Bogart VGM - 8Bit Action- Menu_Select.mp3");
            PlayMusicStream(music);
            SetMusicVolume(music, volume);
            SetSoundVolume(hit_sound, volume);
            SetSoundVolume(select_sound, volume);
        }
    } resources;

    enum WindowType {
        MENU_WINDOW,
        GAME_WINDOW
    } window_type = MENU_WINDOW;
} ctx;