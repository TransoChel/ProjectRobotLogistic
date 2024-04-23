#include "App.h"




App::App(Graf* graf, ceSerial* com, Robot* robot, float screenWidth, float screenHeight)
{
    for (int i = 0; i < 12; ++i) {
        RadioButton* A = new RadioButton({radioButtonFromX, 180 + 60 * i}, {350, 50}, RED, std::to_string(i + 1));
        LeftPanel.buttons[i] = (A);
    }
    for (int i = 0; i < 12; ++i) {
        RadioButton* A = new RadioButton({radioButtonToX, 180 + 60 * i}, {350, 50}, RED, std::to_string(i + 1));
        RightPanel.buttons[i] = (A);
    }
    this->graf = graf;
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->robot = robot;

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
        LeftPanel.Update();
        RightPanel.Update();
        if (toMenu.CheckButtonPressed())
        {
            status = STARTING;
            ShouldIDrawArrow = false;
            InvalidRequest = false;
            LeftPanel.NullUpdate();
            RightPanel.NullUpdate();
        }
        if (LeftPanel.CheckUpdate() && RightPanel.CheckUpdate()) 
        {
            if(send.CheckButtonPressed()) //(CheckCollisionPointRec(GetMousePosition(), {1425, 900, 100, 100})) 
            {
                if (LeftPanel.SendNum() == RightPanel.SendNum()) {
                    InvalidRequest = true;
                }
                else {
                    from = LeftPanel.SendNum();
                    to = RightPanel.SendNum();
                    status = SENT;
                    startTimeSent = GetTime();
                    ShouldIDrawArrow = false;
                    InvalidRequest = false;
                    queue.addRequest(Request(from, to, graf, robot));
                    LeftPanel.NullUpdate();
                    RightPanel.NullUpdate();
                }
            }
        }
    }
}

void App::drawGeneral()
{
    DrawRectangleV({0, 100}, {500, 935}, {255, 0, 0, 255});//queue light-red zone
    DrawRectangleV({0, 0}, {screenWidth, 100}, {200, 0, 0, 255});//red zone in the top
    rl_DrawTextureEx(logo, {18, 18}, 0, 2, WHITE); //наше лого в уголке
    rl_DrawTextureEx(queueTexture, {100, 125}, 0, 5, WHITE); //надпись "очередь"

    DrawRectangleV({25, 775}, {450, 200}, {255, 255, 255, 255});//статус робота
    DrawRectangleV({35, 785}, {430, 180}, {255, 0, 0, 255});

    const char* statusText = robot->getStatusString().c_str();
    rl_DrawText(statusText, 240 - MeasureText(statusText, 50)/2, 875 - MeasureTextEx(GetFontDefault(), statusText, 50, 0).y/2, 50, WHITE);
    if (status == STARTING)
    {
        doRequest.Draw();
    }
    else if (status == ORDERING)
    {
        toMenu.Draw();
        rl_DrawTextureEx(fromTexture, {screenWidth - 710 - 180 - 175 - (52 * 5 / 2), 125}, 0, 5, WHITE);
        rl_DrawTextureEx(toTexture, {radioButtonToX + 175 - (34 * 5 / 2), 125}, 0, 5, WHITE);
        //DrawLine(0, 949, 1500, 949, BLACK);
        send.Draw();
        LeftPanel.Draw();
        RightPanel.Draw();
        if (ShouldIDrawArrow)
        {
            DrawRectangleV({LeftPanel.buttons[LeftPanel.SendNum()]->coord.x + 350, LeftPanel.buttons[LeftPanel.SendNum()]->coord.y + 20}, {180, 10}, {200, 0, 0, 255}); 
            DrawRectangleV({(screenWidth - 500) / 2 - 5 + 500, std::min(LeftPanel.buttons[LeftPanel.SendNum()]->coord.y + 20, RightPanel.buttons[RightPanel.SendNum()]->coord.y + 20) + 10}, {10, std::abs(RightPanel.buttons[RightPanel.SendNum()]->coord.y - LeftPanel.buttons[LeftPanel.SendNum()]->coord.y)}, {200, 0, 0, 255});
            DrawRectangleV({RightPanel.buttons[RightPanel.SendNum()]->coord.x - 180, RightPanel.buttons[RightPanel.SendNum()]->coord.y + 20}, {180, 10}, {200, 0, 0, 255});
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
            rl_PlaySound(ding);
            sentSpeed += 2;
        }
        if (GetTime() - startTimeSent < 0.65) {
            rl_PlaySound(woosh);
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