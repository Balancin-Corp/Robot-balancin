#include <controlStage.h>

uint32_t LoopTimer;

float dt = 4; //The duration of each loop in ms. 

float E1 = 0;
float dE1 = 0;
float IE1 = 0;
float KP1 = 0;
float KI1 = 0;
float KD1 = 0;
float PID1 = 0;


float angleOffset=1;

float E2 = 0;
float dE2 = 0;
float IE2 = 0;
float KP2 = 0;
float KI2 = 0;
float KD2 = 0;
float PID2 = 0;

float rateYawOffset = 0;

float elapsedTime = 0;

inline int clamp(float min, float val, float max) {
    if (val < min) return min;
    if (val > max) return max;
    else return val;
}

void updatePID() {
    float prevE1 = E1;
    E1 = KalmanAnglePitch-angleOffset;
    dE1 = RatePitch;
    IE1 += E1*elapsedTime/1000000; 
    PID1 = clamp(-PWMscale, KP1*E1 + KI1*IE1 + KD1*dE1, PWMscale);

    float prevE2 = E2;
    E2 = RateYaw - rateYawOffset;
    dE2 = (E2-prevE2)/elapsedTime;
    IE2 += E2*elapsedTime/1000000;
    PID2 = KP2*E2 + KI2*IE2 + KD2*dE2; 
}


void controlStageLoop(void* pvParameters) {
    kalmanAngleSetup();
    PWMsetup();
    //control loop
    LoopTimer = micros();
    while (1) {
        uint32_t initialTime = micros();
        updateKalmanAngle();
        updatePID();

        MotorSpeed(chM1_A, chM1_B, PID1);
        MotorSpeed(chM2_A, chM2_B, PID1);


        uint32_t finalTime = micros();
        elapsedTime = (finalTime - initialTime)/1000.0;
        //Ensurese the loop lasts dt (ms)
        while (micros() - LoopTimer < dt*1000)
            LoopTimer=micros();
        
    }
}