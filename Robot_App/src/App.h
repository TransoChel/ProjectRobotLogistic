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
    Texture2D toMenu = LoadTexture("../Robot_App/textures/toMenu.png");
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
public:
    bool ShouldIDrawArrow = false;
    RadioButtonControl AB;
    RadioButtonControl ABto;
    WindowStatus status = STARTING;
    TextureButton doRequest = TextureButton(Vector2({960, 450}), (float)5, LoadTexture("../Robot_App/textures/doRequest.png"));
    TextureButton fromTo = TextureButton(Vector2({975, 125}), (float)3, LoadTexture("../Robot_App/textures/fromTo.png"));
    TextureButton send = TextureButton(Vector2({1425, 900}), (float)3, LoadTexture("../Robot_App/textures/send.png"));
    Queue queue;
    App(Graf* graf);
    void LeftMouseButtonPressed();
    void drawGeneral(float screenWidth);
};