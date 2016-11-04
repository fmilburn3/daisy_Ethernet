// -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8

#include <SPI.h>
#include <Ethernet.h>

#define DEBUG       0                // 0 = no debug, 1...3 is increasing debug
#define STATUS_LED  P2_0             // status LED is on port 2.0
#define MAXLEN      120              // maximum length of nmea sentence
#define MAXID       17               // maximum length of dAISy ID
#define CHECK       60000            // time (ms) before connection check

// marifact query strings
const char versionNo[]  = "dAISy Ethernet 1_3";
const char clientStr0[] = "api.marifact.net";
const char clientStr1[] = "GET /ais_sources/initialize/";
const char clientStr2[] = " HTTP/1.1";
const char clientStr3[] = "Host: api.marifact.net";
const char clientStr4[] = "200 OK";
const char clientStr5[] = "api.marifact.net/ais_sources/";

char nmea[MAXLEN];                   // general purpose buffer / char storage
                                     // used mainly for AIS nmea sentences
char ID[MAXID];                      // holds dAISy ID
byte mac[]      = {0x00,0x00,0x00,0x00,0x00,0x00};  // mac formed from dAISy ID
byte server[]   = {0, 0, 0, 0};      // alfa.marifact IP   
int  serverPort = 0;                 // alfa.marifact port

EthernetClient client;               // instantiate Ethernet client 
EthernetUDP udp;                     // instantiate Ethernet UDP      

void setup(){
  initIO();
  getID();
  getMAC(ID, mac);
  initEthernet();
  initConnect();
}
void loop(){ 
  sendData();
}
