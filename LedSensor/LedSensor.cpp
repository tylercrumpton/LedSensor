/*
  LedSensor.h - Library for using an LED as a light sensor.
  Copyright 2012 Tyler Crumpton.
  This library is licensed under a GPLv3 License (see COPYING).
  Source at: https://github.com/tac0010/LED-Sensor-Library

  (Based on http://arduino.cc/playground/Learning/LEDSensor)

  April 14, 2012 - v0.3: Added selectable timing range.
  March 25, 2012 - v0.2: Using actual timing instead of for-loop.
  March 19, 2012 - v0.1: Initial release.
*/

#include "Arduino.h"
#include "LedSensor.h"

LedSensor::LedSensor(int pinP, int pinN)
{
  _pinP = pinP;
  _pinN = pinN;
  _timeout = 30000;
  _minValue = 30000;
  _maxValue = 0;
  _resolution = MILLI;
}

LedSensor::LedSensor(int pinP, int pinN, unsigned long timeout)
{
  _pinP = pinP;
  _pinN = pinN;
  _timeout = timeout;
  _minValue = timeout;
  _maxValue = 0;
  _resolution = MILLI;
}

LedSensor::LedSensor(int pinP, int pinN, unsigned long timeout, boolean resolution)
{
  _pinP = pinP;
  _pinN = pinN;
  _timeout = timeout;
  _minValue = timeout;
  _maxValue = 0;
  _resolution = resolution;
}

//Reads the sensor ten times and finds the minimum and maximum values over the ten
//  readings. The max and min are used in order to use readCalibrated(), and
//  calibrate() should be run multiple times in order to get the full range of
//  values.
void LedSensor::calibrate()
{
  int j;
  for (j=0; j<10; ++j)
  {
    unsigned int value = LedSensor::read();
    if (value > _maxValue)
      _maxValue = value;
    if (value < _minValue)
      _minValue = value;
  }
}

//Reads the raw sensor data in terms of milliseconds/microseconds (depending on the
//  set resolution).
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
  unsigned long startTime = getTime(); // Get time at start of sensing
  unsigned long totalTime = 0;		   // Total time elapsed

  while(digitalRead(_pinN)==1 && totalTime <= _timeout)  // Keep looping until timeout or logic zero
  {
    totalTime = getTime() - startTime; //Find new total elapsed time
  }
  //Make sure the value doesn't overflow int:
  if (totalTime > 65535)
  {
    totalTime = 65535;
  }
  return totalTime; // Return time taken to drop to zero.
}

//Reads the calibrated sensor data as a value between 0 and 1000 (regardless of
//  resolution). Requires that calibrate() has been run, or max and min values
//  have been manually set.
unsigned int LedSensor::readCalibrated()
{
  unsigned int value = LedSensor::read();
  return (1000 * value / (_maxValue - _minValue));
}

//Manually sets the minimum sensor value in terms of milliseconds/microseconds
//  (depending on the set resolution).
void LedSensor::setMin(unsigned int minValue)
{
  _minValue = minValue;
}

//Manually sets the maximum sensor value in terms of milliseconds/microseconds
//  (depending on the set resolution).
void LedSensor::setMax(unsigned int maxValue)
{
  _maxValue = maxValue;
}

//Set the resolution of the sensor to MILLI (milliseconds) or MICRO (microsec).
//  If doing white/black line detection, it is a good idea to use MICRO, but
//  if searching for objects, it is usually better to use MILLI.
void LedSensor::setResolution(boolean resolution)
{
  _resolution = resolution;
}

//Returns the minimum sensor value in terms of milliseconds/microseconds
//  (depending on the set resolution).
unsigned int LedSensor::getMin()
{
  return _minValue;
}

//Returns the minimum sensor value in terms of milliseconds/microseconds
//  (depending on the set resolution).
unsigned int LedSensor::getMax()
{
  return _maxValue;
}

//Returns the currently set resolution of the sensor (MILLI or MICRO).
boolean LedSensor::getResolution()
{
  return _resolution;
}

//Private function that gets the current system in microseconds or
//  milliseconds, depending on the currently set resolution.
unsigned long LedSensor::getTime()
{
  if (_resolution == MILLI)
  {
    return millis();
  }
  else
  {
    return micros();
  }
}
