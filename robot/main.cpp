#include"requests.cpp"

int main()
{
    Request Test(0, 3);
    std::cout << "path: ";
    for(int i = 0; i < Test.path.size(); i++)
        std::cout << Test.path[i] << ' ';
}