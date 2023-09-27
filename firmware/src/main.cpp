#include <Arduino.h>
#include <controlStage.h>
#include <tuningTools.h>

TaskHandle_t controlStage;


void setup() {
  Serial.begin(115200);
  tuningToolsSetup();
  //Creates controlStage task
  xTaskCreatePinnedToCore(controlStageLoop, "controlStage", 100000, NULL, 1, &controlStage, 0);               
  delay(500); 

}

//This loop runs on core 1, independently from controlStage task.

void loop() {

  switch (plotState) {
      case 0: 
          Serial.println(integratedRatePitch);
          break;
      case 1:
          Serial.println(AnglePitch);
          break;
      case 2:
          Serial.println(KalmanAnglePitch);
          break;
      case 3:
        Serial.println(PID1);
        break;
  }
  tuningToolsInput();
  delay(10);

}
  
