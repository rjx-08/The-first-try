#include "raylib.h"
#include <vector>
#include <iostream>

// Структура Point
struct Point {
    int x, y;
    Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
};

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
            case 'O': cellColor = GREEN; break;  // Голова
            case 'o': cellColor = LIME; break;   // Тело
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
    // ====== ИНИЦИАЛИЗАЦИЯ ======
    const int SIZE = 20;
    const int cellSize = 40;
    const int screenWidth = SIZE * cellSize;
    const int screenHeight = SIZE * cellSize;

    std::vector<std::vector<char>> field(SIZE, std::vector<char>(SIZE, '.'));

    // Создаем змейку из 3 точек по центру
    std::vector<Point> snake;
    int centerX = SIZE / 2;
    int centerY = SIZE / 2;

    snake.push_back(Point(centerX, centerY));     // Голова
    snake.push_back(Point(centerX - 1, centerY)); // Тело
    snake.push_back(Point(centerX - 2, centerY)); // Тело

    // Рисуем границы (#)
    for (int i = 0; i < SIZE; i++) {
        field[0][i] = '#';              // Верхняя граница
        field[SIZE - 1][i] = '#';       // Нижняя граница
        field[i][0] = '#';              // Левая граница
        field[i][SIZE - 1] = '#';       // Правая граница
    }

    // Размещаем змейку на поле
    for (size_t i = 0; i < snake.size(); i++) {
        if (i == 0) {
            field[snake[i].y][snake[i].x] = 'O';  // Голова
        }
        else {
            field[snake[i].y][snake[i].x] = 'o';  // Тело
        }
    }

    // Добавим яблоко для демонстрации
    field[15][15] = '@';  // Яблоко

    // Вывод в консоль
    std::cout << "Консольная версия поля:" << std::endl;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            std::cout << field[i][j] << ' ';
        }
        std::cout << std::endl;
    }

    // ====== ОТРИСОВКА RAYLIB ======
    InitWindow(screenWidth, screenHeight, "Snake Game - Raylib");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        drawField(field);  // Вызываем функцию отрисовки

        DrawText("Press ESC to exit", 10, 10, 20, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}