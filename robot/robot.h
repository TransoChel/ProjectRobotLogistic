#pragma once

#include <vector>
#include <stdio.h>
#include <iostream>
#include "ceSerial.h"


enum RobotStatus : char
{
    OFF = 0,
    WAITING_FOR_TAKING = 1,
    DOING_REQUEST = 2,
    WAITING_FOR_RDOPPING = 3,
    DONE = 4,
};

class Robot
{
private:
    RobotStatus status = OFF;

public:
    void send(std::vector<char> path, ceSerial* com);//ceSerial *com, 
    void read(ceSerial *com);
    RobotStatus getStatus();
};