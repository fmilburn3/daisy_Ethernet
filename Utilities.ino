void blinkForever(int delayTime){
/*
 toggles the status LED forever at a regular interval equal to delayTime
*/
  for(;;){
    digitalWrite(STATUS_LED, HIGH);
    delay(delayTime);
    digitalWrite(STATUS_LED, LOW);
    delay(delayTime);
  }
}
// -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8
void getLine(char array[], int length){
/*
 reads incoming serial characters into array[] until carriage return or line
 feed is recognized or no new characters are available
*/
  int i = 0;
  int keepLooping = 1;
  while (keepLooping){
    if (client.available()){
      if (i < length-1){
        array[i] = client.read();
        if (DEBUG > 2){     
          Serial.print(i);
          Serial.print("  ");
          Serial.print(toascii(array[i]));
          Serial.print("  ");
          Serial.print(array[i]);
          Serial.print("  ");
          Serial.println(array);
        }
        if (array[i] == 10 || array[i] == 13){
          array[i] = '\0';
          keepLooping = 0;
        }
        array[++i] = '\0';
      }
    }
    else {
      keepLooping = 0;
    }
  }
}
