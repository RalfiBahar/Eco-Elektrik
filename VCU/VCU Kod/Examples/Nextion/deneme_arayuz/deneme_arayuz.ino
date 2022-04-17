// sol led sol sinyali, sağ led sağ sinyali temsil eder
// amaç burada nextiondan alınan veriyi digital pinden dışarı vermektir
// nextion veriyi 4 hex byte şeklinde verir.
// bu örnekte sadece ilk byte'ı kontrol etmek yeter ancak 
// aynı mantıkla bütün received_data array'i kontrol edilebilir.

int LED_SOL = 13; //internal
int LED_SAG = 6;
byte received_data[5]; // 5 bytelık yer önceden açmak performansa da yararlı, bugları da azaltır. 

void setup(){
  Serial.begin(9600);
  pinMode(LED_SOL, OUTPUT);
  pinMode(LED_SAG, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) //serial girisi varsa
  {
    int recieved = Serial.readBytesUntil('\n', received_data, 5); // terminating olarak newline yolluyor nextion
    int info = received_data[0];
    int state = received_data[1]; 
    Serial.print(info); 
    Serial.print('\n');
    Serial.print(state);
    Serial.print('\n'); 

    if (info == 97) {
      if (state == 0) {
        Serial.print("Sol sinyal kapandi");
        Serial.print('\n');
      }
      else {
        Serial.print("Sol sinyal acildi");
        Serial.print('\n');
      }
    }
       
    if (info == 98) {
      if (state == 0) {
        Serial.print("Sag sinyal kapandi");
        Serial.print('\n');
      }
      else {
        Serial.print("Sag sinyal acildi");
        Serial.print('\n');
      }
    }
    if (info == 99) {
      if (state == 0) {
        Serial.print("On far kapandi");
        Serial.print('\n');
      }
      else {
        Serial.print("On far acildi");
        Serial.print('\n');
      }
    }
     if (info == 100) {
      if (state == 0) {
        Serial.print("Dortlu kapandi");
        Serial.print('\n');
      }
      else {
        Serial.print("Dortlu acildi");
        Serial.print('\n');
      }
    } 
   }
}
