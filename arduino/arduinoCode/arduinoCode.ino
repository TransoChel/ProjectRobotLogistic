#include <AFMotor.h>

#include <SoftwareSerial.h>

#define S1 1
#define S2 2
#define S3 3

AF_DCMotor motor[2];

void motorLeft(int v)
{
  motor[0].setSpeed(abs(v));
  if(v / abs(v) > 0) motor[0].run(FORWARD);
  else motor[0].run(BACKWARD);
}

void motorRight(int v)
{
  motor[1].setSpeed(abs(v));
  if(v / abs(v) > 0) motor[1].run(FORWARD);
  else motor[1].run(BACKWARD);
}

sensorData[2];

void readSensors()
{

}

void line()
{
  float err, u, kP = 1, kD = 10, kI = 0.001, i, eold = 0;
  while()
  {
  readSensor();
  err = sensorData[1] - sensorData[0];
  u = err * kP + (err - eold) * kD + i;
  i += kI * err
  motorLeft(v + u);
  motorRight(v - u);
  delay(1);
  eold = err;
  }
}

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
