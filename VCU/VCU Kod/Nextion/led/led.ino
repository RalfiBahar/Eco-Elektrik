int LED = 5;

void setup(){
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) //serial girisi varsa
  {
    int recieved = Serial.parseInt();
    analogWrite(LED, recieved); //serial girisini pine yaz
  }
}
