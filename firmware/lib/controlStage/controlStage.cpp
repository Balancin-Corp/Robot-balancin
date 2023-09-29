#include <controlStage.h>

uint32_t LoopTimer;

float dt = 4; //The duration of each loop in ms. 


//PID 1 (Tilt angle)
float E1 = 0;
float dE1 = 0;
float IE1 = 0;
float KP1 = 0;
float KI1 = 0;
float KD1 = 0;
float PID1 = 0;
float angleOffset = 1;
float PID1_gain = 1; 

//PID2 (Yaw rate)
float E2 = 0;
float dE2 = 0;
float IE2 = 0;
float KP2 = 0;
float KI2 = 0;
float KD2 = 0;
float PID2 = 0;
float balM1 = 1;
float balM2 = 1;


float rateYawOffset = 0;

float elapsedTime = 0;
int plotState = 0; //0: integral w dt - 1: anglePitch - 2: kalmanAnglePitch  


void updatePID() {
    float prevE1 = E1;
    E1 = KalmanAnglePitch-angleOffset;
    dE1 = RatePitch;
    IE1 += E1*elapsedTime/1000000;
    float prevPID1 = PID1; 
    PID1 = clamp(-PWMscale, KP1*E1 + KI1*IE1 + KD1*dE1, PWMscale);
    PID1 = prevPID1 + PID1_gain*(PID1-prevPID1);
    float prevE2 = E2;
    E2 = RateYaw - rateYawOffset;
    dE2 = (E2-prevE2)/elapsedTime;
    IE2 += E2*elapsedTime/1000000;

    PID2 = sgn(PID1)*clamp(-PWMscale, KP2*E2 + KI2*IE2 + KD2*dE2, PWMscale);
}

void updateBalance(float PID) {
    float balance12 = pow(2, PID/PWMscale);
    if (balance12>=1) {
        balM1 = 1;
        balM2 = 1/balance12;
    }
    else {
        balM2 = 1;
        balM1 = balance12;
    }
}

void controlStageLoop(void* pvParameters) {
    kalmanAngleSetup();
    PWMsetup();
    //control loop
    LoopTimer = micros();
    while (1) {
        uint32_t initialTime = micros();
        updateKalmanAngle();
        integratedRatePitch += elapsedTime/1000 * RatePitch; //Multiplies elapsedTime/1000 (s) to RatePitch (*/seg)
        updatePID();
        updateBalance(PID2);
        MotorSpeed(chM1_A, chM1_B, balM1*PID1);
        MotorSpeed(chM2_A, chM2_B, balM2*PID1);


        uint32_t finalTime = micros();
        elapsedTime = (finalTime - initialTime)/1000.0;
        //Ensurese the loop lasts dt (ms)
        while (micros() - LoopTimer < dt*1000)
            LoopTimer=micros();
        
    }
}