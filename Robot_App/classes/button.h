#include <raylib.h>
#include <string>
#pragma once

class Button
{
    public:
        Vector2 coord, size;
        Color color;
        std::string text;

        Button(Vector2 coord, Vector2 size, Color color, std::string text);

        virtual void Draw();
        virtual bool CheckButtonPressed();
};