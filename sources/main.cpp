#include "headers.h"
#include "consts.h"
#include "collision.h"
#include "util.h"
#include "GlobalContext.h"
#include "Game.h"
#include "Menu.h"


int main() {
    glm::vec2(3, 2);
    SetTraceLogLevel(LOG_WARNING);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Arkanoid");
    SetExitKey(-1); // override default behaviour of closing on ESC
    SetTargetFPS(60);
    InitAudioDevice();
    ctx.resources.load();
    game.load();

    while (!WindowShouldClose() && !ctx.exited) {
        UpdateMusicStream(ctx.resources.music);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        switch (ctx.window_type) {
            case ctx.GAME_WINDOW:
                game.update();
                break;
            case ctx.MENU_WINDOW:
                menu.update();
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
