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

    Texture2D doRequest = LoadTexture("../textures/doRequest.png");
    Texture2D logo = LoadTexture("../textures/logo.png");
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
            if(CheckCollisionPointRec(GetMousePosition(), {920, 485, 640, 160})) {
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

        ClearBackground(WHITE);
        DrawRectangleV({0, 0}, {500, 1035}, LIGHTGRAY);
        DrawText("Queue", 150, 50, 50, BLACK);
        DrawRectangleV({0,0}, {1920, 100}, {255, 0, 0, 255});
        DrawText("RoboLogi", 114, 20, 50, WHITE);
        DrawTextureEx(logo, {25, 15}, 0 , 2, WHITE);  
        if (!OrderMenu) {
            DrawTextureEx(doRequest, {920, 485}, 0, 5, RAYWHITE);
        }
        else {
            DrawText("Placeholder", 1070, 125, 50, BLACK);
            DrawRectangleV({1420, 885}, {1820, 935}, {255, 0, 0, 255});
            DrawText("To main", 1600, 915, 50, BLACK);
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