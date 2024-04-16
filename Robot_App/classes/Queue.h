#ifndef QUEUE_H
#define QUEUE_H
#include "Request.h"
#include <vector>
#include <raylib.h>
#include "../../robot/robot.h"

class Queue
{
private:
    std::vector<Request*> priority;
    std::vector<Request> requests;
    Graf* graf;
public:
    Request* getNext();
    void addRequest(Request request);
    void sendRequest(Robot* robot, ceSerial* com);
    void sendRequestIfNeed(Robot* robot, ceSerial* com);
    Queue() {};
    Queue(std::vector<Request> requests);
    void draw(Vector2 coord, Color color);
    double drawDelta = 0;
};
#endif