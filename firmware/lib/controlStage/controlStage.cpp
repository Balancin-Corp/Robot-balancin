#include <controlStage.h>

void controlStageLoop(void* pvParameters) {
    //Updates KalmanAnglePitch and KalmanAngleRoll
    KalmanAngleSetup();

    //control loop
    while (1) {
        updateKalmanAngle();

        Serial.print("Angle pitch = ");
        Serial.println(KalmanAnglePitch);
        Serial.print("Angle roll = ");
        Serial.println(KalmanAngleRoll);

        //PID control:

        //Ensures the loop lasts 4ms.
        while (micros() - LoopTimer < 4000);
        LoopTimer=micros();
    }
}