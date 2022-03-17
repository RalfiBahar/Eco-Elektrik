// sol led sol sinyali, sağ led sağ sinyali temsil eder
// amaç burada nextiondan alınan veriyi digital pinden dışarı vermektir
// nextion veriyi 4 hex byte şeklinde verir.
// bu örnekte sadece ilk byte'ı kontrol etmek yeter ancak 
// aynı mantıkla bütün received_data array'i kontrol edilebilir.

int LED_SOL = 13; //internal
int LED_SAG = 6;
byte received_data[4]; // 4 bytelık yer önceden açmak performansa da yararlı, bugları da azaltır. 

void setup(){
  Serial.begin(9600);
  pinMode(LED_SOL, OUTPUT);
  pinMode(LED_SAG, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) //serial girisi varsa
  {
    int recieved = Serial.readBytesUntil('\n', received_data, 4 ); // terminating olarak newline yolluyor nextion
    int info = received_data[0]; // bu ornekte ilk byte bize yetiyor
    Serial.print(info); // ne aldıysak bi yazalım dedik
    Serial.print('\n'); 

    if (info == 1) {
      digitalWrite(LED_SOL, !digitalRead(LED_SOL)); // sol ve sağ için ayrı aç/kapat byte'ı yerine toggle ile yaptım (şimdilik) 
    }                                               // daha komplike işlerde "state" tarzı bi değişken yaratılabilir. 

    else if (info == 0) {
      digitalWrite(LED_SOL, !digitalRead(LED_SOL));
    }
  }
}
