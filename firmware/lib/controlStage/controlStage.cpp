#include <controlStage.h>

float dt=2; //The duration of each loop in ms. 

float E=0;
float dE;
float IE;
float PID=0;

float PID_P = 8;
float PID_I = 0;
float PID_D = 0;

float angleOffset=0;

void updatePID() {
    float prevE = E;
    E = KalmanAnglePitch-angleOffset;
    dE = RatePitch;
    IE += E*dt;  //The idea is to use another Kalman filter to find the integral.
    PID = PID_P*E;
}


void controlStageLoop(void* pvParameters) {
    //Updates KalmanAnglePitch and KalmanAngleRoll
    kalmanAngleSetup();
    PWMsetup();
    //control loop
    while (1) {
        updateKalmanAngle();

        updatePID();
        MotorSpeed(1, PID);
        MotorSpeed(2, PID);
        //Ensures the loop lasts 4ms.
        while (micros() - LoopTimer < dt*1000)
            LoopTimer=micros();
        
    }
}