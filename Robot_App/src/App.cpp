#include "App.h"




App::App(Graf* graf, ceSerial* com, Robot* robot, float screenWidth, float screenHeight)
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
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

    transparensy = 255;
    sentSpeed = 0, sentScale = 10, sentTimer = 60;
    sentPos = {(screenWidth - 500 - Sent.width * 10) / 2 + 500, (screenHeight - 100 - Sent.height * 10) / 2 + 100};
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
            InvalidRequest = false;
            AB.NullUpdate();
            ABto.NullUpdate();
        }
        if (AB.CheckUpdate() && ABto.CheckUpdate()) 
        {
            if (CheckCollisionPointRec(GetMousePosition(), {1425, 900, 100, 100})) 
            {
                if (AB.SendNum() == ABto.SendNum()) {
                    InvalidRequest = true;
                }
                else {
                    from = AB.SendNum();
                    to = ABto.SendNum();
                    status = SENT;
                    startTimeSent = GetTime();
                    ShouldIDrawArrow = false;
                    InvalidRequest = false;
                    queue.addRequest({from, to, graf});
                    AB.NullUpdate();
                    ABto.NullUpdate();
                }
            }
        }
    }
}

void App::drawGeneral()
{
    
    DrawRectangleV({0, 100}, {500, 935}, {255, 0, 0, 255});
    DrawRectangleV({0, 0}, {screenWidth, 100}, {200, 0, 0, 255});
    rl_DrawTextureEx(logo, {18, 18}, 0, 2, WHITE);
    rl_DrawTextureEx(queueTexture, {100, 125}, 0, 5, WHITE);
    if (status == STARTING)
    {
        doRequest.Draw();
    }
    else if (status == ORDERING)
    {
        toMenu.Draw();
        rl_DrawTextureEx(fromTexture, {screenWidth - 710 - 180 - 175 - (52 * 5 / 2), 250}, 0, 5, WHITE);
        rl_DrawTextureEx(toTexture, {radioButtonToX + 175 - (34 * 5 / 2), 250}, 0, 5, WHITE);
        //DrawLine(0, 949, 1500, 949, BLACK);
        send.Draw();
        AB.Draw();
        ABto.Draw();
        if (ShouldIDrawArrow)
        {
            DrawRectangleV({AB.buttons[AB.SendNum()]->coord.x + 350, AB.buttons[AB.SendNum()]->coord.y + 37}, {180, 10}, {200, 0, 0, 255});
            DrawRectangleV({(screenWidth - 500) / 2 - 5 + 500, std::min(AB.buttons[AB.SendNum()]->coord.y + 37, ABto.buttons[ABto.SendNum()]->coord.y + 37) + 10}, {10, std::abs(ABto.buttons[ABto.SendNum()]->coord.y - AB.buttons[AB.SendNum()]->coord.y)}, {200, 0, 0, 255});
            DrawRectangleV({ABto.buttons[ABto.SendNum()]->coord.x - 180, ABto.buttons[ABto.SendNum()]->coord.y + 37}, {180, 10}, {200, 0, 0, 255});
        }
        if (InvalidRequest) 
        {
            static unsigned char inReqOpacity = 0;
            static int errorTimer = 120;
            static float inReqXpos = 1200, inReqMargin = 50;
            if (errorTimer >= 0) 
            {
                rl_DrawTextureEx(invalidRequest, {inReqXpos, 909}, 0, 5, {255, 255, 255, inReqOpacity});
                inReqXpos -= inReqMargin;
                if (inReqOpacity <= 255 - 20) {
                    inReqOpacity += 20;
                }
                else {
                    inReqOpacity += 255 - inReqOpacity;
                }
                inReqMargin /= 2;
                --errorTimer;
            }
            else if(errorTimer == -1)
            {
                inReqMargin = 10;
                errorTimer--;
            }
            else if(errorTimer > -120)
            {
                rl_DrawTextureEx(invalidRequest, {inReqXpos, 909}, 0, 5, {255, 255, 255, inReqOpacity});
                inReqXpos += inReqMargin;
                if (inReqOpacity >= 40) {
                    inReqOpacity -= 40;
                }
                else {
                    inReqOpacity = 0;
                }
                inReqMargin /= 2;
                --errorTimer;
            }
            else 
            {
                errorTimer = 120;
                inReqXpos = 1200;
                inReqMargin = 50;
                inReqOpacity = 0;
                InvalidRequest = false;
            }
        }
    }
    else if (status == SENT) 
    {
        //for sent Status
        
        rl_DrawTextureEx(Sent, sentPos, 0, sentScale, {255, 255, 255, transparensy});
        if(sentScale >= 3)
        {
            sentScale -= 0.25;
        }
        if(GetTime() - startTimeSent < 0.35) 
        {
            sentSpeed -= 1;
        }
        else if(GetTime() - startTimeSent < 1) 
        {
            sentSpeed += 2;
        }
        if(transparensy >= 4) transparensy-= 4;
        sentPos.x = (screenWidth - 500 - Sent.width * sentScale) / 2 + 500;
        sentPos.y -= sentSpeed;
    }
}

void App::sentLogic()
{
    if(startTimeSent + 2 < GetTime())
    {
        this->status = STARTING;
        sentSpeed = 0;
        sentScale = 10;
        sentTimer = 60;
        sentPos = {(screenWidth - 500 - Sent.width * 10) / 2 + 500, (screenHeight - 100 - Sent.height * 10) / 2 + 100};
        transparensy = 255;
    }
}