#include <string>
#include <vector>
#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "extras/raygui.h"
#include "../../robot/requests.cpp"
// 255 130 130

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1035;

    InitWindow(screenWidth, screenHeight, "RoboLogist");

    bool OrderMenu = false;
    bool Sent = false;
    int from, to;
    std::vector <Request> Queue;
    Color selectedColor = GREEN;
    

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
            else if(CheckCollisionPointRec(GetMousePosition(), {1420, 885, 1820, 935}) && OrderMenu) {
                OrderMenu = false;
            }
            //else if (CheckCollisionPointRec(GetMousePosition(), ))
            // else if (CheckCollisionPointCircle(GetMousePosition(), ))
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
        if (!OrderMenu && !Sent) {
            DrawTextureEx(doRequest, {960, 450}, 0, 5, WHITE);
            //DrawRectangleV({960, 350}, {500, 200}, {255, 0, 0, 255});
            //DrawText("Order", 1150, 410, 50, WHITE);
        }
        else {
            Sent = false;
            DrawTextureEx(toMenu, {1550, 900}, 0, 3, WHITE);
            DrawText("From", 750, 250, 60, RED);
            DrawRectangleV({675, 325}, {350, 75}, GRAY);
            DrawText("A", 830, 340, 50, RED);
            DrawRectangleV({675, 400}, {350, 75}, GRAY);
            DrawText("B", 830, 415, 50, RED);
            DrawRectangleV({675, 475}, {350, 75}, GRAY);
            DrawText("C", 830, 480, 50, RED);
            DrawRectangleV({675, 550}, {350, 75}, GRAY);
            DrawText("D", 830, 555, 50, RED);
            DrawTextureEx(fromTo, {920, 125}, 0, 3, WHITE);
            DrawTextureEx(send, {1425, 900}, 0, 3, WHITE);
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