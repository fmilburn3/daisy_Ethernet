// -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8
int getServerPort(){
/*
 * Gets a server and port from marifact and returns the following information:
 *  0 = marifact did not return "200 OK"
 *  1 = All OK
 */
  int returnCode = 1;
  if (DEBUG > 0){
    Serial.println("\ngetServerPort...");
  }
  int numLoops = 0;
  while(serverPort == 0){
    numLoops++;
    static int zeroLength = 0;
    if (client.available() && (zeroLength < 4)) {
      getLine(nmea, MAXLEN);
      if (numLoops == 0){
        // first pass, check to see if "200 OK" is in the string
        char *ptr200;
        ptr200 = strstr(nmea,clientStr4);
        if (ptr200 == NULL){          // did server return "200 OK"?
          if (DEBUG > 1){
            Serial.println("Server did not return 200 OK");
          }
          returnCode = 0;
        } 
      }
      if (strlen(nmea) > 0){
        if (zeroLength < 4) {
          zeroLength = 0;
        }
        if (DEBUG > 2){
          Serial.print("New line: ");
          Serial.println(nmea);
        }
      }
      else {
        zeroLength++;
        if (DEBUG > 2){
          Serial.print("===>  zero length: ");
          Serial.println(zeroLength);
        }
      }
    }
    if (zeroLength == 4) {
      getLine(nmea, MAXLEN);
      convertServerString(nmea,server);
      if (DEBUG > 1) {
        Serial.print("server = ");
        int i;
        for (i = 0; i < 4; i++){
          Serial.print(server[i]);
          Serial.print("  ");
        }
        Serial.println("");
      }
      
      getLine(nmea, MAXLEN);
      serverPort = atoi(nmea);
      if (DEBUG > 1) {
        Serial.print("serverPort = ");
        Serial.println(serverPort);
      }
      zeroLength = 0;
    }                                                          
    // if the server's disconnected, stop the client:
    if (!client.connected()) {
      Serial.println("\nDisconnecting...");
      client.stop();
    }
  }
  return returnCode;
}

// -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8
void convertServerString(char a[], byte num[]) {
/*
 * places 4 numbers from the period separated string (a) into a byte
 * array (num).  For example, if a[] = "123.222.78.9" the byte array
 * becomes num[0] = 123, num[1] = 222, num[2] = 78, num[3] = 9
 */ 
  num[0] = (byte)(atoi(a));               // 1st number - num[0]
  char *ptr1, *ptr2, *ptr3;               // pointers to the '.' in string a
  ptr1 = strchr(a, '.');
  num[1] = (byte)(atoi(ptr1+1));          // 2nd number - num[1]
  if (num[1] > 99) {
    ptr2 = ptr1 + 4;
  }
  else if (num[1] > 9) {
    ptr2 = ptr1 + 3;
  }
  else {
    ptr2 = ptr1 + 2;
  }
  num[2] = (byte)(atoi(ptr2+1));          // 3rd number - num[2]
  ptr3 = strrchr(a, '.');
  num[3] = (byte)(atoi(ptr3+1));          // 4th number - num[3]
}

