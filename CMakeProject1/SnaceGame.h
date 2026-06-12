#pragma once
#define UTILS_H

#include <vector>
#include "raylib.h"

const int SIZE = 20;
const int CELL_SIZE = 40;
const int SCREEN_WIDTH = SIZE * CELL_SIZE;
const int SCREEN_HEIGHT = SIZE * CELL_SIZE;

struct Point {
    int x, y;
    Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
};

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    STOP // Начальное положение
};

void drawField(const std::vector<std::vector<char>>& field);
Point generateRandomFood(const std::vector<Point>& snake, int SIZE);

