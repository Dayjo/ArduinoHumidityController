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
  _motorSpeed = 0;
  _motorBaseSpeed = 50;
  _motorMaxSpeed = 100;
  _motorMinSpeed = 40;
  // motor speed adjustment to add
  _motorAdjustment = 0;
}

String HumidityController::updateStatus(double temp, double humidity, bool reverse) {
    _temp = temp;
    _humidity = humidity;


    // The priority is reduce humidity
    // if it's more than the max humidity, increase the fan speed each loop until it's less
    if ( _humidity > _maxHumidity ) {
        _motorAdjustment += round((_humidity - _maxHumidity) / 2); // 0 - 100(%)
		reverse = true; // suck out all that moisture
    }
    else {

        // If the humidity is acceptable and it's not hot enough, reduce the speed of the fan
        if ( _temp < _desiredTemperature) {
			if ( _motorSpeed > _motorMinSpeed ) {
	            _motorAdjustment--;
			}
			reverse = true; // Air flow mode
        }
		// It's too hot, so cool it down
		else if ( _temp > _desiredTemperature  ) {
			if ( _motorSpeed < _motorMaxSpeed ) {
				_motorAdjustment++;
			}
			reverse = false; // try to pump cool air in
		}
		// If everything is ok, slow the motor down as much as possible
		else if ( _humidity <= _maxHumidity  ) {
			if (_motorSpeed > _motorMinSpeed && _motorAdjustment > 0 ) {
	            _motorAdjustment--;
			}
			reverse = true; // Air flow mode
	   }

    }

	// @TODO fix this, wtf?
    if ( _motorAdjustment < -100 ) {
        _motorAdjustment = -100;
    }
    else if ( _motorAdjustment > 100 ) {
        _motorAdjustment = 100;
    }



    _motorSpeed = _motorBaseSpeed + _motorAdjustment;
    if ( _motorSpeed > _motorMaxSpeed ) {
        _motorSpeed = _motorMaxSpeed;
    }

	if ( _motorSpeed < _motorMinSpeed ) {
        _motorSpeed = _motorMinSpeed;
    }

    setMotor(_motorSpeed, reverse);
    return "Speed: " + String(_motorSpeed) + "\nAdjustment: " + String(_motorAdjustment) + "\nReverse: " + String(reverse);
}


void  HumidityController::setMotor(double speed, bool reverse) {
    // Turn speed from 0 - 100 into 0-255;
  speed = ((speed/100) * 250);
  analogWrite(_motorEnablePin, speed);
  digitalWrite(_motorIn1Pin, reverse);
  digitalWrite(_motorIn2Pin, ! reverse);
}
