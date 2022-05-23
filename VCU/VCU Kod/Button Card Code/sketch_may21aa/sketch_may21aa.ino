const int buttonPin = 2;     
int buttonState = 0; 
int counter = 0;
int prevstate = 0;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  Serial.println(counter);

  if (buttonState == LOW && prevstate == 0) {
      counter++;
      Serial.println("LOW");
      prevstate = 1;
  } else {
      Serial.println("HIGH");
      prevstate = 0;  
  }
  delay(100);
}
