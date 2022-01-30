#include <TinyGPS++.h>
#include <SoftwareSerial.h>

TinyGPSPlus gps;
SoftwareSerial gpsSerial(3, 6);
const int increaseButtonPIN = 2;
int speedValue = 0;
int actualSpeed = 0;

void setup()
{
    pinMode(increaseButtonPIN, INPUT);
    Serial.begin(9600);
    Serial2.begin(9600);
}

void loop()
{
    getSpeed();
    String msg = "Current speed of the car: " + (actualSpeed);
    Serial.println(msg);
    boolean increseButtonPressed = digitalRead(BUTTON);
    if (increseButtonPressed == HIGH)
    {
        speedValue += 5;
        String serialMessage1 = "The speed value of the car is " + String(speedValue);
        getSpeed();
        String serialMessage2 = "The actual speed of the car is " + String(actualSpeed);
        Serial.println(serialMessage1);
        Serial.println(serialMessage2);
    }

    boolean decreaseButtonPressed = digitalRead(BUTTON);
    if (decreaseButtonPressed == HIGH)
    {
        if (speedValue >= 5)
        {
            speedValue -= 5;
            String serialMessage1 = "The speed value of the car is " + String(speedValue);
            getSpeed();
            String serialMessage2 = "The actual speed of the car is " + String(actualSpeed);
            Serial.println(serialMessage1);
            Serial.println(serialMessage2);
        }
    }
    gpsCheck(1000);
}

void getSpeed()
{
    if (gps.speed.isValid())
    {
        actualSpeed = gps.speed.kmph();
    }
    else
    {
        Serial.println("GPS Error: Please Check the Antennaaa!")
    }
}

void gpsCheck(unsigned long ms)
{
    unsigned long start = millis();
    do
    {
        while (gpsSerial.available())
            gps.encode(gpsSerial.read());
    } while (millis() - start < ms);
}
