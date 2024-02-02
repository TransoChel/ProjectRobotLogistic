#include "app.h"
void App::LeftMouseButtonPressed()
{
    if (CheckCollisionPointRec(GetMousePosition(), {960, 450, 128 * 5, 32 * 5}) && status == STARTING)
    {
        status = ORDERING;
    }
    else if (status = ORDERING)
    {
        AB.Update();
        ABto.Update();
        if (CheckCollisionPointRec(GetMousePosition(), {1550, 900, (float)toMenu.width * 3, (float)toMenu.height * 3}))
        {
            status = STARTING;
            AB.NullUpdate();
            ABto.NullUpdate();
        }
        if (AB.CheckUpdate() && ABto.CheckUpdate()) {
            if (CheckCollisionPointRec(GetMousePosition(), {1425, 900, 100, 100})) {
                from = AB.SendNum();
                to = AB.SendNum();
                status = SENT;
                AB.NullUpdate();
                ABto.NullUpdate();
            }
        }
    }
}

void App::drawGeneral(int screenWidth)
{
    DrawRectangleV({0, 100}, {500, 935}, {255, 0, 0, 255});
    DrawRectangleV({0, 0}, {screenWidth, 100}, {200, 0, 0, 255});
    DrawTextureEx(logo, {18, 18}, 0, 2, WHITE);
    DrawTextureEx(queueTexture, {100, 125}, 0, 5, WHITE);
}