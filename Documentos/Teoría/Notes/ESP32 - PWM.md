[Fuente](https://github.com/espressif/arduino-esp32/blob/master/docs/source/api/ledc.rst)

```cpp
// the motor pins
const int M1_A = 4;
const int M1_B= 2;
const int M2_A = 18;
const int M2_B = 19;

// PWM settings

const int PWMfreq = 30000;
const int ChM1_A = 0;
const int ChM1_B = 1;
const int ChM2_A = 2;
const int ChM2_B = 3;
const int PWMres = 16; // 16 bits
const int PWMscale = 100;


void PWPsetup() {

	//Set the motor pins as output
	pinMode(M1_A, OUTPUT);
	pinMode(M1_B, OUTPUT);
	pinMode(M2_A, OUTPUT);
	pinMode(M2_B, OUTPUT);

	//Set freq and resolution
	ledcSetup(chM1_A, PWMfreq, PWMres);
	ledcSetup(ChM1_B, PWMfreq, PWMres);
	ledcSetup(chM2_A, PWMfreq, PWMres);
	ledcSetup(ChM2_B, PWMfreq, PWMres);
	
	// attach the PWM channels to the Motor pins.
	ledcAttachPin(M1_A, chM1_A);
	ledcAttachPin(M1_B, chM1_B);
	ledcAttachPin(M2_A, chM2_A);
	ledcAttachPin(M2_B, chM2_B);
}

void MotorSpeed(int Motor, float Speed) { //Receives a float value between -PWMscale to PWMscale
	switch (Motor) {
		case 1:
			if (Speed >= 0) { //Powers M1_A
				ledcWrite(chM1_B, 0);
				delayMicroseconds(50);
				ledcWrite(chM1_A, (int)(Speed*65536.0/PWMscale));
			}
			else
				ledcWrite(chM1_A, 0);
				delayMicroseconds(50);
				ledcWrite(chM1_B, (int)(-Speed*65536.0/PWMscale));
			break;
		case 2:
			if (Speed >= 0) { //Powers M2_A
				ledcWrite(chM2_B, 0);
				delayMicroseconds(50);
				ledcWrite(chM2_A, (int)(Speed*65536.0/PWMscale));
			}
			else
				ledcWrite(chM2_A, 0);
				delayMicroseconds(50);
				ledcWrite(chM2_B, (int)(-Speed*65536.0/PWMscale));
			break;	
	}
}

void setup(){

	PWMsetup();

}
 
void loop(){

}
```


