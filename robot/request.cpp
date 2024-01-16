#include <iostream>
#include <vector>
#include <algorithm>
#include<map>
#include "graf.cpp"

class Request
{
public:
    std::vector<char> path;
    Request(int from, int to, Graf* graf)
    {
        short d[graf->numberOfDots];  // d - вектор путей до точки, индекс - номер точки, значение - длинна пути до него
        bool isUsed[graf->numberOfDots];
        char father[graf->numberOfDots];
        for(char i = 0; i < graf->numberOfDots; i++)
        {
            isUsed[i] = false;
            father[i] = 0;
            d[i] = -3;
        }
        d[from] = 0;
        for (int i = 0; i < graf->numberOfDots; i++) // выполнить для всех точек
        {
            char v = -1;// v - точка с которой мы делаем всякое
            for (int j = 0; j < graf->numberOfDots; j++) //ищем ближайшего соседа точки v
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

            for (auto [target, len] : graf->g[v])
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
