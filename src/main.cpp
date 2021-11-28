#include "raylib.h"
#include <vector>
#include <random>
#include <algorithm>

constexpr int MOVEMENT_SPEED = 10;
constexpr int PLAYER_WIDTH = 56;
constexpr int PLAYER_HEIGHT = 96;

struct Asteroid {
    Rectangle rec;
    float rotation;
    int rotationSpeed;
    int additionalSpeed; 
};

enum Direction {
    LEFT = -1,
    NONE = 0,
    RIGHT = 1
};

int main(int argc, const char **argv) {

    InitWindow(500, 800, "Flying rocket game");
    SetTargetFPS(60);

    const int width = GetScreenWidth();
    const int height = GetScreenHeight();
    const int centerPos = 250 - PLAYER_WIDTH / 2;

    Texture2D textureAtlas = LoadTexture("res/atlas.png");

    std::random_device r;
    std::default_random_engine rngEngine{r()};
    std::uniform_int_distribution<int> horizontalDist{0, width};
    std::uniform_int_distribution<int> verticalDist{0, height};
    std::uniform_int_distribution<int> asteroidCooldownDist{50, 200};
    std::uniform_int_distribution<int> asteroidRotationDist{-10, 10};
    std::uniform_int_distribution<int> asteroidAdditionalSpeedDist{0, 3};

    Rectangle player{(width - PLAYER_WIDTH) / 2.0f, (height - PLAYER_HEIGHT) / 2.0f, PLAYER_WIDTH, PLAYER_HEIGHT};
    std::vector<Vector2> stars{static_cast<std::vector<Vector2>::size_type>(width * height / 4000)};
    std::vector<Asteroid> asteroids{};

    for (Vector2& star : stars) {
        star.x = horizontalDist(rngEngine);
        star.y = verticalDist(rngEngine);
    }

    bool pause = false;
    bool dead = false;
    Direction movement = NONE;
    int ticks = 0;
    int asteroidCooldown = asteroidCooldownDist(rngEngine);

    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        if (IsKeyPressed(KEY_SPACE)) {
            if (dead) {
                pause = false;
                dead = false;
                movement = NONE;
                ticks = 0;
                asteroidCooldown = asteroidCooldownDist(rngEngine);
                asteroids.clear();
                player.x = (width - PLAYER_WIDTH) / 2.0f;
            } else {
                pause = !pause;
            }
        }

        if (!pause && !dead) {
            ticks++;
            if (IsKeyPressed(KEY_A) && player.x > 100 + MOVEMENT_SPEED) {
                movement = LEFT;
            } else if (IsKeyPressed(KEY_D) && player.x < 350 - MOVEMENT_SPEED) {
                movement = RIGHT;
            }

            float lastX = player.x;
            if (movement == RIGHT) {
                player.x += MOVEMENT_SPEED;
            } else if (movement == LEFT) {
                player.x -= MOVEMENT_SPEED;
            }

            if (player.x <= 100 || (lastX < centerPos && player.x >= centerPos) || (lastX > centerPos && player.x <= centerPos) || player.x >= 350) {
                movement = NONE;
            }

            for (Vector2& star : stars) {
                star.y++;
                if (star.y > height) {
                    star.y = 0;
                    star.x = horizontalDist(rngEngine);
                }
            }

            if (--asteroidCooldown == 0) {
                asteroids.push_back(Asteroid{
                        {static_cast<float>(horizontalDist(rngEngine)), -50, 50, 50},
                        0,
                        asteroidRotationDist(rngEngine),
                        asteroidAdditionalSpeedDist(rngEngine)});
                asteroidCooldown = asteroidCooldownDist(rngEngine);
            }

            for (Asteroid& asteroid : asteroids) {
                asteroid.rec.y += std::min(ticks/200.0, 20.0) + asteroid.additionalSpeed;
                asteroid.rotation += asteroid.rotationSpeed;
                //if (CheckCollisionRecs(asteroid.rec, player)) {
                if (CheckCollisionCircleRec({asteroid.rec.x, asteroid.rec.y}, asteroid.rec.width / 2.0f, player)) {
                    dead = true;
                }
            }
            asteroids.erase(std::remove_if(asteroids.begin(), asteroids.end(), 
                        [height](const Asteroid& asteroid) {return asteroid.rec.y > height;}), asteroids.end());
        }

        DrawTextureQuad(textureAtlas, {14.0f / textureAtlas.width, 24.0f / textureAtlas.height}, {(33.0f + movement * 32.0f) / textureAtlas.width, ticks / 10 % 2 * 24.0f / textureAtlas.height}, player, WHITE);
        DrawText(TextFormat("Score: %i", ticks), 5, 5, 36, RAYWHITE);
        
        for (Vector2 star : stars) {
            DrawPixelV(star, WHITE);
        }

        for (Asteroid asteroid : asteroids) {
            DrawTexturePro(textureAtlas, {0, 49, 16, 16}, asteroid.rec, {asteroid.rec.width / 2, asteroid.rec.height / 2}, asteroid.rotation, WHITE);
        }

        if (dead) {
            DrawText("YOU DIED", (width - MeasureText("YOU DIED", 36)) / 2, height / 2, 36, MAROON);
        } else if (pause) {
            DrawText("PAUSED", (width - MeasureText("PAUSED", 36)) / 2, height / 2, 36, GRAY);
        }

        EndDrawing();
    }
    CloseWindow();

    return 0;
}
