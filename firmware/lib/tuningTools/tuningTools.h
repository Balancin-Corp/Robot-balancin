#ifndef tuningTools_h
#define tuningTools_h

#include <Arduino.h>
#include <BluetoothSerial.h>
#include <controlStage.h>
extern BluetoothSerial SerialBT;


extern String strList[];
extern float* val[];

void tuningToolsSetup();
void printValues(String keyword);
float getValue(String);
int includedIn(String string1, String String2);
void tuningToolsInput();




#endif