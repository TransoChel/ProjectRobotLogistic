#include "TextureButton.h"

void TextureButton::Draw()
{
    DrawTextureEx(texture, coord, 0, textureSize, WHITE);
}

TextureButton::TextureButton(Vector2 coord, float size, Texture2D texture) : Button(coord, {0, 0}, WHITE, "")
{
    this->textureSize = size;
    this->texture = texture;
}