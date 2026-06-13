#include "asdasd.h"
#include <cmath>

Game::Game()
    : deltaTime(0.0f)
    , gameRunning(true)
{
    playerPosition = { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
    playerVelocity = { 0.0f, 0.0f };
}

Game::~Game() {
    Cleanup();
}

void Game::Init() {
    // Инициализация окна
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "My Raylib Game");
    SetTargetFPS(60); // Установка FPS
    InitAudioDevice(); // Для звука (если понадобится)
}

void Game::HandleInput() {
    // Обнуляем скорость
    playerVelocity = { 0.0f, 0.0f };

    // Обработка клавиш WASD или стрелок
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        playerVelocity.x = 1.0f;
    }
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        playerVelocity.x = -1.0f;
    }
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
        playerVelocity.y = 1.0f;
    }
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
        playerVelocity.y = -1.0f;
    }

    // Нормализуем диагональное движение
    if (playerVelocity.x != 0.0f && playerVelocity.y != 0.0f) {
        playerVelocity.x *= 0.7071f; // 1 / sqrt(2)
        playerVelocity.y *= 0.7071f;
    }

    // Выход по ESC
    if (IsKeyPressed(KEY_ESCAPE)) {
        gameRunning = false;
    }
}

void Game::UpdatePlayer() {
    // Обновляем позицию игрока
    playerPosition.x += playerVelocity.x * PLAYER_SPEED * deltaTime;
    playerPosition.y += playerVelocity.y * PLAYER_SPEED * deltaTime;

    // Ограничения по границам экрана
    if (playerPosition.x < 0) playerPosition.x = 0;
    if (playerPosition.x > SCREEN_WIDTH - PLAYER_SIZE)
        playerPosition.x = SCREEN_WIDTH - PLAYER_SIZE;
    if (playerPosition.y < 0) playerPosition.y = 0;
    if (playerPosition.y > SCREEN_HEIGHT - PLAYER_SIZE)
        playerPosition.y = SCREEN_HEIGHT - PLAYER_SIZE;
}

void Game::Update() {
    deltaTime = GetFrameTime();

    HandleInput();
    UpdatePlayer();
}

void Game::Draw() {
    BeginDrawing();

    ClearBackground(BACKGROUND_COLOR);

    // Рисуем игрока
    DrawRectangleV(playerPosition, { PLAYER_SIZE, PLAYER_SIZE }, PLAYER_COLOR);

    // Рисуем границы экрана
    DrawRectangleLines(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, DARKGRAY);

    // Выводим информацию на экран
    DrawText("Use WASD or Arrow Keys to move", 10, 10, 20, DARKGRAY);
    DrawText("Press ESC to exit", 10, 35, 20, DARKGRAY);

    // Выводим FPS
    DrawFPS(SCREEN_WIDTH - 100, 10);

    EndDrawing();
}

void Game::Run() {
    while (!WindowShouldClose() && gameRunning) {
        Update();
        Draw();
    }
}

bool Game::ShouldClose() const {
    return WindowShouldClose() || !gameRunning;
}

void Game::Cleanup() {
    CloseAudioDevice();
    CloseWindow();
}

// Точка входа
int main() {
    Game game;
    game.Init();
    game.Run();
    return 0;
}