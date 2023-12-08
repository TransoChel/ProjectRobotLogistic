#include <iostream>
#include <vector>
#include <algorithm>
const unsigned short numberOfDots = 7;


int dots[numberOfDots] = {0, 1, 2, 3, 4, 5, 6};

void sendToRobot(std::vector<int> path){}
class Request
{
public:
    std::vector<int> path;
    Request(int from, int to)
    {
        std::vector<std::vector<std::pair<int, int>>> g(numberOfDots); // двумерный вектор пар "таблица смежности" int1 - точка куда ведёт ребро, int2 - его вес. Первая мера вектора - все точки, Вторая мера вектора - конкретная точка, от неё идут пары с ребром.
        
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

            for (int j = 0; j < g[v].size(); j++) //выполнить для всех соседей точки v
            {
                int target = g[v][j].first; // переменная номера точки куда идём
                int len = g[v][j].second; //переменная длины пути до to
                if (d[v] + len < d[target]) //если существующая указанная длина пути до точки to больше, чем посчитанная нами, то заменим значение
                {
                    d[target] = d[v] + len;
                    father[target] = v;//указать отцом точки to точку v
                }
            }
        }

        for (size_t i = 0; i < numberOfDots; i++)
        {
            std::cout << d[i] << "\n";
        }
        

        for (int v = to; v != from; v = father[v]) //восстанавливаем путь до изначально точки to от точки from
        {
            this->path.push_back(v);
        }
        this->path.push_back(from);
        std::reverse(this->path.begin(), this->path.end());
    }
};
