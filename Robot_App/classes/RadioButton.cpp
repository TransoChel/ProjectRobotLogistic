#include "Radiobutton.h"
#pragma once

void RadioButton::Draw()
{
    DrawRectangleV(coord, size, (active ? pressedcol : color));
    DrawText(text.c_str(), coord.x + size.x / 2 - 50 * text.size() / 2, coord.y + size.y / 2 - 25, 50, WHITE);
}

RadioButton::RadioButton(Vector2 coord, Vector2 size, Color color, std::string text) : Button(coord, size, color, text)
{
}
