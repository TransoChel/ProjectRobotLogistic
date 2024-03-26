#ifndef ROBOT_H
#define ROBOT_H

#include <stdio.h>
#include <vector>
#include <iostream>
#include "ceSerial.h"


enum RobotStatus : char
{
    ON = 0,
    GO_TO_TAKE = 1,
    WAITING_FOR_TAKING = 2,
    DOING_REQUEST = 3,
    WAITING_FOR_DROPPING = 4,
    DONE = 5,
    READED = 6
};

class Robot
{
private:
    RobotStatus status = ON;

public:
    int correctPosition = 0, correctDirection = 0;
    void send(std::string path, ceSerial* com);//ceSerial *com, 
    void read(ceSerial *com);
    RobotStatus getStatus();
};

#endif