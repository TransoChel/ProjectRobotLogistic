#include "TextureButton.h"

void TextureButton::Draw()
{
    rl_DrawTextureEx(texture, coord, 0, textureSize, WHITE);
}

TextureButton::TextureButton(Vector2 coord, float size, Texture2D texture) : Button(coord, {0, 0}, WHITE, "")
{
    this->textureSize = size;
    this->texture = texture;
}

bool TextureButton::CheckButtonPressed()
{
    return CheckCollisionPointRec(GetMousePosition(), {coord.x, coord.y, texture.width * textureSize, texture.height * textureSize});
}