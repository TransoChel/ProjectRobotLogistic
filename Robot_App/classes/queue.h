#pragma once
#include "request.cpp"
#include <vector>
#include <raylib.h>

class Queue
{
private:
    std::vector<Request*> priority;
public:
    Request* getNext();
    void doneThis();
    void addRequest(Request* request);
    Queue() {};
    Queue(std::vector<Request*> requests);
    void draw(Vector2 coord, Color color);
};