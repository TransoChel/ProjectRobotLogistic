#include "robot.h"

void Robot::send(std::vector<char> path)//ceSerial *com, 
{
    ceSerial com("\\\\.\\COM4", 9600, 8, 'N', 1);
    if (!com.Open()) printf("OK.\n");
    bool successFlag;
    std::string s = "";
    for (short i = 0; i < path.size(); i++)
    {
        if(i != 0) s += ",";
        s += std::to_string(path[i]);   
    }
    printf("Writing %s of size %d\n", s.c_str(), s.length() + 1);
    successFlag = com.Write(s.c_str(), s.length() + 1); // write string
    com.Close();
}

void Robot::read(ceSerial *com, Robot *robot)
{
    bool successFlag;
    char status = com->ReadChar(successFlag); // read a char
    printf("Closing port %s.\n", com->GetPort().c_str());
    robot->status = RobotStatus(status);
}

RobotStatus Robot::getStatus()
{
    return status;
}