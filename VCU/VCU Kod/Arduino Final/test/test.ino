byte received_data[50];

void setup(){
  Serial1.begin(250000);
  Serial.begin(250000);
}

void loop() {
  if (Serial1.available() > 0) //serial girisi varsa
  {
    Serial.println("al mukaddes");
    Serial1.readBytes(received_data, 50); // terminating olarak newline yolluyor nextion
    Serial.print((char*)received_data);
    //int info = received_data[0];
    //int state = received_data[1]; 
  }



}
