#include <AFMotor.h>

#include <SoftwareSerial.h>

#define S1 22
#define S2 24
#define S3 3
#define COMMON_SPEED 90

AF_DCMotor motorLeft(4);
AF_DCMotor motorRight(1);

void motorLeftGo(int v)
{
  motorLeft.setSpeed(abs(v));
  if(v / abs(v) > 0) motorLeft.run(BACKWARD);
  else motorLeft.run(FORWARD);
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
  sensorData[0] = !digitalRead(S1);
  sensorData[1] = !digitalRead(S2);
}

void testSensors()
{
  readSensors();
  Serial.print(sensorData[0]);
  Serial.print(" ");
  Serial.println(sensorData[1]);
}

void cross(byte v = COMMON_SPEED)
{
  float err, u, kP = 1, kD = 10, kI = 0.001, i, eold = 0;
  short crossCounter = 0;
  readSensors();
  while(crossCounter < 15)
  {
    readSensors();
    err = sensorData[0] - sensorData[1];
    u = err * kP + (err - eold) * kD;
    i += kI * err;
    motorLeftGo(v - u * 15);
    motorRightGo(v + u * 15);
    eold = err;
    Serial.print(sensorData[0]);
    Serial.print(" ");
    Serial.print(sensorData[1]);
    Serial.print("\t");
    Serial.println(u * 10);
    if(!sensorData[0] && !sensorData[1]) crossCounter++;
    else crossCounter = 0;
  }
  motorLeftGo(0);
  motorRightGo(0);
  delay(100);
  Serial.println("done CROSS");
}

void forward(short sp = COMMON_SPEED)
{
  motorLeftGo(sp);
  motorRightGo(sp);
  delay(600);
  motorLeftGo(0);
  motorRightGo(0);
  delay(100);
  motorLeftGo(2 *sp);
  motorRightGo(-2 * sp);
  delay(1900);
  motorLeftGo(0);
  motorRightGo(0);
  delay(100);
  Serial.println("done step");
}

void turnToLine(short sp = COMMON_SPEED)
{
  int timer = millis();
  while(sensorData[!(sp > 0)] || millis() < timer + 700)
  {
    readSensors();
    motorLeftGo(-sp);
    motorRightGo(sp);
  }
  motorLeftGo(0);
  motorRightGo(0);
  delay(100);
  Serial.println("TURNED");
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
  READED = 6,
  TEST = 10
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
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);

  // set the data rate for the SoftwareSerial port
  Serial3.begin(9600);
  Serial.println("connected myserial");
  sendStatus();
  status = TEST;
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
    Serial.println("went to take");
    status = WAITING_FOR_TAKING;
    sendStatus();
  }
  if(status == WAITING_FOR_TAKING)
  {
    delay(10000);
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
    }
    status = WAITING_FOR_DROPPING;
    Serial.println("DONE REQUEST");
  }
  else if(status == WAITING_FOR_DROPPING)
  {
    sendStatus();
    delay(10000);
    status = DONE;
    Serial.println("DROPPED");
    algorithm = "";
    algorithmToStart = "";
  }
  else if (status == DONE) 
  {
    String c = Serial3.readString();
    if (c != -1) 
    {
      Serial.print("begin reading");
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
  else if(status == TEST)
  {
    // motorLeftGo(100);
    // motorRightGo(100);
    //testSensors();
    // +
    cross();
    forward();
    turnToLine(-COMMON_SPEED);
    turnToLine(-COMMON_SPEED);
    cross();
    forward();
    turnToLine();
    cross();
    forward();
    delay(10000);
  }
}
