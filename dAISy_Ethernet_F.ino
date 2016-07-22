// -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8
/*
  LED meaning
   * LED on during startup - The adapter is trying to configuring itself
     (usually approximately 1 sec)
   * LED briefly off during startup - The adapter configured itself and is
     trying to configure Ethernet
   * Rapid regular (10 Hz) flashes following startup - The adapter was unable to
     configure Ethernet
   * Irregular flashes - Startup successful and a NMEA sentence was sent to the
     W5500 module
   * Frozen LED on or off - The adapter has lost the Ethernet connection and is
     trying to recover
*/

#include <SPI.h>
#include <Ethernet.h>

#define DEBUG       2                // 0 = no debug, 1...3 is increasing debug
#define STATUS_LED  P2_0
#define MAXLEN      100              // maximum length of nmea sentence
#define MAXID       17               // maximum length of dAISy ID

char nmea[MAXLEN];                   // general purpose buffer but mainly used
                                     // for handling AIS nmea sentences
char ID[MAXID];                      // holds dAISy ID
byte mac[]      = {0x00,0xB9,0x13,0x51,0x29,0x00};
byte server[]   = {0, 0, 0, 0};      // alfa.marifact IP   
int  serverPort = 0;                 // alfa.marifact port

EthernetClient client;               // Initialize the Ethernet client library
EthernetUDP udp;                     // Initialize the Ethernet UDP library        ?????????? on same tme as client?

void setup(){
  initIO();
  getDaisyID();
  getMAC(ID, mac, 6);
  getServerPort();
  initUDP();
}
void loop(){  
  static int i = 0;                                   // tracks characters read into the nmea array
  static int blinkSentence = 0;

  while (Serial.available()) {                        // read incoming NMEA sentences from dAISy       
    if (i < MAXLEN-1) {
      nmea[i] = (char)Serial.read();                  // place new chars into nmea[]
    }
    nmea[++i] = 0;                                    // increment the counter and store a end of string                                                     
    if (nmea[i-1] == '\n') {                          // newline indicates the end of the NMEA sentence
      if (DEBUG) Serial.print(nmea);                  // debug print of sentence to serial monitor
      blinkSentence = !blinkSentence;
      digitalWrite(STATUS_LED, blinkSentence);        // toggle the status LED for successful NMEA sentence
      udp.beginPacket(server, serverPort);            // UDP packet transfer
      udp.write(nmea);
      udp.endPacket();
      i = 0;                                          // now set the counter back to 0
      nmea[i] = '\0';                                 // and initialize the first element of nema to null          
    }                                           
  }
}




