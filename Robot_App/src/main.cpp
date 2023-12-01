#include <string>

#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "extras/raygui.h"

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1400;
    const int screenHeight = 700;

    InitWindow(screenWidth, screenHeight, "Robot");

    bool OrderMenu = false;

    std::string text = "";
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //---------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            if(CheckCollisionPointRec(GetMousePosition(), {550, 225, 500, 250})) {
                OrderMenu = true;
            }
        }

        //----------------------------------------------------------------------------------

        

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLUE);
        DrawRectangleV({0, 0}, {300, 700}, DARKBLUE);
        DrawText("Query:", 75, 25, 50, WHITE);
        if (!OrderMenu) {
            DrawRectangleV({550, 225}, {500, 250}, SKYBLUE);
            DrawText("Order", 675, 325, 75, WHITE);
        }
        else {
            DrawText("Placeholder", 400, 100, 50, WHITE);
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