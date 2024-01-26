#include "queue.h"
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

void Queue::addRequest(Request* request)
{
    priority.push_back(request);
}

Queue::Queue(std::vector<Request *> requests)
{
    for (short i = 0; i < requests.size(); i++)
    {
        addRequest(requests[i]);
    }
}

void Queue::draw(Vector2 coord, Color color)
{
    for(short i = 0; i < priority.size(); i++)
    {
        DrawRectangleV({coord.x, coord.y + 75 * i}, {200, 50}, color);
        std::string text = char(priority[i]->from + 42) + "->" + char(priority[i]->to + 42);
        DrawText(text.c_str(), coord.x + 50, 10 + coord.y + 75 * i, 10, WHITE);
    }
}