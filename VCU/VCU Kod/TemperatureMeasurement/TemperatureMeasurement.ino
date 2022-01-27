#include <math.h>
#include <SoftwareSerial.h>

SoftwareSerial Serial2(3, 6);
#define LEDPIN 2

void setup()
{
    pinMode(LEDPIN, OUTPUT);
    Serial.begin(9600);
    Serial2.begin(9600);
}

double getTemperature(int analog)
{
    double temp = log(((10240000 / analog) - 10000));
    temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * sq(temp))) * temp);
    temp -= 273.15;
    return (temp);
}

boolean checkTemperature(){
  int analogValue = analogRead(A0);
  double temperature = getTemperature(analogValue);
  if(temperature >= 40){
    return false
  }
  return true
}

void loop()
{
    Serial2.println(checkTemperature()); //sends false to BMS if temperature levels get higher than 40 degrees celcius
    delay(200);
}
