#import "imports.ino"
#import "variables.ino"

SoftwareSerial Serial2(7, 2); // MCU
SoftwareSerial Serial3(3, 6); // BMS

void setup()
{
  Serial.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600); 
}

void loop()
{
    receiveUARTData();
    getUARTData();
    delay(loopDelay);
}
