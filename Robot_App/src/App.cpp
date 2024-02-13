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
    if (doRequest.CheckButtonPressed() && status == STARTING)
    {
        status = ORDERING;
    }
    else if (status = ORDERING)
    {
        AB.Update();
        ABto.Update();
        if (toMenu.CheckButtonPressed())
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

void App::drawGeneral(float screenWidth, float screenHeight)
{
    DrawRectangleV({0, 100}, {500, 935}, {255, 0, 0, 255});
    DrawRectangleV({0, 0}, {screenWidth, 100}, {200, 0, 0, 255});
    DrawTextureEx(logo, {18, 18}, 0, 2, WHITE);
    DrawTextureEx(queueTexture, {100, 125}, 0, 5, WHITE);
    if (status == STARTING)
    {
        doRequest.Draw();
    }
    else if (status == ORDERING)
    {
        toMenu.Draw();
        DrawText("From", (screenWidth - 500 - 150) / 2 + 500 - 350, 250, 60, RED);//350
        DrawText("To", (screenWidth - 500 - 100) / 2 + 500 + 350, 250, 60, RED);
        DrawTextureEx(fromTo, {(screenWidth - 500 - fromTo.width * 3) / 2 + 500, 100 + 25}, 0, 3, WHITE);
        send.Draw();
        AB.Draw();
        ABto.Draw();
        if (ShouldIDrawArrow) 
        {
            DrawRectangleV({AB.buttons[AB.SendNum()]->coord.x + 350, AB.buttons[AB.SendNum()]->coord.y + 37}, {180, 10}, {200, 0, 0, 255});
            DrawRectangleV({(screenWidth - 500) / 2 - 5 + 500, std::min(AB.buttons[AB.SendNum()]->coord.y + 37, ABto.buttons[ABto.SendNum()]->coord.y + 37) + 10}, {10, std::abs(ABto.buttons[ABto.SendNum()]->coord.y - AB.buttons[AB.SendNum()]->coord.y)}, {200, 0, 0, 255});
            DrawRectangleV({ABto.buttons[ABto.SendNum()]->coord.x - 180, ABto.buttons[ABto.SendNum()]->coord.y + 37}, {180, 10}, {200, 0, 0, 255});
        }
    }
    else if (status == SENT) 
    {
        DrawTextureEx(Sent, {(screenWidth - 500 - Sent.width * 10) / 2 + 500, (screenHeight - 100 - Sent.height * 10) / 2 + 100}, 0, 10, WHITE);
        //DrawText("Order sent!", 1000, 500, 90, RED);
    }
}