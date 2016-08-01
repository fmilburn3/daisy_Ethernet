// -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8
void initEthernet(){
/*
 * Connect to Ethernet with Ethernet.begin
 */
  if (DEBUG > 0){
    Serial.println("attempt to configure Ethernet");
  }
  if (Ethernet.begin(mac) == 0) {
    if (DEBUG > 1){
      Serial.println("\nFailed to configure Ethernet...");
    }
    statusLED(100,-1);                      // blink forever toggling 100 ms    
  }
  delay(1000);                              // Let Ethernet stabilize
}
