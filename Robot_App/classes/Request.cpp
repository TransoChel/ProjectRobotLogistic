#include "Request.h"

Request::Request(int from, int to, Graf* graf)
{
    this->from = from;
    this->to = to;
    
    unsigned short d[graf->numberOfDots - 1];  // d - вектор путей до точки, индекс - номер точки, значение - длинна пути до него
    bool isUsed[graf->numberOfDots - 1];
    char father[graf->numberOfDots - 1];
    
    for(char i = 0; i < graf->numberOfDots; i++)
    {
        isUsed[i] = false;
        father[i] = 0;
        d[i] = -1;
    }
    std::cout <<"IM ALIVE";
    
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
    

    for (char v = to; v != from; v = father[v]) //восстанавливаем путь до изначально точки to от точки from
    {
        this->path.push_back(v);
    }
    this->path.push_back(from);
    std::reverse(this->path.begin(), this->path.end());
    for(short i = 0; i < path.size(); i++)
    {
        std::cout << int(path[i]) << ' ';
    }
    std::cout <<'\n';

    for(short i; i < path.size(); i++)
    {
        
    }
}

std::string calculateTurn(short from, short to, short direction, Graf* graf)
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

std::vector<char> Request::getPath()
{
    return algorithm;
}