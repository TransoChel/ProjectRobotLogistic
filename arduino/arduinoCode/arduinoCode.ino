#include <AFMotor.h>

#include <SoftwareSerial.h>

#define S1 1
#define S2 2
#define S3 3

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

}

void cross(byte v)
{
  float err, u, kP = 1, kD = 10, kI = 0.001, i, eold = 0;
  short crossCounter = 0;
  while(crossCounter > 50)
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

void forward(byte sp)
{
  motorLeftGo(sp);
  motorRightGo(sp);
  delay(400);
}

void turnToLine(byte sp)
{

}

void goToNeighbor(short from, short to, short direction, byte sp)
{
	while(direction != to)
	{
		turnToLine(sp);
		if(direction != numberOfDots - 1) direction++;
		else direction = 0;
		while(graf[from][direction] == -69) direction++;
	}
	cross(sp);
	forward(sp);
}
void goTo(byte from, byte to, byte startDirection, byte sp)
{
	for(int i = 0; i < numberOfDots ; i++) writeDebugStreamLine("%d", path[i]);
	short direction = startDirection;
	for(byte i = 0; path[i] != to; i++)
	{
		goToNeighbor(path[i], path[i+1], direction, sp, ss);
		turn(ninety*2);
		direction = path[i];
	}
}

String dataFromComputer = "", path;

enum St : char 
{
  GOING_TO_START = 1,
  WAITING_FOR_TAKING = 2,
  DOING_REQUEST = 3,
  WAITING__FOR_DROPPING = 4,
  DONE = 5,
  READED = 6
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
      if(c != ';')
      {
        dataFromComputer += String(c);
        if (c == 0) 
        {
          Serial.println(dataFromComputer);
          dataFromComputer = "";
        }
      }
      else
      {
        short j = 0;
        for(short i = 0; i < dataFromComputer.length(); i++)
        {
          String nowNumber;
          while(dataFromComputer[i] != ',' || dataFromComputer[i] != ';')
          {
            nowNumber += dataFromComputer[i];
            i++;
          }
          path[j] += atoi(nowNumber.c_str());
          j++;
        }
        status = READED;
      }
    }
    sendStatus();
    Serial.println("reading");
  }
  else if(status == READED)
  {
    sendStatus();
    status = GOING_TO_START;
  }
}
