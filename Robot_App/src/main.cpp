#include <string>

#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "extras/raygui.h"

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1035;

    InitWindow(screenWidth, screenHeight, "RoboLogist");

    bool OrderMenu = false;

    std::string text = "Ffjaslkj";
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //---------------------------------------------------------------------------------------

    Texture2D logo = LoadTexture("../textures/logo.png");
    Texture2D doRequest = LoadTexture("../textures/doRequest.png");
    Texture2D toMenu = LoadTexture("../textures/toMenu.png");
    Texture2D send = LoadTexture("../textures/send.png");
    Texture2D fromTo = LoadTexture("../textures/fromTo.png");
    Texture2D queue = LoadTexture("../textures/queue.png");
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            if(CheckCollisionPointRec(GetMousePosition(), {960, 450, 128*5, 32*5}) && !OrderMenu) {
                OrderMenu = true;
            }
        }
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            if(CheckCollisionPointRec(GetMousePosition(), {1420, 885, 1820, 935}) && OrderMenu)
                OrderMenu = false;
        }

        //----------------------------------------------------------------------------------

        

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(WHITE);
        DrawRectangleV({0, 100}, {500, 935}, {255, 0, 0, 255});
        DrawRectangleV({0, 0}, {screenWidth, 100}, {200, 0, 0, 255});
        
        DrawTextureEx(logo, {18, 18}, 0, 2, WHITE);
        DrawTextureEx(queue, {100, 125}, 0, 5, WHITE);
        if (!OrderMenu) {
            DrawTextureEx(doRequest, {960, 450}, 0, 5, WHITE);
            //DrawRectangleV({960, 350}, {500, 200}, {255, 0, 0, 255});
            //DrawText("Order", 1150, 410, 50, WHITE);
        }
        else {
            DrawTextureEx(toMenu, {1350, 855}, 0, 5, WHITE);
            DrawTextureEx(fromTo, {920, 125}, 0, 5, WHITE);
            DrawTextureEx(send, {1150, 855}, 0, 5, WHITE);
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