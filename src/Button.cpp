#include "Button.hpp"

void Button::frame() {
    if (CheckCollisionPointRec(GetMousePosition(), rec)) {
        DrawRectangle(rec.x, rec.y + 1, rec.width, rec.height, focusColor);
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            onClick();
        }
    } else {
        DrawRectangle(rec.x, rec.y + 1, rec.width, rec.height, color);
    }

    DrawRectangleLinesEx(rec, 10, WHITE);
    DrawText(text.c_str(),
             rec.x + (rec.width - MeasureText(text.c_str(), 36)) / 2,
             rec.y + (rec.height / 2) - 18, 36, WHITE);
}
