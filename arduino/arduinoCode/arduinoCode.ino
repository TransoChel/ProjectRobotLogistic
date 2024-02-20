#include <SoftwareSerial.h>

enum status : char 
{
  WAITING_FOR_TAKING = 1,
  DOING_REQUEST = 2,
  WAITING_FOR_RDOPPING = 3,
  DONE = 4,
};

void setup() 
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.println("begin");

  // set the data rate for the SoftwareSerial port
  Serial3.begin(9600);
  Serial.println("connected myserial");
  status = DONE;
}
String dataFromComputer = "";
void loop() 
{  // run over and over
  if (status == DONE) 
  {
    char c = Serial3.read();
    if (c != -1) 
    {
      Serial.println(Serial3.available());
      Serial.print("Processing ");
      Serial.println(c);
      dataFromComputer += String(c);
      if (c == 0) 
      {
        Serial.println(dataFromComputer);
        dataFromComputer = "";
      }
    }
  }
  else if()
}
