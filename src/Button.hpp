#pragma once

#include "raylib.h"
#include <functional>
#include <string>

struct Button {
    std::string text;
    Rectangle rec;
    std::function<void(void)> onClick;
    Color color = DARKBLUE;
    Color focusColor = BLUE;
    void frame();
};
