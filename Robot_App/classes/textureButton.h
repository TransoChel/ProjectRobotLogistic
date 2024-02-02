#include <raylib.h>
#include "button.h"

class TextureButton : public Button
{
private:
    Texture2D texture;
    float textureSize;
public:
    TextureButton(Vector2 coord, float size, Texture2D texture);
    void Draw();
};