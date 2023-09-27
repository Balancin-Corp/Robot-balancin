#include <tuningTools.h>
BluetoothSerial SerialBT;

String strList[] = {"p1", "p2", "i1", "i2", "d1", "d2", "o1", "o2"};
float* val[] = {&KP1, &KP2, &KI1, &KI2, &KD1, &KD2, &angleOffset, &rateYawOffset};

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
        SerialBT.print("SerialPlot = "); SerialBT.println(plotState);
        SerialBT.println();
    }
    if (keyword == "pid1" || keyword == "all") { //Shows all pid related values
        SerialBT.print("KP1 = "); SerialBT.println(KP1);
        SerialBT.print("KI1 = "); SerialBT.println(KI1);
        SerialBT.print("KD1 = "); SerialBT.println(KD1);
        SerialBT.println();
        SerialBT.print("E1 = "); SerialBT.println(E1);
        SerialBT.print("IE1 = "); SerialBT.println(IE1);
        SerialBT.print("dE1 = "); SerialBT.println(dE1);
        SerialBT.println();   
    }
    if (keyword == "pid2" || keyword == "all") { //Shows all pid related values
        SerialBT.print("KP2 = "); SerialBT.println(KP2);
        SerialBT.print("KI2 = "); SerialBT.println(KI2);
        SerialBT.print("KD2 = "); SerialBT.println(KD2);
        SerialBT.println();
        SerialBT.print("E2 = "); SerialBT.println(E2);
        SerialBT.print("IE2 = "); SerialBT.println(IE2);
        SerialBT.print("dE2 = "); SerialBT.println(dE2);
        SerialBT.println();   
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
        if (includedIn("ri1", text)) { //Sets integral to zero.
            IE1 = 0;
            return ;
        }
        else if (includedIn("ri2", text)) { //Sets integral to zero.
            integratedRatePitch = 0;
            return ;
        }   
        else if (includedIn("X", text) || includedIn("x", text)) {
            String keywords[5] = {"angle", "pid1", "pid2", "all"};
            for (int i = 0; i < 5; i++) {
                if (includedIn(keywords[i], text))
                    printValues(keywords[i]);
            }
            return;
        }
        else if (includedIn("sp", text)) {
            text.remove(0, 2);
            plotState = getValue(text);
        }
        else
            for (int i = 0; i <8; i++) {
                if (includedIn(strList[i], text)) {
                    text.remove(0, 2);
                    *(val[i]) = getValue(text);
                    break;
                }
            }


    }
}