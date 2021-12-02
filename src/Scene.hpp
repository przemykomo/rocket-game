#pragma once
#include "GameProperties.hpp"
#include <functional>

class Scene {
  private:
    GameProperties &gameProperties;

  protected:
    Scene(GameProperties &gameProperties);

  public:
    virtual void frame() = 0;
    virtual ~Scene() = default;
    void exitScene();
    void openScene(std::function<Scene *(GameProperties &)> constructor);
    void closeGame();
};
