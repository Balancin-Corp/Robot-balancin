#ifndef controlStage_h
#define controlStage_h

#include <Arduino.h>
#include <KalmanAngle.h>
#include <PWM.h>


extern uint32_t LoopTimer;

extern float dt; //The duration of each loop in ms. 

extern float E1;
extern float dE1;
extern float IE1;
extern float KP1;
extern float KI1;
extern float KD1;
extern float PID1;

extern float angleOffset;


extern float E2;
extern float dE2;
extern float IE2;
extern float KP2;
extern float KI2;
extern float KD2;
extern float PID2;
extern float rateYawOffset;

extern float elapsedTime;


inline int clamp(float, float, float);

void updatePID();

void controlStageLoop(void* pvParameters);


#endif