#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include "Graf.h"

class Request
{
public:
    std::string path, algorithm, algorithmtoStart;
    int from, to;
    std::string calculatePath(int from, int to, Graf* graf);
    Request(int from, int to, Graf* graf);
    std::string getPath();
};
