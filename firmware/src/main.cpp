#include <Arduino.h>
#include <kalmanAngle.h>
#include <controlStage.h>

TaskHandle_t controlStage;
TaskHandle_t Task2;

void Task1code( void * pvParameters );
void Task2code( void * pvParameters );

void setup() {
  Serial.begin(115200); 

  xTaskCreatePinnedToCore(controlStageLoop, "Task1", 10000, NULL, 1, &controlStage, 0);               
  delay(500); 

  xTaskCreatePinnedToCore(Task2code, "Task2", 10000, NULL, 1, &Task2, 1);
  delay(500); 
}

//Task2code: blinks an LED every 700 ms
void Task2code( void * pvParameters ){
  Serial.print("Task2 running on core ");
  Serial.println(xPortGetCoreID());

  for(;;){
    Serial.print("Angle pitch = ");
    Serial.println(KalmanAnglePitch);
    delay(500);
    //PID control:

  }
}

void loop() {
  
}