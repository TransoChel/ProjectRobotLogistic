#include "Request.h"

std::string Request::calculatePath(int from, int to, Graf* graf)
{   
    std::string path;
    unsigned short d[graf->numberOfDots - 1];  // d - вектор путей до точки, индекс - номер точки, значение - длинна пути до него
    bool isUsed[graf->numberOfDots - 1];
    char father[graf->numberOfDots - 1];
    
    for(char i = 0; i < graf->numberOfDots; i++)
    {
        isUsed[i] = false;
        father[i] = 0;
        d[i] = -1;
    }
    //std::cout <<"IM ALIVE";
    
    d[from] = 0;
    
    for (int i = 0; i < graf->numberOfDots; i++) // выполнить для всех точек
    {
        char v = -1;// v - точка с которой мы делаем всякое
        for (int j = 0; j < graf->numberOfDots; j++)
        {
            if ((v == -1 || d[j] < d[v]) && !isUsed[j]) //задаём начальную точку и последующие ближайшие к ней
            {
                v = j;
            }
        }

        if (d[v] == -3) // если путь до ближайшей точки -3 то мы точно закончили
            break;
        isUsed[v] = true; // помечаем v как уже обработанную

        for (auto [target, rotation_len] : graf->g[v])
        {
            if (d[v] + rotation_len.second < d[target]) //если существующая указанная длина пути до точки to больше, чем посчитанная нами, то заменим значение
            {
                d[target] = d[v] + rotation_len.second;
                father[target] = v;//указать отцом точки to точку v
            }
        }
    }
    //std::cout <<"IM ALIVE2";

    for (char v = to; v != from; v = father[v]) //восстанавливаем путь до изначально точки to от точки from
    {
        path += v;
    }
    //std::cout <<"IM ALIVE3";
    path += from;
    //std::cout <<"IM ALIVE4";
    std::reverse(path.begin(), path.end());
    //std::cout <<"IM ALIVE5";
    return path;
}

Request::Request(int from, int to, Graf* graf, Robot* robot)
{
    this->from = from;
    this->to = to;
    std::string pathToFrom = calculatePath(robot->correctPosition, from, graf);
    path = calculatePath(from, to, graf);   
    // for(short i = 0; i < path.size(); i++)
    // {
    //     std::cout << int(path[i]) << ' ';
    // }
    // std::cout <<'\n';
    for(short i = 1; i < pathToFrom.size(); i++)
    {
        static short direction = robot->correctDirection;
        algorithmToStart += calculateTurn(pathToFrom[i - 1], pathToFrom[i], direction, graf);
        algorithmToStart += "1";
        direction = graf->g[pathToFrom[i - 1]][pathToFrom[i]].first;
    }
    for(short i = 1; i < path.size(); i++)
    {
        static short direction;
        if(pathToFrom.size() > 1) direction = graf->g[pathToFrom[pathToFrom.size() - 1]][from].first;
        else direction = robot->correctDirection;
        algorithm += calculateTurn(path[i - 1], path[i], direction, graf);
        algorithm += "1";
        direction = graf->g[path[i - 1]][path[i]].first;
    }
}

std::string Request::calculateTurn(short from, short to, short direction, Graf* graf)
{
    std::string algorithm;
    short result = graf->g[from][to].first - direction;
    if(result >= 0)
    {
        for(short i = 0; i < result; i++)
        {
            algorithm += "2";
        }
    }
    else
    {
        for(short i = 0; i > result; i--)
        {
            algorithm += "3";
        }
    }
    return algorithm;
}
// void goTo(short from, short to, short startDirection, unsigned short sp, bool ss)
// {
// 	short direction = startDirection;
// 	for(short i = 0; path[i] != to; i++)
// 	{
// 		goToNeighbor(path[i], path[i+1], direction, sp, ss);
// 		turn(ninety*2);
// 		direction = path[i];
// 	}
// }

std::string Request::getPath()
{
    return algorithmToStart + "4" + algorithm;
}