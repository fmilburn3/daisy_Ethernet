// -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8
void initConnect() {
  connectServer();
  while (!getServerPort()) {
    if (DEBUG > 1){
      Serial.println("Will try again later...");
    }
    statusLED(1000, 600000);     // Wait 10 minutes, toggling at 1 Hz
  }
  initUDP();
  if (DEBUG > 0){
    Serial.println("connection initialized");
  }
} 
