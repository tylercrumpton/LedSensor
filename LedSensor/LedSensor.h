/*
  LedSensor.h - Library for using an LED as a light sensor.
  Copyright 2012 Tyler Crumpton.
  This library is licensed under a GPLv3 License (see COPYING).
  Source at: https://github.com/tac0010/LED-Sensor-Library
  
  (Based on http://arduino.cc/playground/Learning/LEDSensor)
  
  March 25, 2012 - v0.2: Using actual timing instead of for-loop. 
*/

#ifndef LedSensor_h
#define LedSensor_h

#include "Arduino.h"

class LedSensor
{
  public:
    LedSensor(int pinP, int pinN);
    LedSensor(int pinP, int pinN, int timeout);
    void calibrate();
    unsigned int read();
    unsigned int readCalibrated();
    void setMin(unsigned int minValue);
    void setMax(unsigned int maxValue);
    unsigned int getMin();
    unsigned int getMax();
  private:
    int _pinP, _pinN;
    unsigned int _timeout;
    unsigned int _maxValue, _minValue;
};

#endif
