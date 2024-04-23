#include "Queue.h"
#include <string>

Request* Queue::getNext()
{
    return priority[1];
}

void Queue::addRequest(Request request)
{
    requests.push_back(request);
}

Queue::Queue(std::vector<Request> requests) 
{
    for (short i = 0; i < requests.size(); i++)
    {
        addRequest(requests[i]);
    }
}

void Queue::draw(Vector2 coord, Color color)
{
    for(short i = 0; i < requests.size(); i++)
    {
        double drawPosition = i + drawDelta;
        DrawRectangleV({coord.x, coord.y + 75 * drawPosition}, {200, 50}, color);
        rl_DrawText((std::to_string(requests[i].from + 1) + " -> " + std::to_string(requests[i].to + 1)).c_str(), coord.x + 65, 10 + coord.y + 75 * drawPosition, 30, WHITE);
    }

    if (drawDelta >= 0) {
        drawDelta -= 0.1;
    }
}

void Queue::sendRequest(Robot* robot, ceSerial* com)
{
    drawDelta++;
    robot->send(requests[0].getPath(), com);
    requests.erase(requests.begin());
}
void Queue::sendRequestIfNeed(Robot* robot, ceSerial* com)
{
    static double timer = GetTime();
    if(robot->getStatus() == 5 && requests.size() && GetTime() - timer > 1) 
    {
        sendRequest(robot, com);
        timer  = GetTime();    
    }
}