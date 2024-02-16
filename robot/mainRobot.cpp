#include "robot.cpp"
#include<iostream>

int main()
{
    ceSerial com("\\\\.\\COM4", 9600, 8, 'N', 1);
    Robot logist;

    printf("Opening port %s.\n", com.GetPort().c_str());
    if (!com.Open()) printf("OK.\n");
    else printf("Error.\n");
    
    for(int i = 0; i < 1024; i++)
    {
    logist.send(&com, {0, 1, 2});
    ceSerial::Delay(200);
    }
    std::cout<< "finish";
    com.Close();
}