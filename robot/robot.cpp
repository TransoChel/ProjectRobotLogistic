#include "robot.h"

void Robot::send(ceSerial *com, std::vector<char> path)
{
    bool successFlag;
    printf("Writing.\n");
    std::string s;
    for (short i = 0; i < path.size(); i++)
    {
        s += path[i];
    }
    char size = s.size();
    successFlag = com->Write(&size);
    successFlag = com->Write(s.c_str()); // write string
}

void Robot::read(ceSerial *com, Robot* robot)
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