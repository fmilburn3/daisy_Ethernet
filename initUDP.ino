// -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8
void initUDP(){
  udp.begin(8888);
  delay(1000);                                        // let Ethernet stabilize
  if (DEBUG > 1){
    Serial.print("Initialized UDP"); 
  }
}
