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
  Serial1.begin(9600); // nextion
  Serial2.begin(9600); // bms (baud kontrol edilecek)
  Serial3.begin(9600); // mcu
  //SoftwareSerial dbgSerial(5, 6); dummy serial
}

void sendNextionCmd(String cmd, int value) // nextiona komut yollarken nextion dilinde komut satiri yollamak yetiyor
{
  Serial1.print(cmd);
  Serial1.print(value);
  Serial1.write("\xFF\xFF\xFF"); //3 tane bu 
                                // byte gelmedikce nextion komut almiyor
}

void parseNextionInput(int info, int state) { // nextiondan gelen komutu isler, 
                                              //google docsta yaziyor detaylar
  if (info == 97) {
      if (state == 0) {
        Serial1.print("Sol sinyal kapandi");
        Serial1.print('\n');
      }
      else {
        Serial1.print("Sol sinyal acildi");
        Serial1.print('\n');
      }
    }
       
    if (info == 98) {
      if (state == 0) {
        Serial1.print("Sag sinyal kapandi");
        Serial1.print('\n');
      }
      else {
        Serial1.print("Sag sinyal acildi");
        Serial1.print('\n');
      }
    }
    if (info == 99) {
      if (state == 0) {
        Serial1.print("On far kapandi");
        Serial1.print('\n');
      }
      else {
        Serial1.print("On far acildi");
        Serial1.print('\n');
      }
    }
     if (info == 100) {
      if (state == 0) {
        Serial1.print("Dortlu kapandi");
        Serial1.print('\n');
      }
      else {
        Serial1.print("Dortlu acildi");
        Serial1.print('\n');
      }
    }   
}

void nextionInput() {
  if (Serial1.available() > 0) //serial girisi varsa
  {
    int recieved = Serial1.readBytesUntil('\n', received_data_nextion, 5); // terminating olarak newline yolluyor nextion
    int info = received_data_nextion[0]; // ilk byte info bytei yani neyin acilip kapanacagini veriyor
    int state = received_data_nextion[1];  // ikinci byte ise state, acik kapali
    Serial1.print(info); // debug
    Serial1.print('\n');
    Serial1.print(state);
    Serial1.print('\n'); 
    parseNextionInput(info, state); // nextion komutunu gelen verilere gore isliyor
  }
}

void bmsInput() {

  // if (Serial2.available() > 0) {
    // gelen veriyi isle, bms degiskenlerine veriyi ata
  // }
  bmsDataNextion(bmsVoltage, bmsCurrent, SoH, SoC, bmsTemp);
}

void bmsDataNextion(int bmsVoltage, int bmsCurrent, int SoH, int SoC, int bmsTemp) {
  sendNextionCmd("n4.val=", bmsVoltage);
  sendNextionCmd("x0.val=", bmsCurrent);
  sendNextionCmd("n3.val=", SoH);
  sendNextionCmd("n1.val=", SoC);
  sendNextionCmd("n2.val=", bmsTemp);
}


void loop() {

  nextionInput(); // nextiondan veri al
  bmsInput();
}
