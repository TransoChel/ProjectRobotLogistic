#include <string>

#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "extras/raygui.h"

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1035;

    InitWindow(screenWidth, screenHeight, "RoboLogi");

    bool OrderMenu = false;

    std::string text = "Ffjaslkj";
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //---------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            if(CheckCollisionPointRec(GetMousePosition(), {960, 350, 500, 200})) {
                OrderMenu = true;
            }
        }
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            if(CheckCollisionPointRec(GetMousePosition(), {1420, 885, 1820, 935}))
                OrderMenu = false;
        }

        //----------------------------------------------------------------------------------

        

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLUE);
        DrawRectangleV({0, 0}, {500, 1035}, DARKBLUE);
        DrawText("Queue", 175, 25, 50, WHITE);
        if (!OrderMenu) {
            DrawRectangleV({960, 350}, {500, 200}, SKYBLUE);
            DrawText("Order", 1150, 410, 50, WHITE);
        }
        else {
            DrawText("Placeholder", 1070, 25, 50, WHITE);
            DrawRectangleV({1420, 885}, {1820, 935}, DARKBLUE);
            DrawText("To main", 1600, 905, 50, WHITE);
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}