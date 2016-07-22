// -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8
void getDaisyID(){
  if (DEBUG > 0){
    Serial.print("Request id from dAISy...  ");
  }  
  Serial.println("I");                             // request ID from dAISy
  static int i = 0;                                // tracks characters read into the nmea array
  int keepLooping = 1;                             // don't exit until a valid ID is received - ********************** make sure it is 16 characters long.......
  while (keepLooping){
    while (Serial.available()) {                   // read incoming from dAISy      
      if (i < MAXLEN-1){
        nmea[i] = (char)Serial.read();             // place new chars into nmea[]
      }
      nmea[++i] = '\0';                            // increment the counter and store a end of string                                                     
      if (nmea[i-1] == '\n'){                      // newline indicates the end of the sentence
        if (nmea[0] == '!'){                       // it was a nmea sentence
          i = 0;                                   // now set the counter back to 0
          nmea[i] = '\0';                          // and initialize the first element of nema to null 
          Serial.print("I");                       // request ID from dAISy again
        }   
        else{
          strncpy(ID, nmea, 16);
          keepLooping = 0;
          break;
        }  
      }
    }                                              // TO DO:  Check if this loop can get stuck - put in a timer
  }
  digitalWrite(STATUS_LED, LOW);                   // ID obtained
  if (DEBUG > 0){
    Serial.print("id = ");
    Serial.println(ID);
  }  
}
