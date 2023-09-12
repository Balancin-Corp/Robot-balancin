#include <Arduino.h>
#include <PWM.h>

void setup() {
    Serial.begin(115200);
    PWMsetup();
}

void loop() {
    MotorSpeed(1, 100);
    delay(1000);
    MotorSpeed(1, -100);
    delay(1000);
}