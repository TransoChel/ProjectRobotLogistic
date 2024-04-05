#include "robot.h"

void Robot::send(std::string path, ceSerial* com)//ceSerial *com, 
{
    bool successFlag;
    std::string s = path;
    //s += ';';
    printf("Writing %s of size %d\n", s.c_str(), s.length() + 1);
    successFlag = com->Write(s.c_str(), s.length()); // write string
    Sleep(2000);
}

void Robot::read(ceSerial *com)
{ 
    bool successFlag;
    char status = com->ReadChar(successFlag); // read a char
    if(successFlag) this->status = RobotStatus(status);
    if(status != 0) std::cout << "read: " + std::to_string(status) + '\n'; 
}

RobotStatus Robot::getStatus()
{
    return status;
}