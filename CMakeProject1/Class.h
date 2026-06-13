#pragma once

#include "snaceGame.h"

class SnakeGame {
private:
    Direction dir;
    int score;
    bool gameover;
    std::vector<Point> snake;
    Point food;
    double lastMoveTime;
    float moveDelay;

public:
    SnakeGame();
    void init();
    void input();
    void update(double currentTime);
    void draw();
    bool isGameOver() const;
    int getScore() const;
    void drawGameOver();
};

