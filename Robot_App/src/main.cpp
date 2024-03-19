#include <string>
#include <vector>
#define RAYGUI_IMPLEMENTATION
#include "extras/raygui.h"

#define CE_SERIAL_IMPLEMENTATION
#include "App.h"

int main()
{
    ceSerial com("\\\\.\\COM4", 9600, 8, 'N', 1);
    Robot logist;
    if (com.Open()) printf("NOT OK.\n");
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1035;

    Graf graf;
    graf.writeGraf();

    InitWindow(screenWidth, screenHeight, "RoboLogist");
    InitAudioDevice();
    App app(&graf, &com, &logist, screenWidth, screenHeight);

    SetTargetFPS(60); // Set our APP to run at 60 frames-per-second
    //---------------------------------------------------------------------------------------
    

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------debug-functions---------------------------------------------

        //----------------------------------------------------------------------------------

        if (app.AB.CheckUpdate() && app.ABto.CheckUpdate()) 
        {
            app.ShouldIDrawArrow = true;
        }

        if (app.status == SENT) 
        {
            app.sentLogic();
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
        
        app.drawGeneral();
        app.queue.draw({150, 250}, {255, 0, 0, 255});

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    rl_CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    com.Close();
    return 0;
}