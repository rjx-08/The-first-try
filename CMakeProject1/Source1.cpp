#include "raylib.h"
#include <vector>
#include <iostream>

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    STOP
};

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
            case 'F': cellColor = RED; break;      
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

   
    Direction dir = STOP;

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
        if (i == 0) field[snake[i].y][snake[i].x] = 'O';
        else field[snake[i].y][snake[i].x] = 'o';

    }

    
    field[15][15] = 'F';

   
    std::cout << "Консольная версия поля:" << std::endl;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            std::cout << field[i][j] << ' ';
        }
        std::cout << std::endl;
    }
 
    InitWindow(screenWidth, screenHeight, "Snake Game - Raylib");
    SetTargetFPS(60);
    double LastMoveTime = GetTime();
    float moveDelay = 0.15f;

    while (!WindowShouldClose()) {

        if ((IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) && dir != DOWN) dir = UP;
        if ((IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) && dir != UP) dir = DOWN;
        if ((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) && dir != RIGHT) dir = LEFT;
        if ((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) && dir != LEFT) dir = RIGHT;

        double currentTime = GetTime();
        if (currentTime - LastMoveTime >= moveDelay) {
            if (dir != STOP) {
                Point NewHead = snake[0];
                switch (dir) {
                case UP:    NewHead.y--; break;
                case DOWN:  NewHead.y++; break;
                case LEFT:  NewHead.x--; break;
                case RIGHT: NewHead.x++; break;
                default: break;
                }
                snake.insert(snake.begin(), NewHead);
                snake.pop_back();
            }
            for (int i = 1; i < SIZE - 1; i++) {
                for (int j = 1; j < SIZE - 1; j++) {
                    field[i][j] = '.';
                }

                for (size_t i = 0; i < snake.size(); i++) {
                    char symbol = (i == 0) ? 'O' : 'o';
                    field[snake[i].y][snake[i].x] = symbol;
                }

                field[15][15] = 'F';
                LastMoveTime = currentTime;
            }
        }


        if (IsKeyPressed(KEY_X)) {
            CloseWindow();
        }


        BeginDrawing();
        ClearBackground(BLACK);

        drawField(field);


        const char* dirText;
        switch (dir) {
        case UP:    dirText = "UP"; break;
        case DOWN:  dirText = "DOWN"; break;
        case LEFT:  dirText = "LEFT"; break;
        case RIGHT: dirText = "RIGHT"; break;
        case STOP:  dirText = "STOP"; break;
        default:    dirText = "???";
        }
        DrawText(TextFormat("Direction: %s", dirText), 10, 40, 20, YELLOW);
        DrawText("Press ESC to exit", 10, 10, 20, WHITE);

        EndDrawing();

    }
    CloseWindow();
    return 0;
}