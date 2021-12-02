#include "GameScene.hpp"
#include "GameProperties.hpp"
#include "Scene.hpp"
#include "raylib.h"
#include <algorithm>
#include <random>
#include <vector>

GameScene::GameScene(GameProperties &gameProperties)
    : Scene(gameProperties), width(GetScreenWidth()), height(GetScreenHeight()),
      centerPos(250 - PLAYER_WIDTH / 2),
      textureAtlas(LoadTexture("res/atlas.png")), r(), rngEngine(r()),
      horizontalDist(0, width), verticalDist(0, height),
      asteroidCooldownDist(50, 200), asteroidRotationDist(-10, 10),
      asteroidAdditionalSpeedDist(0, 3), player{(width - PLAYER_WIDTH) / 2.0f,
                                                (height - PLAYER_HEIGHT) / 2.0f,
                                                PLAYER_WIDTH, PLAYER_HEIGHT},
      stars(
          static_cast<std::vector<Vector2>::size_type>(width * height / 4000)),
      asteroids(), pause(false), dead(false), movement(NONE), ticks(0),
      asteroidCooldown(asteroidCooldownDist(rngEngine)),
      unpauseButton{
          "Unpause",
          {width / 5.0f, height * 1.75f / 3.0f, width * 3 / 5.0f, width / 5.0f},
          [this]() { pause = false; }},
      playAgainButton{
          "Play again",
          {width / 5.0f, height * 1.75f / 3.0f, width * 3 / 5.0f, width / 5.0f},
          [this]() { restartGame(); }},
      exitButton{
          "Exit",
          {width / 5.0f, height * 2.25f / 3.0f, width * 3 / 5.0f, width / 5.0f},
          [this]() { exitScene(); }}
{
    for (Vector2 &star : stars) {
        star.x = horizontalDist(rngEngine);
        star.y = verticalDist(rngEngine);
    }
}

GameScene::~GameScene() { UnloadTexture(textureAtlas); }

void GameScene::restartGame() {
    pause = false;
    dead = false;
    movement = NONE;
    ticks = 0;
    asteroidCooldown = asteroidCooldownDist(rngEngine);
    asteroids.clear();
    player.x = (width - PLAYER_WIDTH) / 2.0f;
}

void GameScene::frame() {
    BeginDrawing();
    ClearBackground(BLACK);

    if (IsKeyPressed(KEY_SPACE)) {
        pause = !pause;
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

        if (player.x <= 100 || (lastX < centerPos && player.x >= centerPos) ||
            (lastX > centerPos && player.x <= centerPos) || player.x >= 350) {
            movement = NONE;
        }

        for (Vector2 &star : stars) {
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

        for (Asteroid &asteroid : asteroids) {
            asteroid.rec.y +=
                std::min(ticks / 200.0, 20.0) + asteroid.additionalSpeed;
            asteroid.rotation += asteroid.rotationSpeed;

            if (CheckCollisionCircleRec({asteroid.rec.x, asteroid.rec.y}, 20.0f,
                                        player)) {
                dead = true;
            }
        }
        asteroids.erase(std::remove_if(asteroids.begin(), asteroids.end(),
                                       [this](const Asteroid &asteroid) {
                                           return asteroid.rec.y > this->height;
                                       }),
                        asteroids.end());
    }

    DrawTextureQuad(textureAtlas,
                    {14.0f / textureAtlas.width, 24.0f / textureAtlas.height},
                    {(33.0f + movement * 32.0f) / textureAtlas.width,
                     ticks / 10 % 2 * 24.0f / textureAtlas.height},
                    player, WHITE);
    DrawText(TextFormat("Score: %i", ticks), 5, 5, 36, RAYWHITE);

    for (Vector2 star : stars) {
        DrawPixelV(star, WHITE);
    }

    for (Asteroid asteroid : asteroids) {
        DrawTexturePro(textureAtlas, {0, 49, 16, 16}, asteroid.rec,
                       {asteroid.rec.width / 2, asteroid.rec.height / 2},
                       asteroid.rotation, WHITE);
    }

    if (dead) {
        DrawText("YOU DIED", (width - MeasureText("YOU DIED", 36)) / 2,
                 height / 4, 36, MAROON);
        playAgainButton.frame();
        exitButton.frame();
    } else if (pause) {
        DrawText("PAUSED", (width - MeasureText("PAUSED", 36)) / 2,
                 height / 4, 36, WHITE);
        unpauseButton.frame();
        exitButton.frame();
    }

    EndDrawing();
}
