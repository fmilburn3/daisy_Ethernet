// -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8
void sendData(){
/*
 * Checks serial to see if messages are available from dAISy and sends AIS
 * nmea sentences via UDP to marifact
 */
  static int i = 0;                  // tracks characters read into nmea array

  while (Serial.available()) {       // read incoming NMEA sentences from dAISy       
    if (i < MAXLEN-1) {
      nmea[i] = (char)Serial.read(); // place new chars into nmea[]
    }
    nmea[++i] = 0;                   // increment and store a end of string                                                     
    if (nmea[i-1] == '\n') {         // newline indicates end of NMEA sentence
      if (DEBUG > 1){
        Serial.print(nmea); 
      }   
      statusLED(0,0);                // toggle status LED 
      udp.beginPacket(server, serverPort);      // UDP packet transfer
      udp.write(nmea);
      udp.endPacket();
      i = 0;                         // now set the counter back to 0
      nmea[i] = '\0';                // and set first element of nema to null          
    }                                           
  }
}
