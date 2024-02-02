#include "../classes/request.h"
#include "../classes/queue.h"
#include "../classes/radioButtonControl.h"
#include "../classes/textureButton.h"


enum WindowStatus
{
    STARTING = 0,
    ORDERING = 1,
    SENT = 2
};


class App
{
private:
    WindowStatus status = STARTING;
    Texture2D logo = LoadTexture("../Robot_App/textures/logo.png");
    Texture2D toMenu = LoadTexture("../Robot_App/textures/toMenu.png");
    Texture2D send = LoadTexture("../Robot_App/textures/send.png");
    Texture2D fromTo = LoadTexture("../Robot_App/textures/fromTo.png");
    Texture2D queueTexture = LoadTexture("../Robot_App/textures/queue.png");

    RadioButton A = RadioButton({675.f, 325.f}, {350.f, 75}, RED, "A");
    RadioButton B = RadioButton({675, 425}, {350, 75}, RED, "B");
    RadioButton C = RadioButton({675, 525}, {350, 75}, RED, "C");
    RadioButton D = RadioButton({675, 625}, {350, 75}, RED, "D");
    RadioButton E = RadioButton({675, 725}, {350, 75}, RED, "E");
    RadioButton Ato = RadioButton({1325, 325}, {350, 75}, RED, "A");
    RadioButton Bto = RadioButton({1325, 425}, {350, 75}, RED, "B");
    RadioButton Cto = RadioButton({1325, 525}, {350, 75}, RED, "C");
    RadioButton Dto = RadioButton({1325, 625}, {350, 75}, RED, "D");
    RadioButton Eto = RadioButton({1325, 725}, {350, 75}, RED, "E");
    RadioButtonControl AB;
    RadioButtonControl ABto;
    // AB.buttons.push_back(&A);
    // AB.buttons.push_back(&B);
    // AB.buttons.push_back(&C);
    // AB.buttons.push_back(&D);
    // AB.buttons.push_back(&E);
    // ABto.buttons.push_back(&Ato);
    // ABto.buttons.push_back(&Bto);
    // ABto.buttons.push_back(&Cto);
    // ABto.buttons.push_back(&Dto);
    // ABto.buttons.push_back(&Eto);
public:
    TextureButton doRequest = TextureButton({960, 450}, {128 * 5, 32 * 5}, LoadTexture("../Robot_App/textures/doRequest.png"));
    Queue queue;
    void LeftMouseButtonPressed();
    void drawGeneral();
};