#include <Arduino.h>
#include <Wire.h>

//control
int IMotor1 = 4;
int DMotor1 = 18;
int IMotor2 = 19;
int DMotor2 = 16;
float desired_angle = 0;
float error = 0;
float pid_p=0;
float pid_i=0;
float pid_d=0;
float kp=11;
float ki=1.1;
float kd=0.6;
float elapsedTime, tiempo, timePrev; 
float A,PWM,PID, previous_error;;
//Kalman
float RateRoll, RatePitch, RateYaw;
float RateCalibrationRoll, RateCalibrationPitch, RateCalibrationYaw;
int RateCalibrationNumber;
float AccX, AccY, AccZ;
float AngleRoll, AnglePitch;
uint32_t LoopTimer;
float KalmanAngleRoll=0, KalmanUncertaintyAngleRoll=2*2;
float KalmanAnglePitch=0, KalmanUncertaintyAnglePitch=2*2;
float Kalman1DOutput[]={0,0};

void clockw() {
  analogWrite(IMotor1,PWM);
  analogWrite(IMotor2,0);
  analogWrite(DMotor1,PWM);
  analogWrite(DMotor2,0); 
}
void anti() {
  analogWrite(IMotor2,PWM);
  analogWrite(IMotor1,0);
  analogWrite(DMotor2,PWM);
  analogWrite(DMotor1,0);
}
void halt() {
  analogWrite(IMotor1,0);
  analogWrite(IMotor2,0);
  analogWrite(DMotor1,0);
  analogWrite(DMotor2,0);
  
}

float PitchOffset;
void kalman_1d(float KalmanState, float KalmanUncertainty, float KalmanInput, float KalmanMeasurement) {
  KalmanState=KalmanState+0.004*KalmanInput;
  KalmanUncertainty=KalmanUncertainty + 0.004 * 0.004 * 4 * 4;
  float KalmanGain=KalmanUncertainty * 1/(1*KalmanUncertainty + 3 * 3);
  KalmanState=KalmanState+KalmanGain * (KalmanMeasurement-KalmanState);
  KalmanUncertainty=(1-KalmanGain) * KalmanUncertainty;
  Kalman1DOutput[0]=KalmanState; 
  Kalman1DOutput[1]=KalmanUncertainty;
}

void gyro_signals(void) { //Mide los valores raw del giroscopio
  Wire.beginTransmission(0x68);
  Wire.write(0x1A);
  Wire.write(0x05);
  Wire.endTransmission();
  Wire.beginTransmission(0x68);
  Wire.write(0x1C);
  Wire.write(0x10);
  Wire.endTransmission();
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission(); 
  Wire.requestFrom(0x68,6);
  int16_t AccXLSB = Wire.read() << 8 | Wire.read();
  int16_t AccYLSB = Wire.read() << 8 | Wire.read();
  int16_t AccZLSB = Wire.read() << 8 | Wire.read();
  Wire.beginTransmission(0x68);
  Wire.write(0x1B); 
  Wire.write(0x8);
  Wire.endTransmission();     
  Wire.beginTransmission(0x68);
  Wire.write(0x43);
  Wire.endTransmission();
  Wire.requestFrom(0x68,6);
  int16_t GyroX=Wire.read()<<8 | Wire.read();
  int16_t GyroY=Wire.read()<<8 | Wire.read();
  int16_t GyroZ=Wire.read()<<8 | Wire.read();
  RateRoll=(float)GyroX/65.5;
  RatePitch=(float)GyroY/65.5;
  RateYaw=(float)GyroZ/65.5;
  AccX=(float)AccXLSB/4096;
  AccY=(float)AccYLSB/4096;
  AccZ=(float)AccZLSB/4096;
  AngleRoll=atan(AccY/sqrt(AccX*AccX+AccZ*AccZ))*1/(3.142/180);
  AnglePitch=-atan(AccX/sqrt(AccY*AccY+AccZ*AccZ))*1/(3.142/180);
}

void KalmanAngle() {
    gyro_signals();
    RateRoll-=RateCalibrationRoll;
    RatePitch-=RateCalibrationPitch;
    RateYaw-=RateCalibrationYaw;
    kalman_1d(KalmanAngleRoll, KalmanUncertaintyAngleRoll, RateRoll, AngleRoll);
    KalmanAngleRoll=Kalman1DOutput[0]; 
    KalmanUncertaintyAngleRoll=Kalman1DOutput[1];
    kalman_1d(KalmanAnglePitch, KalmanUncertaintyAnglePitch, RatePitch, AnglePitch);
    KalmanAnglePitch=Kalman1DOutput[0]; 
    KalmanUncertaintyAnglePitch=Kalman1DOutput[1];
}


void setup() {
    pinMode(IMotor1, OUTPUT);
    pinMode(IMotor2, OUTPUT);
    pinMode(DMotor2, OUTPUT);
    pinMode(DMotor1, OUTPUT);
    analogWrite(IMotor1, 0);
    analogWrite(IMotor2, 0);
    analogWrite(DMotor2, 0);
    analogWrite(DMotor1, 0);
    //ledcAttachPin(18, 0);
    //ledcAttachPin(19, 0);
    delay(50);
    
    Serial.begin(115200);
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
    Wire.setClock(400000);
    Wire.begin();
    delay(250);
    Wire.beginTransmission(0x68); 
    Wire.write(0x6B);
    Wire.write(0x00);
    Wire.endTransmission();
    for (RateCalibrationNumber=0; RateCalibrationNumber<2000; RateCalibrationNumber ++) {
        gyro_signals();
        RateCalibrationRoll+=RateRoll;
        RateCalibrationPitch+=RatePitch;
        RateCalibrationYaw+=RateYaw;
        delay(1);
    }
    RateCalibrationRoll/=2000;
    RateCalibrationPitch/=2000;
    RateCalibrationYaw/=2000;
    LoopTimer=micros();
}
void loop() {
    KalmanAngle();
    A = KalmanAnglePitch;
    timePrev = tiempo;  
    tiempo = millis();  
    elapsedTime = (tiempo - timePrev) / 1000; 
    error = A - desired_angle;
    pid_p = kp*error;
    pid_i = pid_i+(ki*error);  
    pid_d = kd*((error - previous_error)/elapsedTime);
    PID = pid_p + pid_d; 
    previous_error = error;
    PWM = abs(PID);
  if(A<-3)
      {
       anti();
      }
    if(A>3)
      {
       clockw();
      }
    if(A>60){
    halt();
    }
    if(A<-60){
    halt();
}


}