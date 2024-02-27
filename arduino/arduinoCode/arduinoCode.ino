#include <SoftwareSerial.h>

enum St : char 
{
  READED = 5,
  WAITING_FOR_TAKING = 1,
  DOING_REQUEST = 2,
  WAITING_FOR_RDOPPING = 3,
  DONE = 4,
};

St status;

void sendStatus()
{
  Serial1.write(status);
}

void setup() 
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.println("begin");

  // set the data rate for the SoftwareSerial port
  Serial3.begin(9600);
  Serial.println("connected myserial");
  status = READED;
}
String dataFromComputer = "";
void loop() 
{  // run over and over
  if (status == DONE) 
  {
    char c = Serial3.read();
    if (c != -1) 
    {
      dataFromComputer += String(c);
      if (c == 0) 
      {
        Serial.println(dataFromComputer);
        dataFromComputer = "";
      }
    }
    sendStatus();
    Serial.println("reading");
  }
  else if(status == WAITING_FOR_TAKING)
  {
    delay(5000);
    status = DOING_REQUEST;
    sendStatus();
    Serial.println("took");
  }
  else
  {
    sendStatus();
    Serial.print("sent: ");
    Serial.println(status);
  }
}
