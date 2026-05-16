#include "raylib.h"
#include <vector>
#include <iostream>

struct Point {
    int x, y;
    Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
};


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
            case 'O': cellColor = GREEN; break;  
            case 'o': cellColor = LIME; break;  
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
    const int SIZE = 20;
    const int cellSize = 40;
    const int screenWidth = SIZE * cellSize;
    const int screenHeight = SIZE * cellSize;

    std::vector<std::vector<char>> field(SIZE, std::vector<char>(SIZE, '.'));

   
    std::vector<Point> snake;
    int centerX = SIZE / 2;
    int centerY = SIZE / 2;

    snake.push_back(Point(centerX, centerY));    
    snake.push_back(Point(centerX - 1, centerY)); 
    snake.push_back(Point(centerX - 2, centerY)); 

    
    for (int i = 0; i < SIZE; i++) {
        field[0][i] = '#';              
        field[SIZE - 1][i] = '#';       
        field[i][0] = '#';            
        field[i][SIZE - 1] = '#';      
    }

    
    for (size_t i = 0; i < snake.size(); i++) {
        if (i == 0) {
            field[snake[i].y][snake[i].x] = 'O';  
        }
        else {
            field[snake[i].y][snake[i].x] = 'o';  
        }
    }

   
    field[15][15] = '@';  

    
    std::cout << "Консольная версия поля:" << std::endl;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            std::cout << field[i][j] << ' ';
        }
        std::cout << std::endl;
    }

   
    InitWindow(screenWidth, screenHeight, "Snake Game - Raylib");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        drawField(field);  

        DrawText("Press ESC to exit", 10, 10, 20, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}