#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include "Graf.h"
#include "../../robot/robot.h"

class Request
{
public:
    std::string path, algorithm, algorithmToStart;
    int from, to;
    std::string calculatePath(int from, int to, Graf* graf);
    std::string calculateTurn(short from, short to, short direction, Graf* graf);
    Request(int from, int to, Graf* graf, Robot* robot);
    std::string getPath();
};
