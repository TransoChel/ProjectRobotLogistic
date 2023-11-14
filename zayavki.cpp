#include <iostream>
class dot
{
    public:
        std::string name;
        int number;
        dot(std::string name, int number)
        {
            this->name = name;
            this-> number = number;
        }
};
int const quantityOfDots = 4;
dot a("a", 0), b("b", 1), c("c", 2), d("d", 3);
bool mapOfWays[quantityOfDots][quantityOfDots];
void addWay(int dot1, int dot2) 
{
    mapOfWays[dot1][dot2] = 1;
}