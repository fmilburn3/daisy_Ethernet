// -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8
void getMAC(char aString[], byte mac[]){
/*
 * Generates a MAC for use with Ethernet from a string
 */
  int n = 6;
  stringToBytes(aString, mac, n); 
  mac[0] = 0x00;
  if (DEBUG > 0) {
    Serial.println("generated MAC...");
  }  
  if (DEBUG > 1) {
    int i;
    Serial.print ("  byte mac[");
    Serial.print (n);
    Serial.print("] = ");              
    for (i = 0; i < n; i++) {
      Serial.print(mac[i],HEX);
      Serial.print(" ");
    }
    Serial.println("");
  }  
}
// -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8
int stringToBytes(char aString[], byte someBytes[], int n) {
/*
 * Takes a C string with n*2 characters representing HEX values and store them
 * in a byte array of length n. HEX values A-F may be upper or lower case.  
 * Example: "A1b913512900" and n=6 gives a byte array with these elements:
 * {A1, B9, 13, 51, 29, 0}.  Strings with improper values return error code 1.
*/
  int error = 0;
  int val[n*2];
  int i;
  // convert each character in aString[] into an integer using toascii()
  for (i = 0; i < n*2; i++) {
    int asciiVal = toascii(aString[i]);
    if ((asciiVal > 47) & (asciiVal < 58)) val[i] = asciiVal - 48;      //0-9
    else if ((asciiVal > 96) & (asciiVal <103)) val[i] = asciiVal - 87; //a-f
    else if ((asciiVal > 64) & (asciiVal < 71)) val[i] = asciiVal - 55; //A-F
    else {
      val[i] = 0;
      error = 1;
    }
  }
  // Convert n pairs of integers into HEX bytes and store in someBytes[]
  for (i = 0; i < n; i++) {
    someBytes[i] = (byte) (val[i*2]*16 + val[i*2+1]);   
  }
  return error;
}
