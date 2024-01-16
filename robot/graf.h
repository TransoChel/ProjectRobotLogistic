#include <vector>
#include <algorithm>
#include <map>

class Graf
{    
public:
    const unsigned short numberOfDots = 7;
    std::vector<std::map<int, int>> g; // двумерный вектор пар "таблица смежности" int1 - точка куда ведёт ребро, int2 - его вес. Первая мера вектора - все точки, Вторая мера вектора - конкретная точка, от неё идут пары с ребром.
    Graf()
    {
        g = std::vector<std::map<int, int>> (numberOfDots);
    }
    void addWay(int from, int to, int lenght);
    void addNeighbors(int from, std::vector<std::pair<int, int>> neighbors);
    void writeGraf();
};