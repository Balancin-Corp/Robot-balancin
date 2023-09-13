#include <controlStage.h>

float dt=2; //The duration of each loop in ms. 

float E=0;
float dE;
float IE;
float PID;

float PID_E = 8.3;
float PID_dE = 0;
float PID_IE = 0;

float angleOffset=0;

void updatePID() {
    float prevE = E;
    E = KalmanAnglePitch-angleOffset;
    dE = RatePitch;
    IE += E*dt;  //The idea is to use another Kalman filter to find the integral.
    PID = PID_E*E;
}


void controlStageLoop(void* pvParameters) {
    //Updates KalmanAnglePitch and KalmanAngleRoll
    kalmanAngleSetup();
    PWMsetup();
    //control loop
    while (1) {
        updateKalmanAngle();

        updatePID();
        MotorSpeed(1, 100);
        MotorSpeed(2, 100);
        //Ensures the loop lasts 4ms.
        while (micros() - LoopTimer < dt*1000)
            LoopTimer=micros();
        
    }
}