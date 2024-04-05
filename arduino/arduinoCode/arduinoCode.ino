#include <AFMotor.h>

#include <SoftwareSerial.h>

#define S1 1
#define S2 2
#define S3 3
#define COMMON_SPEED 90

AF_DCMotor motorLeft(1, 90), motorRight(2, 90);

void motorLeftGo(int v)
{
  motorLeft.setSpeed(abs(v));
  if(v / abs(v) > 0) motorLeft.run(FORWARD);
  else motorLeft.run(BACKWARD);
}

void motorRightGo(int v)
{
  motorRight.setSpeed(abs(v));
  if(v / abs(v) > 0) motorRight.run(FORWARD);
  else motorRight.run(BACKWARD);
}

bool sensorData[2];

void readSensors()
{
  sensorData[0] = digitalRead(S1);
  sensorData[1] = digitalRead(S3);
}

void cross(byte v)
{
  float err, u, kP = 1, kD = 10, kI = 0.001, i, eold = 0;
  short crossCounter = 0;
  while(crossCounter > 30)
  {
    readSensors();
    err = sensorData[0] - sensorData[1];
    u = err * kP + (err - eold) * kD + i;
    i += kI * err;
    motorLeftGo(v + u);
    motorRightGo(v - u);
    delay(1);
    eold = err;
    if(sensorData[0] && sensorData[1]) crossCounter++;
  }
}

void forward(short sp)
{
  motorLeftGo(sp);
  motorRightGo(sp);
  delay(400);
  motorLeftGo(0);
  motorRightGo(0);
}

void turnToLine(short sp)
{
  int timer = millis();
  while(digitalRead(S2) && millis() < timer + 300)
  {
    motorLeftGo(sp);
    motorRightGo(-sp);
    delay(1);
  }
}

String dataFromComputer = "", algorithm, algorithmToStart;

enum St : char 
{
  ON = 0,
  GO_TO_TAKE = 1,
  WAITING_FOR_TAKING = 2,
  DOING_REQUEST = 3,
  WAITING_FOR_DROPPING = 4,
  DONE = 5,
  READED = 6
};

St status = ON;

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
  sendStatus();
  status = DONE;
}


void loop() 
{  // run over and over
  if(status == GO_TO_TAKE)
  {
    for(short i = 0; i < algorithmToStart.length(); i++)
    {
      if(algorithmToStart[i] == "1")
        {
          cross(COMMON_SPEED);
          forward(COMMON_SPEED);
        }
        else if(algorithmToStart[i] == "2")
        {
          turnToLine(COMMON_SPEED);
        }
        else if(algorithmToStart[i] == "3")
        {
          turnToLine(-COMMON_SPEED);
        }
    }
    status = WAITING_FOR_TAKING;
  }
  if(status == WAITING_FOR_TAKING)
  {
    delay(5000);
    status = DOING_REQUEST;
    sendStatus();
    Serial.println("took");
  }
  else if(status == DOING_REQUEST)
  {
    for(short i = 0; i < algorithm.length(); i++)
    {
      if(algorithm[i] == "1")
      {
        cross(COMMON_SPEED);
        forward(COMMON_SPEED);
      }
      else if(algorithm[i] == "2")
      {
        turnToLine(COMMON_SPEED);
      }
      else if(algorithm[i] == "3")
      {
        turnToLine(-COMMON_SPEED);
      }
      status = WAITING_FOR_DROPPING;
    }
  }
  else if(status == WAITING_FOR_DROPPING)
  {
    delay(5000);
    status = DONE;
  }
  else if (status == DONE) 
  {
    algorithm = "";
    algorithmToStart = "";
    String c = Serial3.readString();
    if (c != -1) 
    {
        short j = 0;
        for(short i = 0; c[i] != '4'; i++)
        {
          algorithmToStart += c[i];
          j = i + 2;

        }
        for(; j < c.length(); j++)
        {
          algorithm += c[j];
        }
        status = READED;
    }
    sendStatus();
    Serial.println("reading");
  }
  else if(status == READED)
  {
    sendStatus();
    Serial.println(algorithmToStart);
    Serial.println(algorithm);
    status = GO_TO_TAKE;
  }
  delay(1000);
}
