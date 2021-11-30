#pragma once
#include "Scene.hpp"

class MainMenuScene : public Scene {
  public:
    MainMenuScene(bool &pop, Scene *&toPush);
    void frame() override;
};
