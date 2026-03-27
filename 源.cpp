#include "raylib.h"
#include <vector>
#include <string>

int main() {
    
    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(0, 0, "Master's Giant Picture Snake");

    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();

  
    constexpr float GRID_SIZE = 120.0f;

    
    Texture2D snakeHeadTex = LoadTexture("head.png");
    Texture2D bodyTex = LoadTexture("body.png");      
    Texture2D foodTex = LoadTexture("fruit.png");

    
    float headScale = GRID_SIZE / (float)snakeHeadTex.width;
    float bodyScale = GRID_SIZE / (float)bodyTex.width;
    float foodScale = GRID_SIZE / (float)foodTex.width;

  
    std::vector<Vector2> snake;
    snake.push_back({ (float)screenW / 2, (float)screenH / 2 });
    snake.push_back({ (float)screenW / 2 - GRID_SIZE, (float)screenH / 2 });

    int dir = 0;
    int score = 0;

    float foodX = (float)GetRandomValue(1, (screenW / (int)GRID_SIZE) - 2) * GRID_SIZE;
    float foodY = (float)GetRandomValue(1, (screenH / (int)GRID_SIZE) - 2) * GRID_SIZE;

  
    SetTargetFPS(10);

    
    while (!WindowShouldClose()) {

      
        if (IsKeyPressed(KEY_D) && dir != 1) dir = 0;
        if (IsKeyPressed(KEY_A) && dir != 0) dir = 1;
        if (IsKeyPressed(KEY_S) && dir != 3) dir = 2;
        if (IsKeyPressed(KEY_W) && dir != 2) dir = 3;

      
        Vector2 newHead = snake[0];
        if (dir == 0) newHead.x += GRID_SIZE;
        if (dir == 1) newHead.x -= GRID_SIZE;
        if (dir == 2) newHead.y += GRID_SIZE;
        if (dir == 3) newHead.y -= GRID_SIZE;

        snake.insert(snake.begin(), newHead);

        if (CheckCollisionRecs({ newHead.x, newHead.y, GRID_SIZE, GRID_SIZE }, { foodX, foodY, GRID_SIZE, GRID_SIZE })) {
            score++;
            foodX = (float)GetRandomValue(1, (screenW / (int)GRID_SIZE) - 2) * GRID_SIZE;
            foodY = (float)GetRandomValue(1, (screenH / (int)GRID_SIZE) - 2) * GRID_SIZE;
        }
        else {
            snake.pop_back();
        }

        if (newHead.x < 0 || newHead.x >= screenW || newHead.y < 0 || newHead.y >= screenH) {
            snake.clear();
            snake.push_back({ (float)screenW / 2, (float)screenH / 2 });
            score = 0;
            dir = 0;
        }

  
        BeginDrawing();
        ClearBackground(BLACK);

        for (size_t i = 0; i < snake.size(); i++) {
            if (i == 0) {
             
                DrawTextureEx(snakeHeadTex, snake[i], 0.0f, headScale, WHITE);
            }
            else {
            
                DrawTextureEx(bodyTex, snake[i], 0.0f, bodyScale, WHITE);
            }
        }

     
        DrawTextureEx(foodTex, { foodX, foodY }, 0.0f, foodScale, WHITE);

        std::string scoreText = "Score: " + std::to_string(score);
        DrawText(scoreText.c_str(), 20, 20, 40, RAYWHITE);
        DrawText("Press ESC to exit", screenW - 250, 20, 30, GRAY);

        EndDrawing();
    }

    UnloadTexture(snakeHeadTex);
    UnloadTexture(bodyTex);
    UnloadTexture(foodTex);

    CloseWindow();
    return 0;
}