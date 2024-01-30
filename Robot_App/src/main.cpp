#include <string>
#include <vector>
#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "extras/raygui.h"
#include "../classes/request.cpp"
#include "../classes/queue.cpp"
#include "../classes/button.cpp"
#include "../classes/radiobutton.cpp"
#include "../classes/radiobuttoncontrol.cpp"

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1035;


    Graf graf;
    graf.writeGraf();

    Request A_B(4, 6, &graf);
    Request B_C(1, 2, &graf), A_C(2, 0, &graf);


    InitWindow(screenWidth, screenHeight, "RoboLogist");

    bool OrderMenu = false;
    bool Sent = false;
    int from, to;
    Color selectedColor = GREEN;
    int sentTimer = 180;

    SetTargetFPS(60); // Set our APP to run at 60 frames-per-second
    //---------------------------------------------------------------------------------------

    Texture2D logo = LoadTexture("../Robot_App/textures/logo.png");
    Texture2D doRequest = LoadTexture("../Robot_App/textures/doRequest.png");
    Texture2D toMenu = LoadTexture("../Robot_App/textures/toMenu.png");
    Texture2D send = LoadTexture("../Robot_App/textures/send.png");
    Texture2D fromTo = LoadTexture("../Robot_App/textures/fromTo.png");
    Texture2D queueTexture = LoadTexture("../Robot_App/textures/queue.png");

    RadioButton A({675, 325}, {350, 75}, RED, "A");
    RadioButton B({675, 425}, {350, 75}, RED, "B");
    RadioButton C({675, 525}, {350, 75}, RED, "C");
    RadioButton D({675, 625}, {350, 75}, RED, "D");
    RadioButton E({675, 725}, {350, 75}, RED, "E");
    RadioButton Ato({1325, 325}, {350, 75}, RED, "A");
    RadioButton Bto({1325, 425}, {350, 75}, RED, "B");
    RadioButton Cto({1325, 525}, {350, 75}, RED, "C");
    RadioButton Dto({1325, 625}, {350, 75}, RED, "D");
    RadioButton Eto({1325, 725}, {350, 75}, RED, "E");
    RadioButtonControl AB;
    RadioButtonControl ABto;
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
    
    Queue queue;
    queue.addRequest(&A_B);
    queue.addRequest(&B_C);
    queue.addRequest(&A_C);
    

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

        int from, to;

        if (Sent) {
            while (sentTimer >= 0) {
                ++sentTimer;
            }
            Sent = false;
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (CheckCollisionPointRec(GetMousePosition(), {960, 450, 128 * 5, 32 * 5}) && !OrderMenu)
            {
                OrderMenu = true;
            }
            else if (OrderMenu)
            {
                AB.Update();
                ABto.Update();
                if (CheckCollisionPointRec(GetMousePosition(), {1550, 900, (float)toMenu.width * 3, (float)toMenu.height * 3}))
                {
                    OrderMenu = false;
                    AB.NullUpdate();
                    ABto.NullUpdate();
                }
                if (AB.CheckUpdate() && ABto.CheckUpdate()) {
                    if (CheckCollisionPointRec(GetMousePosition(), {1425, 900, 100, 100})) {
                        from = AB.SendNum();
                        to = AB.SendNum();
                        Sent = true;
                        OrderMenu = false;
                        AB.NullUpdate();
                        ABto.NullUpdate();
                    }
                }
            }
        }

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(WHITE);
        DrawRectangleV({0, 100}, {500, 935}, {255, 0, 0, 255});
        DrawRectangleV({0, 0}, {screenWidth, 100}, {200, 0, 0, 255});
        DrawTextureEx(logo, {18, 18}, 0, 2, WHITE);
        DrawTextureEx(queueTexture, {100, 125}, 0, 5, WHITE);
        queue.draw({150, 250}, {255, 0, 0, 255});
        if (!OrderMenu && !Sent)
        {
            DrawTextureEx(doRequest, {960, 450}, 0, 5, WHITE);
        }
        else if (OrderMenu)
        {
            DrawTextureEx(toMenu, {1550, 900}, 0, 3, WHITE);
            DrawText("From", 775, 250, 60, RED);
            DrawText("To", 1450, 250, 60, RED);
            //DrawTextureEx(fromTo, {920, 125}, 0, 3, WHITE);
            DrawTextureEx(fromTo, {975, 125}, 0, 3, WHITE);
            DrawTextureEx(send, {1425, 900}, 0, 3, WHITE);
            AB.Draw();
            ABto.Draw();
        }
        else if (Sent) {
            DrawText("Order sent!", 1000, 500, 90, RED);
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}