#include <SoftwareSerial.h>

SoftwareSerial mySerial(15, 14); // RX, TX

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.print("\n begin");
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("\n connected");
  
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  while (!mySerial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("\n connected myserial");

}

void loop() 
{ // run over and over
  if (mySerial.available()) 
  {
    Serial.write(mySerial.read());
    Serial.print("imalive ");
  }
}
