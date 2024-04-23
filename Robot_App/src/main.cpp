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
    Graf graf;
    graf.writeGraf();
    App app(&graf, &com, &logist, 1920, 1035);

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        logist.read(&com);
        
        if (app.AB.CheckUpdate() && app.ABto.CheckUpdate()) 
        {
            app.ShouldIDrawArrow = true;
        }

        app.logic();
        
        // Draw
        app.drawGeneral();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    rl_CloseWindow(); // Close window and OpenGL context
    com.Close();
    return 0;
}