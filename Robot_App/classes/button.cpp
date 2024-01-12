#include <raylib.h>
#include <string>
#pragma once
class Button
{
    public:
        Vector2 coord, size;
        Color color;
        std::string text;

        Button(Vector2 coord, Vector2 size, Color color, std::string text)
        {
            this->coord = coord;
            this->size = size;
            this->color = color;
            this->text = text;
        }

        virtual void DrawButton()
        {
            DrawRectangleV(coord, size, color);
            DrawText(text.c_str(), coord.x + size.x/2 - 50 * text.size()/2, coord.y + size.y/2, 50, WHITE);
        }
        bool CheckButtonPressed()
        {
            return CheckCollisionPointRec(GetMousePosition(), {coord.x, coord.y, size.x, size.y});
        }

};