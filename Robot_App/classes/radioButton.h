#include <raylib.h>
#include <string>
#include "button.h"
#pragma once

class RadioButton : public Button {
public:
    Color pressedcol = {std::min(color.r + 20, 255), std::min(color.g + 20, 255), std::min(color.b + 20, 255), 255};
    bool active = false;
    RadioButton(Vector2 coord, Vector2 size, Color color, std::string text);
    void Draw();
};
