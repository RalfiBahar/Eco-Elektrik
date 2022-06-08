#include <Serial_CAN_Module.h>
#include <ModbusMaster.h>
#define MAX485_DE      3
#define MAX485_RE_NEG  2
#define CELL_LEN 13 
#define TEMP_LEN 5
#define CELL_ID_LEN 3
#define AH_CUR_PACK_LEN 3
#define SOC_SOH_LEN 2
#define FLAGS_LEN 1

Serial_CAN can;

#define MCU_TX  18          
#define MCU_RX  19       

unsigned long id = 0;
unsigned char dta[8];

int speedRequested = 0;

int speedIncreaseButtonPin = 0;
int speedIncreaseButtonState = 0;
int speedIncreaseButtonPrevState = 0;

int speedDecreaseButtonPin = 0;
int speedDecreaseButtonState = 0;
int speedDecreaseButtonPrevState = 0;

int speedResetButtonPin = 0;
int speedResetButtonState = 0;
int speedResetButtonPrevState = 0;

boolean ignition = false;
int actualSpeed = 0;

int totalVoltage = 0;
boolean shutSystem = false;

int delayTime = 200;

ModbusMaster node;

void preTransmission(){
  digitalWrite(MAX485_RE_NEG, 1);             
  digitalWrite(MAX485_DE, 1);
}

void postTransmission(){
  digitalWrite(MAX485_RE_NEG, 0);
  digitalWrite(MAX485_DE, 0);
}

void setup() {
  pinMode(speedIncreaseButtonPin, INPUT_PULLUP);
  pinMode(speedDecreaseButtonPin, INPUT_PULLUP);
  pinMode(speedResetButtonPin, INPUT_PULLUP);
  
  pinMode(MAX485_RE_NEG, OUTPUT);
  pinMode(MAX485_DE, OUTPUT);
  digitalWrite(MAX485_RE_NEG, 0);
  digitalWrite(MAX485_DE, 0);

  Serial.begin(38400);             
  can.begin(MCU_TX, MCU_RX, 9600);
    
  node.begin(1, Serial);            
  node.preTransmission(preTransmission);         
  node.postTransmission(postTransmission);
}

void loop() {

  if(shutSystem){
     send_data_MCU(0, 0);
     while(1);
  }
  check_buttons();
  
  send_data_MCU(speedRequested, ignition);
  get_data_MCU();

  send_data_NEXTION(speedRequested, actualSpeed, totalVoltage);
  get_data_NEXTION();

  get_data_BMS();

  delay(delayTime);
}

void check_buttons(){
  //Speed Increase Check
  speedIncreaseButtonState = digitalRead(speedIncreaseButtonPin);
  if (speedIncreaseButtonState == LOW && speedIncreaseButtonPrevState == 0) {
      speedRequested++;
      //Serial.println("LOW");
      speedIncreaseButtonPrevState = 1;
  } else {
      //Serial.println("HIGH");
      speedIncreaseButtonPrevState = 0;  
  }

  //Speed Decrease Check
  speedDecreaseButtonState = digitalRead(speedDecreaseButtonPin);
  if (speedDecreaseButtonState == LOW && speedDecreaseButtonPrevState == 0) {
      speedRequested--;
      speedDecreaseButtonPrevState = 1;
  } else {
      speedDecreaseButtonPrevState = 0;  
  }

  //Speed Reset Check
  speedResetButtonState = digitalRead(speedResetButtonPin);
  if (speedResetButtonState == LOW && speedResetButtonPrevState == 0) {
      speedRequested = 0;
      speedResetButtonPrevState = 1;
  } else {
      speedResetButtonPrevState = 0;  
  }
}

void get_data_BMS(){
  uint16_t cells_voltage[CELL_LEN];
  uint8_t cell_ind = 0; 
  
  uint16_t cells_id[CELL_ID_LEN];
  uint8_t id_ind = 0;
  
  int16_t temperature[TEMP_LEN];
  uint8_t temp_ind = 0;
  
  int32_t ah_cur_pack[AH_CUR_PACK_LEN];
  uint8_t ah_cur_pack_ind = 0;
  
  uint16_t soc_soh[SOC_SOH_LEN];
  uint8_t soc_soh_ind = 0;
  
  uint16_t flags[FLAGS_LEN];
  uint8_t flags_ind = 0;

  int BMS_data[] = [cells_voltage, cells_id, temperature, ah_cur_pack, soc_soh, flags]

  uint8_t result = node.readHoldingRegisters(1, 41);
  if (result == node.ku8MBSuccess)
    {
      for (int j = 0; j < 41; j++)
      {
        if(j + 1 != 19 or j + 1 != 20 or j + 1 != 21 or j + 1 != 22 or j + 1 != 23 or j + 1 != 27 or j + 1 != 31 or j + 1 != 29 or j + 1 != 32 or j + 1 != 33 or j + 1 != 34 or j + 1 != 35 or j + 1 != 39 or j + 1 != 40 or j + 1 != 41){
          if(j < 13){
              cells_voltage[cell_ind] = node.getResponseBuffer(j);
              cell_ind++;
            }
          else if(j >= 13 && j < 18){
              temperature[temp_ind] = node.getResponseBuffer(j);
              temp_ind++; 
           }
          else if(j >= 23 && j < 26){
              cells_id[id_ind] = node.getResponseBuffer(j);
              id_ind++; 
           }    
           else if(j >= 27 && j < 31){
              ah_cur_pack[ah_cur_pack_ind] = node.getResponseBuffer(j);
              ah_cur_pack_ind++; 
           }
            else if(j >= 35 && j < 37){
              soc_soh[soc_soh_ind] = node.getResponseBuffer(j);
              soc_soh_ind++; 
           }
           else if(j >= 37 && j < 38){
              flags[flags_ind] = node.getResponseBuffer(j);
              flags_ind++; 
           }
           else{
            //Serial.println(j);
           }                       
        }
      }
    }
    int currentTotalVoltage = 0;
    for(int l = 0; l < CELL_LEN; l++){
        currentTotalVoltage += cells_voltage[l];
    }
    totalVoltage = currentTotalVoltage;

    if(bitRead(flags, 16 - 2) == 1 or bitRead(flags, 16 - 3) == 1 or bitRead(flags, 16 - 4) == 1 or bitRead(flags, 16 - 5) == 1){
        shutSystem = true;
      }
}

void send_data_MCU(){
  //send(unsigned long id, byte ext, byte rtrBit, byte len, const byte *buf);
  can.send(0x55, 0, 0, 8, requestedSpeed); 
}

void get_data_MCU(){
  can.recv(&id, dta)
}
