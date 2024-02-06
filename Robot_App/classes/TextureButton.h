#include <raylib.h>
#include "Button.h"

class TextureButton : public Button
{
private:
    float textureSize;
public:
    Texture2D texture;
    TextureButton(Vector2 coord, float size, Texture2D texture);
    void Draw();
};