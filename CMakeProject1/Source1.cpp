#include "raylib.h"
#include <vector>
#include <iostream>
#include <cstdlib>   // для rand() и srand()
#include <ctime>     

const int SIZE = 20;
const int CELL_SIZE = 40;
const int SCREEN_WIDTH = SIZE * CELL_SIZE;
const int SCREEN_HEIGHT = SIZE * CELL_SIZE;

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    STOP // Начальное положение
};

struct Point {
    int x, y;
    Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
};

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
            default: cellColor = WHITE;// На всякий случай
            }
            DrawRectangle(j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE - 1, CELL_SIZE - 1, cellColor);
        }
    }

    for (int i = 0; i <= SIZE; i++) {
        DrawLine(i * CELL_SIZE, 0, i * CELL_SIZE, SCREEN_WIDTH, WHITE);//Вертикаль
        DrawLine(0, i * CELL_SIZE, SCREEN_WIDTH, i * CELL_SIZE, WHITE);//Горизонталь
    }
}

int main() {

    Direction dir = STOP;

    int score = 0;
    bool gameover = false;

    std::vector<std::vector<char>> field(SIZE, std::vector<char>(SIZE, '.'));//Двумерный вектор символов.Внешний вектор имеет размер SIZE(20 строк).Каждая строка - это вектор char, размера SIZE, заполненный символом '.' (пустая клетка).
    std::vector<Point> snake;//Хранение сегментов
    int centerX = SIZE / 2;
    int centerY = SIZE / 2;

    snake.push_back(Point(centerX, centerY));//Голова
    snake.push_back(Point(centerX - 1, centerY));//Туловище
    snake.push_back(Point(centerX - 2, centerY));//Хвост

    Point food = { 15, 15 };
    srand((unsigned int)time(NULL));//Наш рандомайзер


    for (int i = 0; i < SIZE; i++) {
        field[0][i] = '#';//Верхняя строка
        field[SIZE - 1][i] = '#';//Нижняя строка
        field[i][0] = '#';//Левый столбец
        field[i][SIZE - 1] = '#';//Правый столбец
    }//Все это стены(Все полу окуружено решеткой)


    for (size_t i = 0; i < snake.size(); i++) {
        if (i == 0) field[snake[i].y][snake[i].x] = 'O';
        else field[snake[i].y][snake[i].x] = 'o';

    }//Размещение змейка на поле

    field[food.y][food.x] = 'F';


    std::cout << "Консольная версия поля:" << std::endl;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            std::cout << field[i][j] << ' ';
        }
        std::cout << std::endl;
    }//Проверка прaвильности размещения(Необязательно)

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake Game");
    SetTargetFPS(60);
    double LastMoveTime = GetTime();
    float moveDelay = 0.15f;



    while (!WindowShouldClose() && !gameover) {

        if ((IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) && dir != DOWN) dir = UP;
        if ((IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) && dir != UP) dir = DOWN;
        if ((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) && dir != RIGHT) dir = LEFT;
        if ((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) && dir != LEFT) dir = RIGHT;

        double currentTime = GetTime();

        if (currentTime - LastMoveTime >= moveDelay) {//Проверяет прошло ли достаточно времени с последнего движения
            if (dir != STOP) {//Двигаем змейку только после начала игры(dir НЕ STOP)
                Point NewHead = snake[0];//Rопия головы змейки (первый элемент вектора)
                switch (dir) {
                case UP:    NewHead.y--; break;
                case DOWN:  NewHead.y++; break;
                case LEFT:  NewHead.x--; break;
                case RIGHT: NewHead.x++; break;
                default: break;
                }//В зависемости от направления изменяем координаты Newhead(Строка/Столбец то увеличивается на 1, то уменьшается)
                // Проверка столкновения со стенами
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
                    }//проверка начинается с первого куска тела, не учитывая голову 

                }
                for (int i = 1; i < SIZE - 1; i++) {
                    for (int j = 1; j < SIZE - 1; j++) {
                        field[i][j] = '.';
                    }
                }

                for (size_t i = 0; i < snake.size(); i++) {
                    char symbol = (i == 0) ? 'O' : 'o';
                    field[snake[i].y][snake[i].x] = symbol;
                }

                field[food.y][food.x] = 'F';

                LastMoveTime = currentTime;
            }


            if (IsKeyPressed(KEY_X)) {
                gameover = true;
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
            }
            DrawText(TextFormat("Direction: %s", dirText), 10, 40, 20, YELLOW);
            DrawText("Press ESC to exit", 10, 10, 20, WHITE);
            DrawText(TextFormat("Score: %i", score), 10, 70, 20, GREEN);

            EndDrawing();
        }
    }
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

    CloseWindow();
    return 0;
}