byte received_data_nextion[5]; // 5 bytelık yer önceden açmak performansa da yararlı, bugları da azaltır. 
                      // bu nextiondan gelecek veri için

byte received_data_mcu[5]; // bu denenecek

byte received_data_bms[100]; // bmsten gelen veri periodic oldugundan hepsi olacak

// comment olarak nextiondaki object idler eklendi
int bmsTemp; // n2
int SoC; // n1
int SoH; // n3
int bmsCurrent; // x0
int bmsVoltage; // n4



void setup(){
  Serial.begin(9600); // nextion
  Serial1.begin(9600); // bms (baud kontrol edilecek)
  Serial2.begin(9600); // mcu
  //SoftwareSerial dbgSerial(5, 6); dummy serial
}

void sendNextionCmd(String cmd) // nextiona komut yollarken nextion dilinde komut satiri yollamak yetiyor
{
  Serial.print(cmd);
  Serial.write("\xFF\xFF\xFF"); //3 tane bu 
                                // byte gelmedikce nextion komut almiyor
}

void parseNextionInput(int info, int state); { // nextiondan gelen komutu isler, 
                                              //google docsta yaziyor detaylar
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

void nextionInput() {
  if (Serial.available() > 0) //serial girisi varsa
  {
    int recieved = Serial.readBytesUntil('\n', received_data_nextion, 5); // terminating olarak newline yolluyor nextion
    int info = received_data_nextion[0]; // ilk byte info bytei yani neyin acilip kapanacagini veriyor
    int state = received_data_nextion[1];  // ikinci byte ise state, acik kapali
    Serial.print(info); // debug
    Serial.print('\n');
    Serial.print(state);
    Serial.print('\n'); 
    parseNextionInput(info, state); // nextion komutunu gelen verilere gore isliyor
  }
}

void bmsInput() {

  if (Serial1.available() > 0) {
    // gelen veriyi isle, bms degiskenlerine veriyi ata
  }
  bmsDataNextion(int bmsVoltage, int bmsCurrent, int SoH, int SoC, int bmsTemp)
}

void bmsDataNextion(int bmsVoltage, int bmsCurrent, int SoH, int SoC, int bmsTemp) {
  sendNextionCmd("n4.val=%i", bmsVoltage);
  sendNextionCmd("x0.val=%i", bmsCurrent);
  sendNextionCmd("n3.val=%i", SoH);
  sendNextionCmd("n1.val=%i", SoC);
  sendNextionCmd("n2.val=%i", bmsTemp);
}


void loop() {

  nextionInput(); // nextiondan veri al
  bmsInput();
}
