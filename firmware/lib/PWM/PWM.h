#ifndef PWN_h
#define PWM_h

#include <Arduino.h>

const int M1_A = 26;
const int M1_B= 25;
const int M2_A = 18;
const int M2_B = 19;

// PWM settings

const int PWMfreq = 30000;
const int chM1_A = 0;
const int chM1_B = 1;
const int chM2_A = 2;
const int chM2_B = 3;
const int PWMres = 8; // 16 bits
const int PWMscale = 100;


void PWMsetup();
void MotorSpeed(int Motor, float Speed); //Receives a float value between -PWMscale to PWMscale


#endif