#ifndef kalmanAngle_h
#define kalmanAngle_h

#include <Arduino.h>
#include <Wire.h>


extern float RateRoll, RatePitch, RateYaw;
extern float RateCalibrationRoll, RateCalibrationPitch, RateCalibrationYaw;
extern int RateCalibrationNumber;
extern float AccX, AccY, AccZ;
extern float AngleRoll, AnglePitch;

extern float KalmanAngleRoll, KalmanUncertaintyAngleRoll;
extern float KalmanAnglePitch, KalmanUncertaintyAnglePitch;
extern float Kalman1DOutput[];
extern float PitchOffset;

extern float integratedRatePitch;

void gyroSignals();
void kalman_1d();
void kalmanAngleSetup();
void updateKalmanAngle();

#endif
