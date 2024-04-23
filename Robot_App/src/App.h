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
    RadioButton A = RadioButton({radioButtonFromX, 180}, {350, 50}, RED, "1");
    RadioButton B = RadioButton({radioButtonFromX, 240}, {350, 50}, RED, "2");
    RadioButton C = RadioButton({radioButtonFromX, 300}, {350, 50}, RED, "3");
    RadioButton D = RadioButton({radioButtonFromX, 360}, {350, 50}, RED, "4");
    RadioButton E = RadioButton({radioButtonFromX, 420}, {350, 50}, RED, "5");
    RadioButton F = RadioButton({radioButtonFromX, 480}, {350, 50}, RED, "6");
    RadioButton G = RadioButton({radioButtonFromX, 540}, {350, 50}, RED, "7");
    RadioButton H = RadioButton({radioButtonFromX, 600}, {350, 50}, RED, "8");
    RadioButton I = RadioButton({radioButtonFromX, 660}, {350, 50}, RED, "9");
    RadioButton J = RadioButton({radioButtonFromX, 720}, {350, 50}, RED, "10");
    RadioButton K = RadioButton({radioButtonFromX, 780}, {350, 50}, RED, "11");
    RadioButton L = RadioButton({radioButtonFromX, 840}, {350, 50}, RED, "12");
    RadioButton Ato = RadioButton({radioButtonToX, 180}, {350, 50}, RED, "1");
    RadioButton Bto = RadioButton({radioButtonToX, 240}, {350, 50}, RED, "2");
    RadioButton Cto = RadioButton({radioButtonToX, 300}, {350, 50}, RED, "3");
    RadioButton Dto = RadioButton({radioButtonToX, 360}, {350, 50}, RED, "4");
    RadioButton Eto = RadioButton({radioButtonToX, 420}, {350, 50}, RED, "5");
    RadioButton Fto = RadioButton({radioButtonToX, 480}, {350, 50}, RED, "6");
    RadioButton Gto = RadioButton({radioButtonToX, 540}, {350, 50}, RED, "7");
    RadioButton Hto = RadioButton({radioButtonToX, 600}, {350, 50}, RED, "8");
    RadioButton Ito = RadioButton({radioButtonToX, 660}, {350, 50}, RED, "9");
    RadioButton Jto = RadioButton({radioButtonToX, 720}, {350, 50}, RED, "10");
    RadioButton Kto = RadioButton({radioButtonToX, 780}, {350, 50}, RED, "11");
    RadioButton Lto = RadioButton({radioButtonToX, 840}, {350, 50}, RED, "12");
public:
    bool ShouldIDrawArrow = false;
    bool InvalidRequest = false;
    RadioButtonControl AB;
    RadioButtonControl ABto;
    WindowStatus status = STARTING;
    TextureButton doRequest = TextureButton(Vector2({float(1920 - 500 - doRequestTexture.width * 5) / 2 + 500, float(1035 - 100 - doRequestTexture.height * 5) / 2 + 100}), 5, doRequestTexture);
    TextureButton send = TextureButton(Vector2({1450, 900}), 3, LoadTexture("../Robot_App/textures/send.png"));
    TextureButton toMenu = TextureButton(Vector2({1575, 900}), 3, LoadTexture("../Robot_App/textures/toMenu.png"));
    Queue queue;
    App(Graf* graf, ceSerial* com, Robot* robot, float screenWidth, float screenHeight);
    void LeftMouseButtonPressed();
    void drawGeneral();
    void sentLogic();
    void logic();
};