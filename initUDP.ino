// -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8
void initUDP(){
/*
 * Initiates UDP
 */
  udp.begin(8888);
  delay(1000);                                        // let Ethernet stabilize
  if (DEBUG > 0){
    Serial.println("Initialized UDP"); 
  }
}

