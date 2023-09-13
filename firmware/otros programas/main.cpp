#include <Arduino.h>
#include <kalmanAngle.h>
#include <controlStage.h>

TaskHandle_t controlStage;
TaskHandle_t Task2;


void Task1code( void * pvParameters );
void Task2code( void * pvParameters );

void setup() {
  Serial.begin(115200); 

  //Creates controlStage task
  xTaskCreatePinnedToCore(controlStageLoop, "controlStage", 100000, NULL, 1, &controlStage, 0);               
  delay(500); 

}

//This loop runs on core 1, independently from controlStage task.

void loop() {

  
}
  
