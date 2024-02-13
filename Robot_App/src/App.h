#include "../classes/Request.h"
#include "../classes/Queue.h"
#include "../classes/RadioButtonControl.h"
#include "../classes/TextureButton.h"


enum WindowStatus
{
    STARTING = 0,
    ORDERING = 1,
    SENT = 2
};


class App
{
private:
    Graf* graf;
    int from, to;
    Texture2D logo = LoadTexture("../Robot_App/textures/logo.png");
    Texture2D queueTexture = LoadTexture("../Robot_App/textures/queue.png");
    Texture2D fromTo = LoadTexture("../Robot_App/textures/fromTo.png");
    Texture2D Sent = LoadTexture("../Robot_App/textures/Sent.png");
    Texture2D doRequestTexture = LoadTexture("../Robot_App/textures/doRequest.png");

    float radioButtonFromX = (1920 - 500 - 350) / 2 + 500 - 350, radioButtonToX = (1920 - 500 - 350) / 2 + 500 + 350;
    RadioButton A = RadioButton({radioButtonFromX, 325.f}, {350.f, 75}, RED, "A");
    RadioButton B = RadioButton({radioButtonFromX, 425}, {350, 75}, RED, "B");
    RadioButton C = RadioButton({radioButtonFromX, 525}, {350, 75}, RED, "C");
    RadioButton D = RadioButton({radioButtonFromX, 625}, {350, 75}, RED, "D");
    RadioButton E = RadioButton({radioButtonFromX, 725}, {350, 75}, RED, "E");
    RadioButton Ato = RadioButton({radioButtonToX, 325}, {350, 75}, RED, "A");
    RadioButton Bto = RadioButton({radioButtonToX, 425}, {350, 75}, RED, "B");
    RadioButton Cto = RadioButton({radioButtonToX, 525}, {350, 75}, RED, "C");
    RadioButton Dto = RadioButton({radioButtonToX, 625}, {350, 75}, RED, "D");
    RadioButton Eto = RadioButton({radioButtonToX, 725}, {350, 75}, RED, "E");
public:
    bool ShouldIDrawArrow = false;
    RadioButtonControl AB;
    RadioButtonControl ABto;
    WindowStatus status = STARTING;
    TextureButton doRequest = TextureButton(Vector2({float(1920 - 500 - doRequestTexture.width * 5) / 2 + 500, float(1035 - 100 - doRequestTexture.height * 5) / 2 + 100}), 5, doRequestTexture);
    TextureButton send = TextureButton(Vector2({1425, 900}), 3, LoadTexture("../Robot_App/textures/send.png"));
    TextureButton toMenu = TextureButton(Vector2({1550, 900}), 3, LoadTexture("../Robot_App/textures/toMenu.png"));
    Queue queue;
    App(Graf* graf);
    void LeftMouseButtonPressed();
    void drawGeneral(float screenWidth, float screenHeight);
};