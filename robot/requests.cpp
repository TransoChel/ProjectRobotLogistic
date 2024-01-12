#include <iostream>
#include <vector>
#include <algorithm>
#include<map>

#include <stdio.h>
#define CE_SERIAL_IMPLEMENTATION
#include "ceSerial.h"

const unsigned short numberOfDots = 7;

std::vector<std::map<int, int>> g(numberOfDots); // двумерный вектор пар "таблица смежности" int1 - точка куда ведёт ребро, int2 - его вес. Первая мера вектора - все точки, Вторая мера вектора - конкретная точка, от неё идут пары с ребром.


void addWay(int from, int to, int lenght)
{
    if(!g[from].count(to) && !g[to].count(from))
    {
        g[from][to] = lenght;
        g[to][from] = lenght;
    }
}
void addNeighbors(int from, std::vector<std::pair<int, int>> neighbors)
{
    for(int i = 0; i < neighbors.size(); i++)
    {
        addWay(from, neighbors[i].first, neighbors[i].second);
    }
}


void sendToRobot(ceSerial *com ,std::vector<char> path)
{

    bool successFlag;
    printf("Writing.\n");
    std::string s;
    for (short i = 0; i < path.size(); i++)
    {
        s += path[i];
    }
    char size = s.size();
    successFlag = com->Write(&size);
    successFlag = com->Write(s.c_str());       // write string
}
void readFromRobot(ceSerial *com)
{
    bool successFlag;
    char status = com->ReadChar(successFlag); // read a char

    printf("Closing port %s.\n", com->GetPort().c_str());
}
class Request
{
public:
    std::vector<char> path;
    Request(int from, int to)
    {
        addNeighbors(0, {{1, 10}, {2, 5}});
        addNeighbors(1, {{2, 6}, {3, 15}});
        addNeighbors(2, {{3, 14}, {4, 7}});
        addNeighbors(3, {{4, 12}, {6, 2}});
        addNeighbors(4, {{5, 11}});
        addNeighbors(5, {{6, 6}});
        short d[numberOfDots];  // d - вектор путей до точки, индекс - номер точки, значение - длинна пути до него
        bool isUsed[numberOfDots];
        char father[numberOfDots];
        for(char i = 0; i < numberOfDots; i++)
        {
            isUsed[i] = false;
            father[i] = 0;
            d[i] = -3;
        }
        d[from] = 0;
        for (int i = 0; i < numberOfDots; i++) // выполнить для всех точек
        {
            char v = -1;// v - точка с которой мы делаем всякое
            for (int j = 0; j < numberOfDots; j++) //ищем ближайшего соседа точки v
            {
                if ((v == -1 || d[j] < d[v]) && !isUsed[j])
                {
                    // нашли
                    v = j;
                }
            }

            if (d[v] == -3) // если путь до ближайшей точки -3 то мы точно закончили
                break;
            isUsed[v] = true; // помечаем v как уже обработанную

            for (auto [target, len] : g[v])
            {
                if (d[v] + len < d[target]) //если существующая указанная длина пути до точки to больше, чем посчитанная нами, то заменим значение
                {
                    d[target] = d[v] + len;
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
    }
    std::vector<char> getPath()
    {
        return path;
    }
};
