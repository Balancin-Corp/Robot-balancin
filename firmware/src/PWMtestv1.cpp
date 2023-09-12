#include <Arduino.h>
#include <PWM.h>


void setup() {
    Serial.begin(115200);
    PWMsetup();
}

void loop() {
    ledcWrite(chM1_A, 255);
    delay(1000);
    ledcWrite(chM1_A, 128);
    delay(1000);
    ledcWrite(chM1_A, 0);
    delay(1000);
}