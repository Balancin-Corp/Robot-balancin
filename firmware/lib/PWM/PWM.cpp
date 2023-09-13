#include <PWM.h>

const int M1_A = 4;
const int M1_B= 16;
const int M2_A = 18;
const int M2_B = 19;

// PWM settings

const int PWMfreq = 30000;
const int chM1_A = 0;
const int chM1_B = 1;
const int chM2_A = 2;
const int chM2_B = 3;
const int PWMres = 10; // 16 bits
const int PWMscale = 100;
const int PWMres_bits = 1023;



void PWMsetup() {

	//Set the motor pins as output
	pinMode(M1_A, OUTPUT);
	pinMode(M1_B, OUTPUT);
	pinMode(M2_A, OUTPUT);
	pinMode(M2_B, OUTPUT);

	//Set freq and resolution
	ledcSetup(chM1_A, PWMfreq, PWMres);
	ledcSetup(chM1_B, PWMfreq, PWMres);
	ledcSetup(chM2_A, PWMfreq, PWMres);
	ledcSetup(chM2_B, PWMfreq, PWMres);
	
	// attach the PWM channels to the Motor pins.
	ledcAttachPin(M1_A, chM1_A);
	ledcAttachPin(M1_B, chM1_B);
	ledcAttachPin(M2_A, chM2_A);
	ledcAttachPin(M2_B, chM2_B);

    ledcWrite(chM1_A, 0);
    ledcWrite(chM1_B, 0);
    ledcWrite(chM2_A, 0);
    ledcWrite(chM2_B, 0);
}

void MotorSpeed(int Motor, float speed) { //Receives a float value between -PWMscale to PWMscale
	if (speed > PWMscale) 
		speed = PWMscale;
    if (speed < -PWMscale) 
		speed = -PWMscale;

	switch (Motor) {
	case 1:
		if (speed >= 0) { //Powers M1_A
			ledcWrite(chM1_B, 0);
			delayMicroseconds(50);
			ledcWrite(chM1_A, (uint32_t)(speed*PWMres_bits/PWMscale));
		}
		else {
			ledcWrite(chM1_A, 0);
			delayMicroseconds(50);
			ledcWrite(chM1_B, (uint32_t)(-speed*PWMres_bits/PWMscale));
		}
	break;

	case 2:
		if (speed >= 0) { //Powers M1_A
			ledcWrite(chM2_B, 0);
			delayMicroseconds(50);
			ledcWrite(chM2_A, (uint32_t)(speed*PWMres_bits/PWMscale));
		}
		else {
			ledcWrite(chM2_A, 0);
			delayMicroseconds(50);
			ledcWrite(chM2_B, (uint32_t)(-speed*PWMres_bits/PWMscale));
		}
	break;

	}
}

