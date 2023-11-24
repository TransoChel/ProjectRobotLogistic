#include <iostream>
#include <vector>
class dot
{
    public:
        std::string name;
        int number;
        std::vector<int[2]> ways;
        dot(std::string name, int number)
        {
            this->name = name;
            this-> number = number;
        }
};

void addWay(dot* dot1, dot* dot2, int lenght)
{
    dot1->ways.push_back({dot2->number, lenght});
    dot2->ways.push_back({dot1->number, lenght});
}

void sendToRobot(std::vector<int> path)
{

}

class request
{
    public:
        request(dot from, dot to)
        {
            std::vector<int> path;
            //дописать
        }
};