#include "SnaceGame.h"
#include <cstdlib>


void drawField(const std::vector<std::vector<char>>& field) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            Color cellColor;
            switch (field[i][j]) {
            case '.': cellColor = DARKGRAY; break;
            case '#': cellColor = BROWN; break;
            case 'O': cellColor = GREEN; break;
            case 'o': cellColor = LIME; break;
            case 'F': cellColor = RED; break;
            default: cellColor = WHITE;
            }
            DrawRectangle(j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE - 1, CELL_SIZE - 1, cellColor);
        }
    }

    for (int i = 0; i <= SIZE; i++) {
        DrawLine(i * CELL_SIZE, 0, i * CELL_SIZE, SCREEN_WIDTH, WHITE);
        DrawLine(0, i * CELL_SIZE, SCREEN_WIDTH, i * CELL_SIZE, WHITE);
    }
}

Point generateRandomFood(const std::vector<Point>& snake, int SIZE) {
    Point newFood;
    bool onSnake;

    do {
        onSnake = false;
        newFood.x = rand() % (SIZE - 2) + 1;
        newFood.y = rand() % (SIZE - 2) + 1;

        for (const auto& segment : snake) {
            if (segment.x == newFood.x && segment.y == newFood.y) {
                onSnake = true;
                break;
            }
        }
    } while (onSnake);

    return newFood;
}