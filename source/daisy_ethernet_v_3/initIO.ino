// -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8
void initIO(){
/*
 * Initiates IO on the G2955
 */
  pinMode(STATUS_LED, OUTPUT);                   
  Serial.begin(38400);
  int i = 0;
  for(i = 0; i<3; i++){
    digitalWrite(STATUS_LED,HIGH);
    delay(250);
    digitalWrite(STATUS_LED,LOW);
    delay(250);
  }
  if (DEBUG > 0){
    Serial.println("\n");
    Serial.println(versionNo);
    Serial.println("IO initiated");
  }  
  digitalWrite(STATUS_LED, HIGH);                  
}
