#include "Graf.h"

void Graf::addWay(int from, int to, int lenght, int direction, int direction2)
{
    if (!g[from].count(to) && !g[to].count(from))
    {
        g[from][to] = {direction, lenght};
        g[to][from] = {direction2, lenght};
    }
}

void Graf::writeGraf()
{
    addWay(1, 2, 1, 2, 0);
	addWay(1, 3, 1, 3, 1);
	addWay(1, 0, 1, 2, 2);
	addWay(2, 6, 2, 3, 0);
	addWay(2, 3, 1, 4, 1);
	addWay(0, 3, 1, 2, 0);
	addWay(0, 4, 2, 2, 1);
	addWay(3, 5, 1, 3, 1);
	addWay(6, 10, 2, 2, 0);
	addWay(6, 7, 1, 4, 1);
	addWay(6, 5, 1, 0, 2);
	addWay(5, 7, 1, 3, 1);
	addWay(5, 4, 1, 3, 2);
	addWay(7, 4, 1, 0, 2);
	addWay(7, 9, 1, 3, 1);
	addWay(4, 8, 2, 1, 1);
	addWay(10, 9, 1, 0, 1);
	addWay(10, 11, 1, 2, 0);
	addWay(9, 11, 1, 1, 1);
	addWay(9, 8, 1, 2, 2);
	addWay(8, 11, 1, 0, 0);
    numberOfDots = 12;
}