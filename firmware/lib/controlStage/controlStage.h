#ifndef controlStage_h
#define controlStage_h

#include <Arduino.h>
#include <KalmanAngle.h>
#include <PWM.h>

extern float dt; //The duration of each loop in ms. 

extern float E;
extern float dE;
extern float IE;
extern float PID;

extern float PID_E;
extern float PID_dE;
extern float PID_IE;

extern float angleOffset;

void updatePID();

void controlStageLoop(void* pvParameters);


#endif