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
    ceSerial* com; 
    Robot* robot;
    Graf* graf;
    double startTimeSent;
    int from, to; 
    float screenWidth, screenHeight;
    Texture2D logo = LoadTexture("../Robot_App/textures/logo.png");
    Texture2D queueTexture = LoadTexture("../Robot_App/textures/queue.png");
    Texture2D fromTo = LoadTexture("../Robot_App/textures/fromTo.png");
    Texture2D Sent = LoadTexture("../Robot_App/textures/Sent.png");
    Texture2D doRequestTexture = LoadTexture("../Robot_App/textures/doRequest.png");
    Texture2D fromTexture = LoadTexture("../Robot_App/textures/from.png");
    Texture2D toTexture = LoadTexture("../Robot_App/textures/to.png");
    Texture2D invalidRequest = LoadTexture("../Robot_App/textures/invalidRequest.png");
    Sound woosh = LoadSound("../Robot_App/sounds/sound_sent.wav");
    Sound ding = LoadSound("../Robot_App/sounds/sound_sent_2.wav");

    float radioButtonFromX = (1920 - 500 - 350) / 2 + 500 - 350, radioButtonToX = (1920 - 500 - 350) / 2 + 500 + 350;
    RadioButton A = RadioButton({radioButtonFromX, 325}, {350, 75}, RED, "A");
    RadioButton B = RadioButton({radioButtonFromX, 425}, {350, 75}, RED, "B");
    RadioButton C = RadioButton({radioButtonFromX, 525}, {350, 75}, RED, "C");
    RadioButton D = RadioButton({radioButtonFromX, 625}, {350, 75}, RED, "D");
    RadioButton E = RadioButton({radioButtonFromX, 725}, {350, 75}, RED, "E");
    RadioButton Ato = RadioButton({radioButtonToX, 325}, {350, 75}, RED, "A");
    RadioButton Bto = RadioButton({radioButtonToX, 425}, {350, 75}, RED, "B");
    RadioButton Cto = RadioButton({radioButtonToX, 525}, {350, 75}, RED, "C");
    RadioButton Dto = RadioButton({radioButtonToX, 625}, {350, 75}, RED, "D");
    RadioButton Eto = RadioButton({radioButtonToX, 725}, {350, 75}, RED, "E");

    short sentTimer = 2;
    unsigned char transparensy;
    float sentSpeed, sentScale;
    Vector2 sentPos;
public:
    bool ShouldIDrawArrow = false;
    bool InvalidRequest = false;
    RadioButtonControl AB;
    RadioButtonControl ABto;
    WindowStatus status = STARTING;
    TextureButton doRequest = TextureButton(Vector2({float(1920 - 500 - doRequestTexture.width * 5) / 2 + 500, float(1035 - 100 - doRequestTexture.height * 5) / 2 + 100}), 5, doRequestTexture);
    TextureButton send = TextureButton(Vector2({1425, 900}), 3, LoadTexture("../Robot_App/textures/send.png"));
    TextureButton toMenu = TextureButton(Vector2({1550, 900}), 3, LoadTexture("../Robot_App/textures/toMenu.png"));
    Queue queue;
    App(Graf* graf, ceSerial* com, Robot* robot, float screenWidth, float screenHeight);
    void LeftMouseButtonPressed();
    void drawGeneral();
    void sentLogic();
};