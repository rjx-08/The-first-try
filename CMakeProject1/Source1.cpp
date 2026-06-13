#include "Class.h"
#include <cstdlib>
#include <ctime>

int main() {
    srand((unsigned int)time(NULL));  // Наш рандомайзер

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake Game");
    SetTargetFPS(60);

    SnakeGame game;

    while (!WindowShouldClose() && !game.isGameOver()) {
        game.input();

        double currentTime = GetTime();
        game.update(currentTime);

        BeginDrawing();
        ClearBackground(BLACK);
        game.draw();
        EndDrawing();
    }

    game.drawGameOver();
    CloseWindow();
    return 0;
}