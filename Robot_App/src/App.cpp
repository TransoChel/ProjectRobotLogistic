#include "App.h"
App::App(Graf* graf)
{
    AB.buttons.push_back(&A);
    AB.buttons.push_back(&B);
    AB.buttons.push_back(&C);
    AB.buttons.push_back(&D);
    AB.buttons.push_back(&E);
    ABto.buttons.push_back(&Ato);
    ABto.buttons.push_back(&Bto);
    ABto.buttons.push_back(&Cto);
    ABto.buttons.push_back(&Dto);
    ABto.buttons.push_back(&Eto);
    this->graf = graf;

}
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
            ShouldIDrawArrow = false;
            AB.NullUpdate();
            ABto.NullUpdate();
        }
        if (AB.CheckUpdate() && ABto.CheckUpdate()) 
        {
            if (CheckCollisionPointRec(GetMousePosition(), {1425, 900, 100, 100})) 
            {
                from = AB.SendNum();
                to = ABto.SendNum();
                status = SENT;
                ShouldIDrawArrow = false;
                queue.addRequest({from, to, graf});
                AB.NullUpdate();
                ABto.NullUpdate();
            }
        }
    }
}

void App::drawGeneral(float screenWidth)
{
    DrawRectangleV({0, 100}, {500, 935}, {255, 0, 0, 255});
    DrawRectangleV({0, 0}, {screenWidth, 100}, {200, 0, 0, 255});
    DrawTextureEx(logo, {18, 18}, 0, 2, WHITE);
    DrawTextureEx(queueTexture, {100, 125}, 0, 5, WHITE);
    if (status == STARTING)
    {
        doRequest.Draw();
        DrawTextureEx(doRequest.texture, {960, 450}, 0, 5, WHITE);
    }
    else if (status == ORDERING)
    {
        DrawTextureEx(toMenu, {1550, 900}, 0, 3, WHITE);
        DrawText("From", 775, 250, 60, RED);
        DrawText("To", 1450, 250, 60, RED);
        //DrawTextureEx(fromTo, {920, 125}, 0, 3, WHITE);
        DrawTextureEx(fromTo, {975, 125}, 0, 3, WHITE);
        DrawTextureEx(send, {1425, 900}, 0, 3, WHITE);
        AB.Draw();
        ABto.Draw();
        if (ShouldIDrawArrow) 
        {
            DrawRectangleV({AB.buttons[AB.SendNum()]->coord.x + 350, AB.buttons[AB.SendNum()]->coord.y + 37}, {155, 10}, {200, 0, 0, 255});
            DrawRectangleV({1170, std::min(AB.buttons[AB.SendNum()]->coord.y + 37, ABto.buttons[ABto.SendNum()]->coord.y + 37) + 10}, {10, std::abs(ABto.buttons[ABto.SendNum()]->coord.y - AB.buttons[AB.SendNum()]->coord.y)}, {200, 0, 0, 255});
            DrawRectangleV({ABto.buttons[ABto.SendNum()]->coord.x - 155, ABto.buttons[ABto.SendNum()]->coord.y + 37}, {155, 10}, {200, 0, 0, 255});
        }
    }
    else if (status == SENT) 
    {
        DrawText("Order sent!", 1000, 500, 90, RED);
    }
}