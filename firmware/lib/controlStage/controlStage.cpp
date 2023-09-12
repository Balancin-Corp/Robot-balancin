#include <controlStage.h>

void controlStageLoop(void* pvParameters) {
    //Updates KalmanAnglePitch and KalmanAngleRoll
    kalmanAngleSetup();

    //control loop
    while (1) {
        updateKalmanAngle();


        //Ensures the loop lasts 4ms.
        while (micros() - LoopTimer < 4000);
        LoopTimer=micros();
    }
}