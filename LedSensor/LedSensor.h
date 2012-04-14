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

#ifndef LedSensor_h
#define LedSensor_h

#include "Arduino.h"

#define MICRO   false
#define MILLI   true

class LedSensor
{
  public:
    LedSensor(int pinP, int pinN);
    LedSensor(int pinP, int pinN, unsigned long timeout);
    LedSensor(int pinP, int pinN, unsigned long timeout, boolean resolution);
    void calibrate();
    unsigned int read();
    unsigned int readCalibrated();
    void setMin(unsigned int minValue);
    void setMax(unsigned int maxValue);
    void setResolution(boolean resolution);
    unsigned int getMin();
    unsigned int getMax();
    boolean getResolution();
  private:
    unsigned long getTime();
    int _pinP, _pinN;
    unsigned long _timeout;
    unsigned int _maxValue, _minValue;
    boolean _resolution;
};

#endif
