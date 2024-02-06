#pragma once
#include "Request.h"
#include <vector>
#include <raylib.h>

class Queue
{
private:
    std::vector<Request*> priority;
    std::vector<Request> requests;
    Graf* graf;
public:
    Request* getNext();
    void doneThis();
    void addRequest(Request request);
    Queue() {};
    Queue(std::vector<Request> requests);
    void draw(Vector2 coord, Color color);
};