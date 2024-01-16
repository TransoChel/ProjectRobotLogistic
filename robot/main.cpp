#include "request.cpp"
#include "robot.cpp"

int main()
{
    ceSerial com("\\\\.\\COM5", 9600, 8, 'N', 1);
    Robot logist;

    printf("Opening port %s.\n", com.GetPort().c_str());
    if (com.Open() == 0) printf("OK.\n");
    else printf("Error.\n");
    
    logist.send(&com, {0, 1, 2});

    com.Close();
}