/*
  LedSensor.h - Library for using an LED as a light sensor.
  Copyright 2012 Tyler Crumpton.
  This library is licensed under a GPLv3 License (see COPYING).
  Source at: https://github.com/tac0010/LED-Sensor-Library
  
  (Based on http://arduino.cc/playground/Learning/LEDSensor)
  
  March 25, 2012 - v0.2: Using actual timing instead of for-loop. 
*/

#include "Arduino.h"
#include "LedSensor.h"

LedSensor::LedSensor(int pinP, int pinN)
{
  _pinP = pinP;
  _pinN = pinN;
  _timeout = 200000;
  _minValue = 200000;
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
  // Apply reverse voltage, charge up the pin and led capacitance
  pinMode(_pinN,OUTPUT);
  pinMode(_pinP,OUTPUT);
  digitalWrite(_pinN,HIGH);
  digitalWrite(_pinP,LOW);

  // Isolate the cathode of the LED
  pinMode(_pinN,INPUT);
  digitalWrite(_pinN,LOW);  // Turn off internal pull-up resistor

  // Measure the time it takes the LED to bleed back down to a logic zero
  unsigned long startTime = millis(); // Get time at start of sensing
  unsigned int totalTime = 0;		 // Total time elapsed
  while(digitalRead(_pinN)!=0 || totalTime > _timeout)  // Keep looping until timeout or logic zero
  {
    totalTime = millis() - startTime; //Find new total elapsed time
  }     
  
  return totalTime; // Return time taken to drop to zero.
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
