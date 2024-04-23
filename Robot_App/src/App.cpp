#include "App.h"




App::App(Graf* graf, ceSerial* com, Robot* robot, float screenWidth, float screenHeight)
{
    InitWindow(screenWidth, screenHeight, "RoboLogist");
    InitAudioDevice();
    SetTargetFPS(60); // Set our APP to run at 60 frames-per-second
    AB.buttons.push_back(&A);
    AB.buttons.push_back(&B);
    AB.buttons.push_back(&C);
    AB.buttons.push_back(&D);
    AB.buttons.push_back(&E);
    AB.buttons.push_back(&F);
    AB.buttons.push_back(&G);
    AB.buttons.push_back(&H);
    AB.buttons.push_back(&I);
    AB.buttons.push_back(&J);
    AB.buttons.push_back(&K);
    AB.buttons.push_back(&L);
    ABto.buttons.push_back(&Ato);
    ABto.buttons.push_back(&Bto);
    ABto.buttons.push_back(&Cto);
    ABto.buttons.push_back(&Dto);
    ABto.buttons.push_back(&Eto);
    ABto.buttons.push_back(&Fto);
    ABto.buttons.push_back(&Gto);
    ABto.buttons.push_back(&Hto);
    ABto.buttons.push_back(&Ito);
    ABto.buttons.push_back(&Jto);
    ABto.buttons.push_back(&Kto);
    ABto.buttons.push_back(&Lto);
    this->graf = graf;
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->robot = robot;
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
            if(send.CheckButtonPressed()) //(CheckCollisionPointRec(GetMousePosition(), {1425, 900, 100, 100})) 
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
                    queue.addRequest(Request(from, to, graf, robot));
                    AB.NullUpdate();
                    ABto.NullUpdate();
                }
            }
        }
    }
}

void App::drawGeneral()
{
    BeginDrawing();
    ClearBackground(WHITE);

    DrawRectangleV({0, 100}, {500, 935}, {255, 0, 0, 255});//queue light-red zone
    DrawRectangleV({0, 0}, {screenWidth, 100}, {200, 0, 0, 255});//red zone in the top
    rl_DrawTextureEx(logo, {18, 18}, 0, 2, WHITE); //наше лого в уголке
    rl_DrawTextureEx(queueTexture, {100, 125}, 0, 5, WHITE); //надпись "очередь"

    DrawRectangleV({25, 775}, {450, 200}, {255, 255, 255, 255});//статус робота
    DrawRectangleV({35, 785}, {430, 180}, {255, 0, 0, 255});

    queue.draw({150, 250}, {255, 0, 0, 255});

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
        AB.Draw();
        ABto.Draw();
        if (ShouldIDrawArrow)
        {
            DrawRectangleV({AB.buttons[AB.SendNum()]->coord.x + 350, AB.buttons[AB.SendNum()]->coord.y + 20}, {180, 10}, {200, 0, 0, 255}); 
            DrawRectangleV({(screenWidth - 500) / 2 - 5 + 500, std::min(AB.buttons[AB.SendNum()]->coord.y + 20, ABto.buttons[ABto.SendNum()]->coord.y + 20) + 10}, {10, std::abs(ABto.buttons[ABto.SendNum()]->coord.y - AB.buttons[AB.SendNum()]->coord.y)}, {200, 0, 0, 255});
            DrawRectangleV({ABto.buttons[ABto.SendNum()]->coord.x - 180, ABto.buttons[ABto.SendNum()]->coord.y + 20}, {180, 10}, {200, 0, 0, 255});
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
        static unsigned char transparensy = 255;
        static float sentSpeed = 0, sentScale = 10, sentTimer = 60;
        static Vector2 sentPos = {(screenWidth - 500 - Sent.width * 10) / 2 + 500, (screenHeight - 100 - Sent.height * 10) / 2 + 100};
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

        if(GetTime() - startTimeSent > 2)
        {
            sentSpeed = 0;
            sentScale = 10;
            sentTimer = 60;
            sentPos = {(screenWidth - 500 - Sent.width * 10) / 2 + 500, (screenHeight - 100 - Sent.height * 10) / 2 + 100};
            transparensy = 255;
        }
    }
    
    EndDrawing();
}

void App::logic()
{
    if (status == SENT && GetTime() - startTimeSent > 2) 
    {
        status = STARTING;
    }
    else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        LeftMouseButtonPressed();
    }
    queue.sendRequestIfNeed(robot, com);
}