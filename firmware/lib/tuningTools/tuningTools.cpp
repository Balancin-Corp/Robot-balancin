#include <tuningTools.h>
BluetoothSerial SerialBT;

void tuningToolsSetup() {
    SerialBT.begin("ESP32");
}



int includedIn(String string1, String string2) {
    if (string2.indexOf(string1) == -1) //If string2 is not included in string1
        return 0;
    return 1;
}


void printValues() {

  SerialBT.print("Angle = "); SerialBT.println(KalmanAnglePitch);

  SerialBT.print("AngleOffset = "); SerialBT.println(angleOffset);
  {
  /*SerialBT.print("M1Voffset = "); SerialBT.println(motor1Voffset);
  
  SerialBT.print("M2Voffset = "); SerialBT.println(motor2Voffset);

  SerialBT.print("Delay M1 = "); SerialBT.println(delayM1);

  SerialBT.print("Delay M2 = "); SerialBT.println(delayM2);*/
  }
  
  SerialBT.print("BalanceCL12 = "); SerialBT.println(balanceCL12);

  SerialBT.print("BalanceACL12 = "); SerialBT.println(balanceACL12);

  SerialBT.print("PID_E = "); SerialBT.println(PID_P);

  SerialBT.print("PID_D = "); SerialBT.println(PID_D);

  SerialBT.print("PID_I = "); SerialBT.println(PID_I);
}



float getValue(String text) {
    //Obtains a float inside the string, if there is none returns 0.
    int sgn = 1;
    if (text.indexOf('-')!=-1) //If text contains '-'
      sgn = -1;
    while (text != "" && !isDigit(text[0]))
            text.remove(0, 1);
    //This function needs to start with a digit, so we removed all the non-digits at the start of the string        
    return (float)(sgn*(text.toFloat()));

}

void tuningToolsInput() {
    if (SerialBT.available()) {
        String text = SerialBT.readStringUntil('\n');
    //SerialBT adds an space to text, so is impossible for it to be empty
    
        if (includedIn("X", text) || includedIn("x", text)) {
            printValues();
            return;
        }
        if (includedIn("P", text) || includedIn("p", text)) {
            PID_P = getValue(text);
        }
        if (includedIn("I", text) || includedIn("i", text)) {
            PID_I = getValue(text);
        }
        if (includedIn("D", text) || includedIn("d", text)) {
            PID_D = getValue(text);
        }
        if (includedIn("O", text) || includedIn("o", text)) {
            angleOffset = getValue(text);
        }
        if (includedIn("BC", text) || includedIn("bc", text)) {
            balanceCL12 = getValue(text);
            updateBalance(&balanceCL12, &balanceCL1, &balanceCL2);
        }
        if (includedIn("BAC", text) || includedIn("bac", text)) {
            balanceACL12 = getValue(text);
            updateBalance(&balanceACL12, &balanceACL1, &balanceACL2);
        }
    }

}