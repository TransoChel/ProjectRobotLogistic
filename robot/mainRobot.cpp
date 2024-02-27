#include "robot.cpp"
#include<iostream>

int main()
{
    ceSerial com("\\\\.\\COM4", 9600, 8, 'N', 1);
    Robot logist;

   // printf("Opening port %s.\n", com.GetPort().c_str());
    
    
    
    for(int i = 0; i < 100; i++)
    {
        logist.read(&com);//&com, 
        Sleep(20);
    }
    std::cout<< "finish";
    com.Close();
}