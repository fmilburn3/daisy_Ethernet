// -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8
void initIO(){
/*
 * Initiates IO on the G2955
 */
  pinMode(STATUS_LED, OUTPUT);                   
  Serial.begin(38400);
  delay(1000); 
  if (DEBUG > 0){
    Serial.println("\n");
    Serial.println(versionNo);
    Serial.println("IO initiated");
  }  
  digitalWrite(STATUS_LED, HIGH);                  
}
