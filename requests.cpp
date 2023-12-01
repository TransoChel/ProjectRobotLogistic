#include <iostream>
#include <vector>

unsigned const int numberOfDots = 5;

class Dot
{
public:
    int weight;
    bool isUsed;
    std::vector<int[2]> ways;
};

Dot dots[numberOfDots];

void addWay(Dot *dot1, Dot *dot2, int lenght)
{
}

void sendToRobot(std::vector<int> path)
{
}

class Request
{
public:
    std::vector<int> path;
    Request(int from, int to)
    {
        std::vector<std::vector<std::pair<int, int>>> g(numberOfDots);
        std::vector<int> d(numberOfDots, 9999), p(numberOfDots);
        std::vector<bool> used(numberOfDots, false);
        for (int i = 0; i < numberOfDots; i++)
        {
            int v = -1;
            for (int j = 0; j < numberOfDots; j++)
            {
                if (v == -1 || d[j] < d[v])
                {
                    v = j;
                }
                if (d[v] == 9999)
                    break;
                used[v] = true;

                for (int j = 0; j < g[v].size(); j++)
                {
                    int to = g[v][j].first,
                        len = g[v][j].second;
                    if (d[v] + len < d[to])
                    {
                        d[to] = d[v] + len;
                        p[to] = v;
                    }
                }
            }
        }
    }
};
