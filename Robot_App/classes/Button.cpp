#include "Button.h"

void Button::Draw()
{
    DrawRectangleV(coord, size, color);
    rl_DrawText(text.c_str(), coord.x + size.x/2 - 50 * text.size()/2, coord.y + size.y/2 - 25, 50, WHITE);
}
bool Button::CheckButtonPressed()
{
    return CheckCollisionPointRec(GetMousePosition(), {coord.x, coord.y, size.x, size.y});
}

Button::Button(Vector2 coord, Vector2 size, Color color, std::string text)
{
    this->coord = coord;
    this->size = size;
    this->color = color;
    this->text = text;
}