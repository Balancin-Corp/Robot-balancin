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


void printValues(String keyword) {
    if (keyword == "angle" || keyword == "all") {//Shows all angle related values
        SerialBT.print("Angle = "); SerialBT.println(KalmanAnglePitch);
        SerialBT.print("AngleOffset = "); SerialBT.println(angleOffset);
        SerialBT.println();
    }
    if (keyword == "pid" || keyword == "all") { //Shows all pid related values
        SerialBT.print("PID_E = "); SerialBT.println(KP1);
        SerialBT.print("PID_D = "); SerialBT.println(KD1);
        SerialBT.print("PID_I = "); SerialBT.println(KI1);
        SerialBT.println();
        SerialBT.print("E = "); SerialBT.println(E1);
        SerialBT.print("IE = "); SerialBT.println(IE1);
        SerialBT.print("dE = "); SerialBT.println(dE1);
        SerialBT.println();   
    }
    if (keyword == "balance" || keyword == "all") {//Shows all balance related values
        SerialBT.println();
    }

    if (keyword == "elapsedtime" || keyword == "all") {//Shows all looptimer related values
        SerialBT.print("elapsedTime = "); SerialBT.print(elapsedTime);SerialBT.println("ms");
    }
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
    //SerialBT adds an space to text, so it's impossible for it to be empty
        if (includedIn("IE", text)) { //Sets integral to zero.
            IE1 = 0;
            return ;
        }   
        if (includedIn("X", text) || includedIn("x", text)) {
            String keywords[5] = {"angle", "pid", "balance", "looptimer", "all"};
            for (int i = 0; i < 5; i++) {
                if (includedIn(keywords[i], text))
                    printValues(keywords[i]);
            }
            return;
        }
        if (includedIn("P", text) || includedIn("p", text)) {
            KP1 = getValue(text);
        }
        if (includedIn("I", text) || includedIn("i", text)) {
            KI1 = getValue(text);
        }
        if (includedIn("D", text) || includedIn("d", text)) {
            KD1 = getValue(text);
        }
        if (includedIn("O", text) || includedIn("o", text)) {
            angleOffset = getValue(text);
        }
        if (includedIn("BC", text) || includedIn("bc", text)) {
            //balanceCL12 = getValue(text);
            //updateBalance(&balanceCL12, &balanceCL1, &balanceCL2);
        }
        if (includedIn("BAC", text) || includedIn("bac", text)) {
            //balanceACL12 = getValue(text);
            //updateBalance(&balanceACL12, &balanceACL1, &balanceACL2);
        }
    }

}