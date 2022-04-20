const int BUTTON_PIN = 2;
const int LED_PIN = 13;
int buttonState = 0;

void setup()
{
    pinMode(BUTTON_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    buttonState = digitalRead(BUTTON_PIN);
    if (buttonState == HIGH)
    {
        digitalWrite(LED_PIN, HIGH);
        Serial.print("high\n");
        delay(100);
    }
    else
    {
        digitalWrite(LED_PIN, LOW);
        Serial.print("low\n");
        delay(100);
    }
}
