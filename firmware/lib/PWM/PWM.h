#ifndef PWN_h
#define PWM_h

#include <Arduino.h>

extern const int M1_A;
extern const int M1_B;
extern const int M2_A;
extern const int M2_B;

// PWM settings

extern const int PWMfreq;
extern const int chM1_A;
extern const int chM1_B;
extern const int chM2_A;
extern const int chM2_B;
extern const int PWMres; // 16 bits
extern const int PWMres_bits;

extern const int PWMscale;

extern int delayM1, delayM2;

extern float balanceCL1;
extern float balanceCL2;
extern float balanceCL12;
extern float balanceACL1;
extern float balanceACL2;
extern float balanceACL12;



void PWMsetup();
void MotorSpeed(int Motor, float Speed); //Receives a float value between -PWMscale to PWMscale


#endif