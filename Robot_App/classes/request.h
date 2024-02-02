#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include<map>
#include "graf.h"

class Request
{
public:
    std::vector<char> path;
    int from, to;
    Request(int from, int to, Graf* graf);
    std::vector<char> getPath();
};
