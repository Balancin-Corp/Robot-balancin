#ifndef kalmanAngle_h
#define kalmanAngle_h

#include <Arduino.h>
#include <Wire.h>

float RateRoll, RatePitch, RateYaw;
float RateCalibrationRoll, RateCalibrationPitch, RateCalibrationYaw;
int RateCalibrationNumber;
float AccX, AccY, AccZ;
float AngleRoll, AnglePitch;
uint32_t LoopTimer;
float KalmanAngleRoll=0, KalmanUncertaintyAngleRoll=2*2;
float KalmanAnglePitch=0, KalmanUncertaintyAnglePitch=2*2;
float Kalman1DOutput[]={0,0};
float PitchOffset;

void gyroSignals();
void kalman_1d();
void KalmanAngleSetup();
void updateKalmanAngle();

#endif
