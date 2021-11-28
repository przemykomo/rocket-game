#pragma once
#include "raylib.h"
#include <algorithm>
#include <random>
#include <vector>

constexpr int MOVEMENT_SPEED = 10;
constexpr int PLAYER_WIDTH = 56;
constexpr int PLAYER_HEIGHT = 96;

struct Asteroid {
    Rectangle rec;
    float rotation;
    int rotationSpeed;
    int additionalSpeed;
};

enum Direction { LEFT = -1, NONE = 0, RIGHT = 1 };

class GameScene {
  private:
    const int width;
    const int height;
    const int centerPos;

    Texture2D textureAtlas;

    std::random_device r;
    std::default_random_engine rngEngine;
    std::uniform_int_distribution<int> horizontalDist;
    std::uniform_int_distribution<int> verticalDist;
    std::uniform_int_distribution<int> asteroidCooldownDist;
    std::uniform_int_distribution<int> asteroidRotationDist;
    std::uniform_int_distribution<int> asteroidAdditionalSpeedDist;

    Rectangle player;
    std::vector<Vector2> stars;
    std::vector<Asteroid> asteroids;

    bool pause;
    bool dead;
    Direction movement;
    int ticks;
    int asteroidCooldown;

  public:
    GameScene();
    void frame();
};
