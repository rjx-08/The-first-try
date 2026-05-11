#include "raylib.h"
#include <vector>
#include <iostream>

// Функция отрисовки поля
void drawField(const std::vector<std::vector<char>>& field) {
    const int SIZE = 20;
    const int cellSize = 40;
    const int screenWidth = SIZE * cellSize;
    const int screenHeight = SIZE * cellSize;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            Color cellColor;
            switch (field[i][j]) {
            case '.': cellColor = DARKGRAY; break;
            case '#': cellColor = BROWN; break;
            case '@': cellColor = GREEN; break;
            case 'O': cellColor = RED; break;
            default: cellColor = WHITE;
            }

            DrawRectangle(j * cellSize, i * cellSize, cellSize - 1, cellSize - 1, cellColor);
        }
    }

    for (int i = 0; i <= SIZE; i++) {
        DrawLine(i * cellSize, 0, i * cellSize, screenHeight, WHITE);
        DrawLine(0, i * cellSize, screenWidth, i * cellSize, WHITE);
    }
}

int main() {
    // ====== ИСХОДНЫЙ КОД (ваш) ======
    const int SIZE = 20;
    std::vector<std::vector<char>> field(SIZE, std::vector<char>(SIZE, '.'));

    // Добавим несколько объектов для демонстрации
    field[5][5] = '#';    // Стена
    field[10][10] = '@';  // Змейка
    field[15][15] = 'O';  // Яблоко

    // Классические циклы for (ваши)
    std::cout << "Консольная версия поля:" << std::endl;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            std::cout << field[i][j] << ' ';
        }
        std::cout << std::endl;
    }

    // ====== ОТРИСОВКА RAYLIB ======
    const int cellSize = 40;
    const int screenWidth = SIZE * cellSize;
    const int screenHeight = SIZE * cellSize;

    InitWindow(screenWidth, screenHeight, "Field 20x20 - Raylib");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        drawField(field);  // Вызываем нашу функцию отрисовки

        DrawText("Press ESC to exit", 10, 10, 20, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}