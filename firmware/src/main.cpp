#include <Arduino.h>
#include <kalmanAngle.h>
#include <controlStage.h>
#include <BluetoothSerial.h>

TaskHandle_t controlStage;

BluetoothSerial SerialBT;

void printValues();
float getValue(String);


void setup() {
  Serial.begin(115200); 
  SerialBT.begin("ESP32");
  //Creates controlStage task
  xTaskCreatePinnedToCore(controlStageLoop, "controlStage", 100000, NULL, 1, &controlStage, 0);               
  delay(500); 

}

//This loop runs on core 1, independently from controlStage task.

void loop() {
  if (SerialBT.available()) {
      String text = SerialBT.readStringUntil('\n');
      //SerialBT adds an space to text, so is impossible for it to be empty
      switch (text[0]) {
        case 'X':
          printValues();
          break;
        case 'O':
          angleOffset = getValue(text);
          break;
        case 'P':
          PID_P = getValue(text);
          break;
        case 'I':
          PID_I = getValue(text);
          break;
        case 'D':
          PID_D = getValue(text);
          break;
      }
  
  }
  
  delay(10);

}
  
void printValues() {

  SerialBT.print("Angle = ");
  SerialBT.println(KalmanAnglePitch);

  SerialBT.print("AngleOffset = ");
  SerialBT.println(angleOffset);


  SerialBT.print("PID_E = ");
  SerialBT.println(PID_P);

  SerialBT.print("PID_D = ");
  SerialBT.println(PID_D);

  SerialBT.print("PID_I = ");
  SerialBT.println(PID_I);
}

float getValue(String text) {
    //Obtains a float inside the string, if there is none returns 0.
    int sgn = 1;
    if (text.indexOf('-')!=-1)
      sgn = -1;
    while (text != "" && !isDigit(text[0]))
            text.remove(0, 1);
    //This function needs to start with a digit, so we removed all the non-digits at the start of the string        
    return (float)(sgn*(text.toFloat()));

}