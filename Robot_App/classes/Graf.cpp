#include "Graf.h"

void Graf::addWay(int from, int to, int lenght)
{
    if (!g[from].count(to) && !g[to].count(from))
    {
        g[from][to] = lenght;
        g[to][from] = lenght;
    }
}

void Graf::addNeighbors(int from, std::vector<std::pair<int, int>> neighbors)
{
    for (int i = 0; i < neighbors.size(); i++)
    {
        addWay(from, neighbors[i].first, neighbors[i].second);
    }
}
void Graf::writeGraf()
{
    addNeighbors(0, {{1, 10}, {2, 5}});
    addNeighbors(1, {{2, 6}, {3, 15}});
    addNeighbors(2, {{3, 14}, {4, 7}});
    addNeighbors(3, {{4, 12}, {6, 2}});
    addNeighbors(4, {{5, 11}});
    addNeighbors(5, {{6, 6}});
}