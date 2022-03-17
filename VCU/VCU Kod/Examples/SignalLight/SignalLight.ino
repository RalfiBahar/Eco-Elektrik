#include <math.h>
#include <SoftwareSerial.h>

const int BUTTON_PIN = 2;
const int LED_PIN = 3;
int buttonState = 0;

void setup()
{
    pinMode(BUTTON_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    buttonState = digitalRead(BUTTON);
    if (buttonState == HIGH)
    {
        digitalWrite(LED_PIN, HIGH);
        delay(500);
        digitalWrite(LED_PIN, LOW);
        delay(500);
        digitalWrite(LED_PIN, HIGH);
    }
    else
    {
        digitalWrite(LED_PIN, LOW);
    }
}
