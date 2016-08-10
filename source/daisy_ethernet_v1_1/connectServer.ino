// -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8
void connectServer(){
/*
 * Connect to server using client.connect and present dAISy Ethernet ID
 */
  if (DEBUG > 0){
    Serial.print("connecting to server... ");
  }
  if (client.connect(clientStr0, 80)) {
    strcpy(nmea, clientStr1);              // nmea is used as space to build
    strcat(nmea, ID);                      // the request string to the server
    strcat(nmea, clientStr2);              // clientStrx are global strings 
    if (DEBUG > 2) {
      Serial.println("");
      Serial.println(nmea);               
    }
    client.println(nmea);
    client.println(clientStr3);    
    client.println("");

    if (DEBUG > 0){
      Serial.println("connected");
    }    
  } 
  else {
    if (DEBUG > 0) {
      Serial.println("connection failed"); 
    }
    statusLED(500,-1);                     // blink forever toggling 500 ms
  }
  
}
