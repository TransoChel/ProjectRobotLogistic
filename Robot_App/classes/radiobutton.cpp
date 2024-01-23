#include <raylib.h>
#include <string>
#include "button.cpp"
#pragma once

class RadioButton : public Button {
public:
    Color pressedcol = {std::min(color.r + 20, 255), std::min(color.g + 20, 255), std::min(color.b + 20, 255), 255};
    bool active = false;
    RadioButton(Vector2 coord, Vector2 size, Color color, std::string text) : Button(coord, size, color, text)
    {
    }
    void Draw()
    {
        DrawRectangleV(coord, size, (active? pressedcol : color));
        DrawText(text.c_str(), coord.x + size.x/2 - 50 * text.size()/2, coord.y + size.y/2 - 25, 50, WHITE);
    }
};
