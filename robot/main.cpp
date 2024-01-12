#include "requests.cpp"

int main()
{
    ceSerial com("\\\\.\\COM4", 9600, 8, 'N', 1);

    printf("Opening port %s.\n", com.GetPort().c_str());
    if (com.Open() == 0) printf("OK.\n");
    else printf("Error.\n");
    

    com.Close();
}