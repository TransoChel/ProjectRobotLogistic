#include <iostream>
#include <vector>
#include <algorithm>
const unsigned short numberOfDots = 7;
class Dot
{
public:
    int number, numberOfFather;
    bool isUsed;
    Dot()
    {
        isUsed = false;
        numberOfFather = 0;
    }
};

Dot dots[numberOfDots];

void sendToRobot(std::vector<int> path)
{
}

class Request
{
public:
    std::vector<Dot> path;
    Request(Dot from, Dot to)
    {
        std::vector<std::vector<std::pair<Dot, int>>> g(numberOfDots); // двумерный вектор пар "таблица смежности" Dot - точка куда ведёт ребро, int - его вес. Первая мера вектора - все точки, Вторая мера вектора - конкретная точка, от неё идут пары с ребром.
        
        g[0].push_back({dots[1], 10});
        g[0].push_back({dots[2], 5});
        g[1].push_back({dots[2], 6});
        g[1].push_back({dots[0], 10});
        g[2].push_back({dots[1], 6});
        g[2].push_back({dots[0], 5});
        g[2].push_back({dots[4], 7});
        g[2].push_back({dots[3], 14});
        g[3].push_back({dots[2], 14});
        g[3].push_back({dots[4], 12});
        g[3].push_back({dots[6], 2});
        g[4].push_back({dots[2], 7});
        g[4].push_back({dots[3], 12});
        g[4].push_back({dots[5], 11});
        g[5].push_back({dots[4], 11});
        g[5].push_back({dots[6], 6});
        g[6].push_back({dots[5], 6});
        g[6].push_back({dots[3], 2});
        
        std::vector<int> d(numberOfDots, 9999);  // d - вектор путей до точки, индекс - номер точки, значение - длинна пути до него
        std::vector<bool> used(numberOfDots, false);
        for (int i = 0; i < numberOfDots; i++) // выполнить для всех точек
        {
            Dot v;  v.number = -1;// v - точка с которой мы делаем всякое
            for (int j = 0; j < numberOfDots; j++) //ищем ближайшего соседа точки v
            {
                if (!v.isUsed && (v.number == -1 || d[j] < d[v.number]))
                {
                    v.number = j; // нашли
                }
            }

            if (d[v.number] == 9999) // если путь до ближайшей точки 9999 то мы точно закончили
                break;
            v.isUsed = true; // помечаем v как уже обработанную

            for (int j = 0; j < g[v.number].size(); j++) //выполнить для всех соседей точки v
            {
                Dot to = g[v.number][j].first; // переменная номера точки куда идём
                int len = g[v.number][j].second; //переменная длины пути до to
                if (d[v.number] + len < d[to.number]) //если существующая указанная длина пути до точки to больше, чем посчитанная нами, то заменим значение
                {
                    d[to.number] = d[v.number] + len;
                    to.numberOfFather = v.number;//указать отцом точки to точку v
                }
            }
        }

        for (Dot v = to; v.number != from.number; v.numberOfFather = v.number) //восстанавливаем путь до изначально точки to от точки from
            this->path.push_back(v);
        this->path.push_back(from);
        std::reverse(this->path.begin(), this->path.end());
    }
};
