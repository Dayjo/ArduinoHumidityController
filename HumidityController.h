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
    HumidityController(int motorEnablePin, int motorIn1Pin, int motorIn2Pin, double desiredTemperature, double maxHumidity);
    String updateStatus(double temp, double humidity);
    void begin();
    void setMotor(int speed, bool reverse);
  private:
    int _motorEnablePin;
    int _motorIn1Pin;
    int _motorIn2Pin;
    int _motorSpeed;
    bool _motorReversed;
    double _temp;
    double _humidity;
    double _desiredTemperature;
    double _maxHumidity;
};

#endif