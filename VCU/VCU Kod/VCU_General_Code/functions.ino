void receiveUARTData() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;
 
    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}


void getUARTData(){
      if (newData == true) {
        Serial.print("This just in ... ");
        Serial.println(receivedChars);
        switch (receivedChars){
            case 'HIGH TEMP':
            Serial3.println('SHUT');
            delay(100);
            Serial.print("Battery will be shutdown!");
            break;
         }
        newData= false;
    }
}
