#pragma once
#include "Button.hpp"
#include "GameProperties.hpp"
#include "Scene.hpp"
#include <vector>

class MainMenuScene : public Scene {
  private:
    std::vector<Button> buttons;

  public:
    MainMenuScene(GameProperties &gameProperties);
    void frame() override;
};
