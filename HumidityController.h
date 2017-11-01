/*
  HumidtyController.h - Library for controlling fan speed and direction based on temperature and humidity
  Created by Joel Day 2017
*/
#ifndef HumidityController_h
#define HumidityController_h

#include "Arduino.h"

class HumidityController
{
  public:
    HumidityController(int sensorPin, int motorEnablePin, int motorIn1Pin, int motorIn2Pin);
    void dot();
    void dash();
    void setMotor(int speed, bool reverse);
  private:
    int _sensorPin;
    int _motorEnablePin;
    int _motorIn1Pin;
    int _motorIn2Pin;
};

#endif