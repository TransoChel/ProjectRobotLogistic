#include "Queue.h"
#include <string>

Request* Queue::getNext()
{
    return priority[1];
}

void Queue::doneThis()
{
    for(short i = 0; i < priority.size() - 1; i++)
    {
        priority[i] = priority[i + 1];
    }
    priority.pop_back();
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
        DrawRectangleV({coord.x, coord.y + 75 * i}, {200, 50}, color);
        const char text[5] = {char(requests[i].from + 65), '-', '>', char(requests[i].to + 65), 0};
        rl_DrawText(&text[0], coord.x + 65, 10 + coord.y + 75 * i, 30, WHITE);
    }
}

void Queue::sendRequest(Robot* robot, ceSerial* com)
{
    robot->send(requests[0].path, com);
    requests.erase(requests.begin());
}