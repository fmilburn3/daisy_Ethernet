// -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8
void statusLED(int toggleTime, long delayTime){
/*
 * toggleTime is the interval (ms) between toggles
 * delayTime delays everything for a specified length of time where
 *    -x  (any negative number) delays forever - i.e. endless blinking loop
 *     0  toggles the LED from present state and immediately returns
 *        (toggleTime can be any value)
 *    +x  delays for x milliseconds and then returns
 *
 * Note: delayTime must be positive and toggleTime should be less than delayTime
 */
  static int toggle = 0;
  if (delayTime == 0){                    // toggle once
    toggle = !toggle;
    digitalWrite(STATUS_LED, toggle);
  }
  else if (delayTime > 0) {               // toggle for a fixed amount of time
    unsigned long stopTime = millis() + delayTime;
    while (millis() < stopTime){
      toggle = !toggle;
      digitalWrite(STATUS_LED, toggle);
      delay(toggleTime);
    }
  }
  else {                                  // negative number - toggle forever
    for(;;){
      toggle = !toggle;
      digitalWrite(STATUS_LED, toggle);
      delay(toggleTime);
    }
  }
}
// -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8
void getLine(char array[], int length){
/*
 * reads incoming serial characters into array[] until carriage return or line
 * feed is recognized or no new characters are available.  length is the
 * maximum length of the array.
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
