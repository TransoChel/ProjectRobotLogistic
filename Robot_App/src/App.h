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
    short sentTimer = 2;
    unsigned char transparensy;
    float sentSpeed, sentScale;
    Vector2 sentPos;
public:
    bool ShouldIDrawArrow = false;
    bool InvalidRequest = false;
    RadioButtonControl LeftPanel;
    RadioButtonControl RightPanel;
    WindowStatus status = STARTING;
    TextureButton doRequest = TextureButton(Vector2({float(1920 - 500 - doRequestTexture.width * 5) / 2 + 500, float(1035 - 100 - doRequestTexture.height * 5) / 2 + 100}), 5, doRequestTexture);
    // TextureButton doRequest = TextureButton(Vector2({890, float(487.5)}), 5, doRequestTexture);
    TextureButton send = TextureButton(Vector2({1450, 900}), 3, LoadTexture("../Robot_App/textures/send.png"));
    TextureButton toMenu = TextureButton(Vector2({1575, 900}), 3, LoadTexture("../Robot_App/textures/toMenu.png"));
    Queue queue;
    App(Graf* graf, ceSerial* com, Robot* robot, float screenWidth, float screenHeight);
    void LeftMouseButtonPressed();
    void drawGeneral();
    void sentLogic();
};