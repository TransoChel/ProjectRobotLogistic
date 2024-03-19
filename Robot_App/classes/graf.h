#include <vector>
#include <algorithm>
#include <map>
#include <utility>


class Graf
{    
public:
    unsigned short numberOfDots;
    std::vector<std::map<int, std::pair<int, int>>> g; // двумерный вектор пар "таблица смежности" int1 - порядок товек по часовой стрелки, pair1 - точка, куда ведёт ребро, pair2 - его вес. Первая мера вектора - все точки, Вторая мера вектора - конкретная точка, от неё идут пары с ребром.
    Graf()
    {
        g = std::vector<std::map<int, std::pair<int, int>>> (numberOfDots);
    }
    void addWay(int from, int to, int lenght, int direction, int direction2);
    void writeGraf();
};