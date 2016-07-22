// -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8
void getServerPort(){
  Serial.begin(38400);
  Serial.println("\ngetServerPort...");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("\nFailed to configure Ethernet...");
    while(true);                            // No point in carrying on          // ??????? status LED not set yet
  }

  delay(1000);                              // Let Ethernet stabilize
   
  if (DEBUG){
    Serial.println("Configured Ethernet, attempt to connect...");
  }
  if (client.connect("api.marifact.net", 80)) {
    char clientStr1[] = "GET /ais_sources/initialize/";
    char clientStr2[] = " HTTP/1.1";
    strcpy(nmea, clientStr1);
    strcat(nmea, ID);
    strcat(nmea, clientStr2);
    Serial.println(nmea); 
    // -------------------------------------------------------------------- abuse of nmea ?????????????????????
    client.println(nmea);
    client.println("Host: api.marifact.net");    
    client.println("");

    Serial.println("Connected and made a HTTP request...");                                                         // <----
  } 
  else {
    Serial.println("connection failed");
  }
  while(serverPort == 0){
    // Look for 4 zero length strings in a row
    // ---------------------------------------------------------- check for 200 OK
    static int zeroLength = 0;
    if (client.available() && (zeroLength < 4)) {
      getLine(nmea, MAXLEN);
      if (strlen(nmea) > 0){
        if (zeroLength < 4) {
          zeroLength = 0;
        }
        //Serial.print("New line: ");
        //Serial.println(nmea);
      }
      else {
        zeroLength++;
        //Serial.print("===>  zero length: ");
        //Serial.println(zeroLength);
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
/*                                                              Should I have removed this ???????  
    // if the server's disconnected, stop the client:
    if (!client.connected()) {
      Serial.println("\nDisconnecting...");
      client.stop();
    }
*/
  }
}

// -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8
void convertServerString(char a[], byte num[]) {
  // places 4 numbers from the period separated string (a) into a byte
  // array (num).  For example, if a[] = "123.222.78.9" the byte array
  // becomes num[0] = 123, num[1] = 222, num[2] = 78, num[3] = 9
  
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
