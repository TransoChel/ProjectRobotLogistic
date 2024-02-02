#include <string>
#include <vector>
#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "extras/raygui.h"
#include "app.h"

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    App app;
    const int screenWidth = 1920;
    const int screenHeight = 1035;

    Graf graf;
    graf.writeGraf();

    InitWindow(screenWidth, screenHeight, "RoboLogist");

    bool OrderMenu = false;
    bool Sent = false;
    bool DrawArrow = false;
    int from, to;
    Color selectedColor = GREEN;
    int sentTimer = 180;

    SetTargetFPS(60); // Set our APP to run at 60 frames-per-second
    //---------------------------------------------------------------------------------------
    

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

        int from, to;

        if (AB.CheckUpdate() && ABto.CheckUpdate()) {
            DrawArrow = true;
        }

        if (Sent) {
            if (sentTimer >= 0) {
                --sentTimer;
            }
            else {
                Sent = false;
            }
         }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            app.LeftMouseButtonPressed();
        }

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(WHITE);
        
        app.queue.draw({150, 250}, {255, 0, 0, 255});
        if (app.status == STARTING)
        {
            app.doRequest.Draw();
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
            if (DrawArrow) {
                DrawRectangleV({AB.buttons[AB.SendNum()]->coord.x + 350, AB.buttons[AB.SendNum()]->coord.y + 37}, {155, 10}, {200, 0, 0, 255});
                DrawRectangleV({1170, std::min(AB.buttons[AB.SendNum()]->coord.y + 37, ABto.buttons[ABto.SendNum()]->coord.y + 37) + 10}, {10, std::abs(ABto.buttons[ABto.SendNum()]->coord.y - AB.buttons[AB.SendNum()]->coord.y)}, {200, 0, 0, 255});
                DrawRectangleV({ABto.buttons[ABto.SendNum()]->coord.x - 155, ABto.buttons[ABto.SendNum()]->coord.y + 37}, {155, 10}, {200, 0, 0, 255});
            }
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