#include <raylib.h>
#include <string>
#include "button.cpp"
#pragma once

class RadioButton : public Button {
public:
    Color pressedcol = {255, 130, 130, 255};
    bool active = false;
    RadioButton(Vector2 coord, Vector2 size, Color color, std::string text) : Button(coord, size, color, text)
    {
    }
    void DrawButton()
    {
        if (active) {
            DrawRectangleV(coord, size, pressedcol);
        }
        else {
            DrawRectangleV(coord, size, color);
        }
        DrawText(text.c_str(), coord.x + size.x / 2 - 50 * text.size() / 2, coord.y + size.y / 2, 50, WHITE);
    }
};
