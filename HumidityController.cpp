/*
  HumidityController.cpp
*/

#include "Arduino.h"
#include "HumidityController.h"

HumidityController::HumidityController(int sensorPin, int motorEnablePin, int motorIn1Pin, int motorIn2Pin)
{
  pinMode(motorEnablePin, OUTPUT);
  pinMode(motorIn1Pin, OUTPUT);
  pinMode(motorIn2Pin, OUTPUT);

  _sensorPin = sensorPin;
  _motorEnablePin = motorEnablePin;
  _motorIn1Pin = motorIn1Pin;
  _motorIn2Pin = motorIn2Pin;
}

void  HumidityController::setMotor(int speed, bool reverse) {

  digitalWrite(_motorEnablePin, speed);
  digitalWrite(_motorIn1Pin, reverse);
  digitalWrite(_motorIn2Pin, ! reverse);
}