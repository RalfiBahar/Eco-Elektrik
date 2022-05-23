#include <ModbusMaster.h>
#define MAX485_DE      3
#define MAX485_RE_NEG  2

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

void loop(){
  uint8_t j;
  uint16_t cells_voltage[13];
  int16_t temperature[5];
  int32_t battery_pack_voltage[1];
  uint16_t soc_soh[2];
  uint16_t flags[1];


  
  uint8_t temp_result = node.readHoldingRegisters(14, 5);
  if (temp_result == node.ku8MBSuccess)
    {
      for (j = 0; j < 5; j++)
      {
        temperature[j] = node.getResponseBuffer(j);
      }
    }
  
  uint8_t cells_result = node.readHoldingRegisters(1, 13);
  /*
  Serial.print("No: "); //General State Print
  Serial.print(node.ku8MBSuccess, HEX);
  Serial.println(result,HEX);
  */
  if (cells_result == node.ku8MBSuccess)
  {
    for (j = 0; j < 13; j++)
    {
      cells_voltage[j] = node.getResponseBuffer(j);

    }
  }

    
  uint8_t pack_voltage_result = node.readHoldingRegisters(32, 1);
  if (pack_voltage_result == node.ku8MBSuccess)
    {
      for (j = 0; j < 1; j++)
      {
        battery_pack_voltage[j] = node.getResponseBuffer(j);
      }
    }

  uint8_t soc_soh_result = node.readHoldingRegisters(36, 2);
  if (soc_soh_result == node.ku8MBSuccess)
    {
      for (j = 0; j < 1; j++)
      {
        soc_soh[j] = node.getResponseBuffer(j);
      }
    }

  uint8_t flags_result = node.readHoldingRegisters(38, 1);
  if (flags_result == node.ku8MBSuccess)
  {
    for (j = 0; j < 13; j++)
    {
      flags[j] = node.getResponseBuffer(j);
    }
  }

  
  delay(200);
}

int[] flag_checker(uint16_t flags){
  int flagIndexes[16];
  int j = 0;
  for(int i = 0; i < 16; i++){
    if(bitRead(flags, i) == 1){
        flagIndexes[j] = i;
        j++;
      }
  }
  return flagIndexes;
}
