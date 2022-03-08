int LED_SOL = 13; //internal
int LED_SAG = 6;
byte received_data[4];

void setup(){
  Serial.begin(9600);
  pinMode(LED_SOL, OUTPUT);
  pinMode(LED_SAG, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) //serial girisi varsa
  {
    int recieved = Serial.readBytesUntil('\n', received_data, 4 );
    int info = received_data[0];
    Serial.print(info);
    Serial.print('\n');

    if (info == 1) {
      digitalWrite(LED_SAG, !digitalRead(LED_SAG));
    }

    else if (info == 0) {
      digitalWrite(LED_SOL, !digitalRead(LED_SOL));
    }
  }
}
