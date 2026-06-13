#pragma once

#include "raylib.h"

// Константы игры
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int PLAYER_SIZE = 50;
const float PLAYER_SPEED = 500.0f; // пикселей в секунду

// Цвета
const Color PLAYER_COLOR = BLUE;
const Color BACKGROUND_COLOR = RAYWHITE;

class Game {
private:
    Vector2 playerPosition;
    Vector2 playerVelocity;
    float deltaTime;
    bool gameRunning;

public:
    Game();
    ~Game();

    void Init();
    void Update();
    void Draw();
    void Run();
    bool ShouldClose() const;
    void Cleanup();

private:
    void HandleInput();
    void UpdatePlayer();
};
