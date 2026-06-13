#include "Class.h"
#include <cstdlib>
#include <ctime>
#include <iostream>


SnakeGame::SnakeGame() {
    init();
}


void SnakeGame::init() {
    dir = STOP;
    score = 0;
    gameover = false;
    moveDelay = 0.15f;
    lastMoveTime = GetTime();

    snake.clear();
    int centerX = SIZE / 2;
    int centerY = SIZE / 2;

    snake.push_back(Point(centerX, centerY));      // Голова
    snake.push_back(Point(centerX - 1, centerY));  // Туловище
    snake.push_back(Point(centerX - 2, centerY));  // Хвост

    food = { 15, 15 };
}


void SnakeGame::input() {
    if ((IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) && dir != DOWN) dir = UP;
    if ((IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) && dir != UP) dir = DOWN;
    if ((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) && dir != RIGHT) dir = LEFT;
    if ((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) && dir != LEFT) dir = RIGHT;

    if (IsKeyPressed(KEY_X)) {
        gameover = true;
    }
}


void SnakeGame::update(double currentTime) {
    if (currentTime - lastMoveTime >= moveDelay) {
        if (dir != STOP) {
            Point NewHead = snake[0];
            switch (dir) {
            case UP:    NewHead.y--; break;
            case DOWN:  NewHead.y++; break;
            case LEFT:  NewHead.x--; break;
            case RIGHT: NewHead.x++; break;
            default: break;
            }


            if (NewHead.x <= 0 || NewHead.x >= SIZE - 1 ||
                NewHead.y <= 0 || NewHead.y >= SIZE - 1) {
                gameover = true;
            }

            bool atefood = (NewHead.x == food.x && NewHead.y == food.y);
            snake.insert(snake.begin(), NewHead);
            if (!atefood) {
                snake.pop_back();
            }
            else {
                score += 10;
                food = generateRandomFood(snake, SIZE);
            }

        
            for (size_t i = 1; i < snake.size(); i++) {
                if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
                    gameover = true;
                    break;
                }
            }

            lastMoveTime = currentTime;
        }
    }
}


void SnakeGame::draw() {
    std::vector<std::vector<char>> field(SIZE, std::vector<char>(SIZE, '.'));

    // Стены
    for (int i = 0; i < SIZE; i++) {
        field[0][i] = '#';              // Верхняя строка
        field[SIZE - 1][i] = '#';       // Нижняя строка
        field[i][0] = '#';              // Левый столбец
        field[i][SIZE - 1] = '#';       // Правый столбец
    }

    // Змея
    for (size_t i = 0; i < snake.size(); i++) {
        if (i == 0) field[snake[i].y][snake[i].x] = 'O';
        else field[snake[i].y][snake[i].x] = 'o';
    }

    // Еда
    field[food.y][food.x] = 'F';

    drawField(field);

    // Интерфейс
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
    DrawText(TextFormat("Score: %i", score), 10, 70, 20, GREEN);
}


bool SnakeGame::isGameOver() const {
    return gameover;
}

int SnakeGame::getScore() const {
    return score;
}

void SnakeGame::drawGameOver() {
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("GAME OVER", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 40, 40, RED);
        DrawText(TextFormat("Final Score: %i", score), SCREEN_WIDTH / 2 - 80, SCREEN_HEIGHT / 2, 30, WHITE);
        DrawText("Press ESC to exit", SCREEN_WIDTH / 2 - 80, SCREEN_HEIGHT / 2 + 50, 20, GRAY);

        EndDrawing();

        if (IsKeyPressed(KEY_ESCAPE)) {
            break;
        }
    }
}