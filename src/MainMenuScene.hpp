#pragma once
#include "Scene.hpp"
#include "raylib.h"
#include <string>
#include <vector>

struct Button {
    std::string text;
    Rectangle rec;
    std::function<void(void)> onClick;
    void frame();
};

class MainMenuScene : public Scene {
  private:
    std::vector<Button> buttons;

  public:
    MainMenuScene(bool &pop, Scene *&toPush);
    void frame() override;
};
