#include <ModbusRtu.h>

byte received_data[500];
uint16_t modbus_array[] = {0,0,0};    //Array initilized with three 0 values
Modbus bus;                          
void setup(){
  Serial2.begin(9600);
  Serial.begin(9600);
  bus = Modbus(1,1,4);            //Modbus slave ID as 1 and 1 connected via RS-485 and 4 connected to DE & RE pin of RS-485 Module 
  bus.begin(9600);                //Modbus slave baudrate at 9600
}

void loop() {
  bus.poll(modbus_array,sizeof(modbus_array)/sizeof(modbus_array[0]));
  Serial.println(sizeof(modbus_array));
  /*if (Serial2.available() > 0) //serial girisi varsa
  {
    Serial.print("deneme\n");
  }
  Serial.print("gelmiyor\n");*/

}
