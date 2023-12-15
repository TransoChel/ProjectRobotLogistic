#include <iostream>
#include <vector>
#include <algorithm>
#include<map>
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


void sendToRobot(std::vector<int> path){}
class Request
{
public:
    std::vector<int> path;
    Request(int from, int to)
    {
        addNeighbors(0, {{1, 10}, {2, 5}});
        addNeighbors(1, {{2, 6}, {3, 15}});
        addNeighbors(2, {{3, 14}, {4, 7}});
        addNeighbors(3, {{4, 12}, {6, 2}});
        addNeighbors(4, {{5, 11}});
        addNeighbors(5, {{6, 6}});
        std::vector<int> d(numberOfDots, 9999);  // d - вектор путей до точки, индекс - номер точки, значение - длинна пути до него
        d[from] = 0;
        std::vector<bool> isUsed(numberOfDots, false);
        std::vector<int> father(numberOfDots, 0);
        for (int i = 0; i < numberOfDots; i++) // выполнить для всех точек
        {
            int v = -1;// v - точка с которой мы делаем всякое
            for (int j = 0; j < numberOfDots; j++) //ищем ближайшего соседа точки v
            {
                if ((v == -1 || d[j] < d[v]) && !isUsed[j])
                {
                    // нашли
                    v = j;
                }
            }

            if (d[v] == 9999) // если путь до ближайшей точки 9999 то мы точно закончили
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
        

        for (int v = to; v != from; v = father[v]) //восстанавливаем путь до изначально точки to от точки from
        {
            this->path.push_back(v);
        }
        this->path.push_back(from);
        std::reverse(this->path.begin(), this->path.end());
    }
};
