#include"requests.cpp"

int main()
{
    Dot from, to;
    from.number = 0;
    to.number = 5;
    Request Test(from, to);
    for(int i = 0; i < Test.path.size(); i++)
        std::cout << Test.path[i].number << ' ';
}