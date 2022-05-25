#include <ModbusMaster.h>
#define MAX485_DE      3
#define MAX485_RE_NEG  2
#define CELL_LEN 13 
#define TEMP_LEN 5
#define CELL_ID_LEN 3
#define AH_CUR_PACK_LEN 3
#define SOC_SOH_LEN 2
#define FLAGS_LEN 1


ModbusMaster node;
void preTransmission(){
  digitalWrite(MAX485_RE_NEG, 1);             
  digitalWrite(MAX485_DE, 1);
}

void postTransmission(){
  digitalWrite(MAX485_RE_NEG, 0);
  digitalWrite(MAX485_DE, 0);
}

void setup(){
  pinMode(MAX485_RE_NEG, OUTPUT);
  pinMode(MAX485_DE, OUTPUT);

  digitalWrite(MAX485_RE_NEG, 0);
  digitalWrite(MAX485_DE, 0);

  Serial.begin(38400);             
  node.begin(1, Serial);            

  node.preTransmission(preTransmission);         
  node.postTransmission(postTransmission);
}

int *get_BMS_data(){
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
            Serial.println(j);
           }                       
        }
      }
    }
    Serial.println("Cell Voltages: ");
    for(int k = 0; k < CELL_LEN; k++){
      Serial.print("Cell ");
      Serial.print(k);
      Serial.print(": ");
      Serial.println(cells_voltage[k]);  
    }
    Serial.println();
    Serial.println("Balance Delta (mV) - Low (index) - High (index): ");
    for(int k = 0; k < CELL_ID_LEN; k++){
      Serial.println(cells_id[k]);  
    }
    
    Serial.println();
    Serial.println("Temperatures: ");
    for(int k = 0; k < TEMP_LEN; k++){
      Serial.print("Temp ");
      Serial.print(k);
      Serial.print(": ");
      Serial.println(temperature[k]);  
    }

    Serial.println();
    Serial.println("Pack Data: ");
    for(int k = 0; k < AH_CUR_PACK_LEN; k++){
      if(k == 0){
        Serial.print("Pack Capacity ");
      }
      if(k == 1){
        Serial.print("Pack Current ");
      }
      if(k == 2){
        Serial.print("Pack Voltage ");
      }
      Serial.print(k);
      Serial.print(": ");
      Serial.println(ah_cur_pack[k]);  
    }

    Serial.println();
    Serial.println("Pack State: ");
    for(int k = 0; k < SOC_SOH_LEN; k++){
      if(k == 0){
        Serial.print("State of Charge ");
      }
      if(k == 1){
        Serial.print("State of Health ");
      }
      Serial.print(k);
      Serial.print(": ");
      Serial.print(soc_soh[k]);  
      Serial.println("%");
    }
  delay(200);
  return(BMS_data);
}
