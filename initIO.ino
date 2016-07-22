// -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8
void initIO(){
  pinMode(STATUS_LED, OUTPUT);                   
  Serial.begin(38400);
  delay(1000); 
  if (DEBUG > 0){
    Serial.println("");
    Serial.println("io initiated");
  }  
  digitalWrite(STATUS_LED, HIGH);                  // IO initialized
}
