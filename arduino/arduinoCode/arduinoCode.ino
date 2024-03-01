#include <SoftwareSerial.h>

enum St : char 
{
  GOING_TO_START = 1
  WAITING_FOR_TAKING = 2,
  DOING_REQUEST = 3,
  WAITING_FOR_RDOPPING = 4,
  DONE = 5,
  READED = 6;
};

St status;

void sendStatus()
{
  Serial3.write(status);
  Serial3.flush();
  Serial.print("sent: ");
  Serial.println(status);
  delay(50);
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
  if(status == GOING_TO_START)
  {
    
  }
  else if(status == WAITING_FOR_TAKING)
  {
    delay(5000);
    status = DOING_REQUEST;
    sendStatus();
    Serial.println("took");
  }
  else if(status == DOING_REQUEST)
  {

  }
  else if(status == WAITING__FOR_DROPPING)
  {
    delay(5000);
    status = DONE;
  }
  else if (status == DONE) 
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
  else if(status == READED)
  {
    sendStatus();
    
  }
}
