#include <controlStage.h>

uint32_t LoopTimer;

float dt = 4; //The duration of each loop in ms. 

float E = 0;
float dE = 0;
float IE = 0;
float PID = 0;

float PID_P = 0;
float PID_I = 0;
float PID_D = 0;

float angleOffset=-1;

float elapsedTime = 0;
float maxElapsedTime = 0;
float minElapsedTime = 100;

void updatePID() {
    float prevE = E;
    E = KalmanAnglePitch-angleOffset;
    dE = RatePitch;
    IE += E*elapsedTime/1000000; 
    PID = PID_P*E + PID_I*IE + PID_D*dE;
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
        MotorSpeed(1, PID);
        MotorSpeed(2, PID);
        uint32_t finalTime = micros();
        elapsedTime = (finalTime - initialTime)/1000.0;

        if (maxElapsedTime < elapsedTime)
            maxElapsedTime= elapsedTime;

        if (minElapsedTime > elapsedTime)
            minElapsedTime = elapsedTime;

        //Ensurese the loop lasts dt (ms)
        while (micros() - LoopTimer < dt*1000)
            LoopTimer=micros();
        
    }
}