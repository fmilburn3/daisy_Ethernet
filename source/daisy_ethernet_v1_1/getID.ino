// -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8
/*
 * Requests an identification string from dAISy (the serial number of the
 * microcontroller
*/
void getID(){
  if (DEBUG > 0){
    Serial.print("Request id from dAISy...  ");
  }  
  Serial.println("&");                   // request ID from dAISy
  static int i = 0;                      // tracks characters read into nmea
  int keepLooping = 1;                   // don't exit until ID is received
  while (keepLooping){
    while (Serial.available()) {         // read incoming from dAISy      
      if (i < MAXLEN-1){
        nmea[i] = (char)Serial.read();   // place new chars into nmea[]
      }
      nmea[++i] = '\0';                  // increment counter, store end of string                                                     
      if (nmea[i-1] == '\n'){            // newline indicates the end of  sentence
        if (nmea[0] == '!'){             // '!' indicates it was a nmea sentence
          i = 0;                         // now set the counter back to 0
          nmea[i] = '\0';                // and set the first element to null 
          Serial.print("&");             // request ID from dAISy again
        }   
        else{                            // it was the ID                                             
          strncpy(ID, nmea, 16);
          keepLooping = 0;
          break;
        }  
      }
    }                                     
  }
  digitalWrite(STATUS_LED, LOW);          // ID obtained
  if (DEBUG > 1){
    Serial.print("  id = ");
    Serial.println(ID);
  }  
}
