/*
  LedSensor.h - Library for using an LED as a light sensor.
  Copyright 2012 Tyler Crumpton.
  This library is licensed under a GPLv3 License (see COPYING).
  
  (Based on http://arduino.cc/playground/Learning/LEDSensor)
  
  March 19, 2012 - v0.1: Initial release. 
*/

#include "Arduino.h"
#include "LedSensor.h"

LedSensor::LedSensor(int pinP, int pinN)
{
  _pinP = pinP;
  _pinN = pinN;
  _timeout = 60000;
  _minValue = 60000;
  _maxValue = 0;
}

LedSensor::LedSensor(int pinP, int pinN, int timeout)
{
  _pinP = pinP;
  _pinN = pinN;
  _timeout = timeout;
  _minValue = timeout;
  _maxValue = 0;
}

void LedSensor::calibrate()
{
  unsigned int value = LedSensor::read();
  if (value > _maxValue)
    _maxValue = value;
  if (value < _minValue)
    _minValue = value;
}
unsigned int LedSensor::read()
{
  unsigned int t;

  // Apply reverse voltage, charge up the pin and led capacitance
  pinMode(_pinN,OUTPUT);
  pinMode(_pinP,OUTPUT);
  digitalWrite(_pinN,HIGH);
  digitalWrite(_pinP,LOW);

  // Isolate the cathode of the diode
  pinMode(_pinN,INPUT);
  digitalWrite(_pinN,LOW);  // turn off internal pull-up resistor

  // Count how long it takes the diode to bleed back down to a logic zero
  for ( t = 0; t < _timeout; ++t) {
    if (digitalRead(_pinN)==0) 
      break;
  }
  
  return t;
}
unsigned int LedSensor::readCalibrated()
{
  unsigned int value = LedSensor::read();
  return (1000 * value / (_maxValue - _minValue));
}
void LedSensor::setMin(unsigned int minValue)
{
  _minValue = minValue;
}
void LedSensor::setMax(unsigned int maxValue)
{
  _maxValue = maxValue;
}
unsigned int LedSensor::getMin()
{
  return _minValue;
}
unsigned int LedSensor::getMax()
{
  return _maxValue;
}
