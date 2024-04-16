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
        const char text[5] = {char(requests[i].from + 49), '-', '>', char(requests[i].to + 49), 0};
        rl_DrawText(&text[0], coord.x + 65, 10 + coord.y + 75 * drawPosition, 30, WHITE);
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