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
        case 'B':
          balanceCL12 = getValue(text);
          if (balanceCL12 <=0) balanceCL12 = 1;
          if (balanceCL12 >=1) { //If balance12 >=1, then M1 will receive more voltage than M2
            balanceCL1 = 1;
            balanceCL2 = balanceCL1/balanceCL12;
          }
          else if (balanceCL12<1) {
            balanceCL2 = 1;
            balanceCL1 = balanceCL2*balanceCL12;
          }
          break;
        case 'b':
          balanceACL12 = getValue(text);
          if (balanceACL12 <=0) balanceACL12 = 1;
          if (balanceACL12 >=1) { //If balance12 >=1, then M1 will receive more voltage than M2
            balanceACL1 = 1;
            balanceACL2 = balanceACL1/balanceACL12;
          }
          else if (balanceACL12<1) {
            balanceACL2 = 1;
            balanceACL1 = balanceACL2*balanceACL12;
          }
          break;


        {/*case 'A':
          motor1Voffset = getValue(text);
          break;
        case 'B':
          motor2Voffset = getValue(text);
          break;
        case 'a':
          delayM1 = (int)(getValue(text));
          break;
        case 'b':
          delayM2 = (int)(getValue(text));
          break;*/}
      }
  
  }
  
  delay(10);

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
    if (text.indexOf('-')!=-1)
      sgn = -1;
    while (text != "" && !isDigit(text[0]))
            text.remove(0, 1);
    //This function needs to start with a digit, so we removed all the non-digits at the start of the string        
    return (float)(sgn*(text.toFloat()));

}