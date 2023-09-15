#ifndef controlStage_h
#define controlStage_h

#include <Arduino.h>
#include <KalmanAngle.h>
#include <PWM.h>


extern uint32_t LoopTimer;

extern float dt; //The duration of each loop in ms. 

extern float E;
extern float dE;
extern float IE;
extern float PID;

extern float PID_P;
extern float PID_I;
extern float PID_D;

extern float angleOffset;

extern float elapsedTime;
extern float maxElapsedTime;
extern float minElapsedTime;

void updatePID();

void controlStageLoop(void* pvParameters);


#endif