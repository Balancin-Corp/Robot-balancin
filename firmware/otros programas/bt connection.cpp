#include <Arduino.h>
#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

String text;

float getValue(String text) {
    //Obtains a float inside the string, if there is none returns 0.
    while (text != "" && (!isDigit(text[0]) || text[0] != '-'))
            text.remove(0, 1);
    //This function needs to start with a digit, so we removed all the non-digits at the start of the string        
    return (float)(text.toFloat());

}

void setup() {
    Serial.begin(115200);
    SerialBT.begin("ESP32");
    
}

void loop() {
    if (SerialBT.available()) {
        text = SerialBT.readStringUntil('\n');

        //For some reason, SerialBT adds an space at the end of text,
        //so we delete it:
        text.remove(text.length()-1,1); 
        Serial.println(text);
        Serial.println(getValue(text));
        Serial.println(text);
    }
    delay(10);
}