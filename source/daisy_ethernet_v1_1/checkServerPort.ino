// -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8
int checkServerPort(){
//          *********************  N O T   W O R K I N G  *********************
/* Checks to see if the serverPort is still active and returns:
 * 0 = not active
 * 1 = active
 */
  int returnValue = 1; 
  if (DEBUG > 1){
    Serial.println("checkServerPort");
  }
  strcpy(nmea, clientStr5);
  strcat(nmea, ID);
  if (DEBUG > 2){
    Serial.println("nmea");
  }
  client.println(nmea);
  getLine(nmea, MAXLEN);
  char *ptrID;
  ptrID= strstr(nmea, ID);
  if (ptrID == NULL){          // did server return the ID?
    if (DEBUG > 1){
      Serial.println("Server did not return the ID");
    }
    returnValue = 0;
  } 
  return returnValue;
}
