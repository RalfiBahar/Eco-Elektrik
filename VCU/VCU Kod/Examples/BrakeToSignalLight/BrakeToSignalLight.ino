const int SWITCH_PIN = 7;
const int LEFT_SIGNAL_LED_PIN = 12;
const int RIGHT_SIGNAL_LED_PIN = 13;

void setup() {
  Serial.begin(9600);
  pinMode(SWITCH_PIN, INPUT);
  pinMode(LEFT_SIGNAL_LED_PIN, OUTPUT);
  pinMode(RIGHT_SIGNAL_LED_PIN, OUTPUT);
}
 
void loop() {
  delay(50);
  if (digitalRead(SWITCH_PIN) == HIGH)
  {
    Serial.println("Braked: Blinking signal lights.");
    digitalWrite(LEFT_SIGNAL_LED_PIN, HIGH);
    digitalWrite(RIGHT_SIGNAL_LED_PIN, HIGH);

  }
 
  else
  {
    Serial.println("Not braked");
    digitalWrite(LEFT_SIGNAL_LED_PIN, LOW);
    digitalWrite(RIGHT_SIGNAL_LED_PIN, LOW);
  }
   

}
