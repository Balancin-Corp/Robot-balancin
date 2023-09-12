#include <PWM.h>

void PWMsetup() {

	//Set the motor pins as output
	pinMode(M1_A, OUTPUT);
	pinMode(M1_B, OUTPUT);
	pinMode(M2_A, OUTPUT);
	pinMode(M2_B, OUTPUT);

	//Set freq and resolution
	ledcSetup(chM1_A, PWMfreq, PWMres);
	ledcSetup(chM1_B, PWMfreq, PWMres);
	/*ledcSetup(chM2_A, PWMfreq, PWMres);
	ledcSetup(chM2_B, PWMfreq, PWMres);*/
	
	// attach the PWM channels to the Motor pins.
	ledcAttachPin(M1_A, chM1_A);
	ledcAttachPin(M1_B, chM1_B);
	/*ledcAttachPin(M2_A, chM2_A);
	ledcAttachPin(M2_B, chM2_B);*/

    ledcWrite(chM1_A, 0);
    ledcWrite(chM1_B, 0);
    ledcWrite(chM2_A, 0);
    ledcWrite(chM2_B, 0);
}

void MotorSpeed(int Motor, float speed) { //Receives a float value between -PWMscale to PWMscale
	if (speed > 10) speed = 10;
    if (speed < -10) speed = -10;
    switch (Motor) {
		case 1:
			if (speed >= 0) { //Powers M1_A
				ledcWrite(chM1_B, 0);
				delayMicroseconds(50);
				ledcWrite(chM1_A, (int)(speed*65535.0/PWMscale));
			}
			else {
				ledcWrite(chM1_A, 0);
				delayMicroseconds(50);
				ledcWrite(chM1_B, (int)(-speed*65535.0/PWMscale));
            }
            return;
		/*case 2:
			if (speed >= 0) { //Powers M2_A
				ledcWrite(chM2_B, 0);
				delayMicroseconds(50);
				ledcWrite(chM2_A, (int)(speed*65535.0/PWMscale));
			}
			else {
				ledcWrite(chM2_A, 0);
				delayMicroseconds(50);
				ledcWrite(chM2_B, (int)(-speed*65535.0/PWMscale));
            }
            return;*/
	}
}
