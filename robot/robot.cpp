#include "robot.h"

void Robot::send(std::vector<char> path, ceSerial* com)//ceSerial *com, 
{
    bool successFlag;
    std::string s = "";
    for (short i = 0; i < path.size(); i++)
    {
        if(i != 0) s += ",";
        s += std::to_string(path[i]);   
    }
    s += ';';
    printf("Writing %s of size %d\n", s.c_str(), s.length() + 1);
    successFlag = com->Write(s.c_str(), s.length() + 1); // write string
    Sleep(200);
}

void Robot::read(ceSerial *com)
{ 
    bool successFlag;
    char status = com->ReadChar(successFlag); // read a char
    this->status = RobotStatus(status);
    if(status != 0) std::cout << "read: " + std::to_string(status) + '\n'; 
}

RobotStatus Robot::getStatus()
{
    return status;
}