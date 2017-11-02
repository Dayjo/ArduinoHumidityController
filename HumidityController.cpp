/*
  HumidityController.cpp
*/

#include "Arduino.h"

#include "HumidityController.h"

HumidityController::HumidityController(int motorEnablePin, int motorIn1Pin, int motorIn2Pin, double desiredTemperature, double maxHumidity)
{
    // Serial.print(_dht);
  // _dht(sensorPin, DHT11);
  pinMode(motorEnablePin, OUTPUT);
  pinMode(motorIn1Pin, OUTPUT);
  pinMode(motorIn2Pin, OUTPUT);

  // _sensorPin = sensorPin;
  _motorEnablePin = motorEnablePin;
  _motorIn1Pin = motorIn1Pin;
  _motorIn2Pin = motorIn2Pin;
  _desiredTemperature = desiredTemperature;
  _maxHumidity = maxHumidity;

}

String HumidityController::updateStatus(double temp, double humidity) {
    _temp = temp;
    _humidity = humidity;
    adjustment = 0;

    // The priority is reduce humidity
    // if it's more than the max humidity, increase the fan speed
    if ( _humidity > maxHumidity ) {
        adjustment += _humidity - maxHumidity; // 0 - 100(%)
    }
    // If the humidity is acceptable and it's not hot enough, reduce the speed of the fan
    else if ( _temp < _desiredTemperature ) {
        adjustment--;
    }

    return String(temp) + " : " + String(humidity);
}


void  HumidityController::setMotor(int speed, bool reverse) {

  digitalWrite(_motorEnablePin, speed);
  digitalWrite(_motorIn1Pin, reverse);
  digitalWrite(_motorIn2Pin, ! reverse);
}