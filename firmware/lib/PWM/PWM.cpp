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

int delayM1 = 10;
int delayM2 = 10;



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

void MotorSpeed(int chM_A, int chM_B, float speed) { //Receives a float value between -PWMscale to PWMscale

	int speed_bits = (int)abs(speed*((float)(PWMres_bits)/PWMscale));

	if (speed >= 0) { //Powers M_A
		ledcWrite(chM_B, 0);
		delayMicroseconds(50);
		ledcWrite(chM_A, speed_bits);
	}
	else {
		ledcWrite(chM_A, 0);
		delayMicroseconds(50);
		ledcWrite(chM_B, speed_bits);
	}

}


void updateBalance(float* balance12, float* balance1, float* balance2) {
	if (*balance12 <=0) *balance12 = 1;
	if (*balance12 >=1) { //If balance12 >=1, then M1 will receive more voltage than M2
	*balance1 = 1;
	*balance2 = *balance1/(*balance12);
	}
	else if (*balance12<1) {
	*balance2 = 1;
	*balance1 = *balance2*(*balance12);
	}
}
