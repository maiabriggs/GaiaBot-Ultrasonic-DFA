#ifndef FiveSensors_h
#define FiveSensors_h

#include "Arduino.h"

class FiveSensors {
  public:
    FiveSensors();

    void begin(int f_trigPin, int f_echoPin, int m2_trigPin, int m2_echoPin, int m1_trigPin, int m1_echoPin, int fm1_trigPin, int fm1_echoPin, int fm2_trigPin, int fm2_echoPin);
    float getFrontSensorDist();
    float getM2SensorDist();
    float getM1SensorDist();
    float getFM2SensorDist();
    float getFM1SensorDist();
    float checkSensor(int sensor);
    bool checkAllSensors();

  private:
    float f_duration, f_distance, m2_duration, m2_distance, m1_duration, m1_distance, fm2_duration, fm2_distance, fm1_duration, fm1_distance;
    int f_trig, f_echo, m1_trig, m1_echo, m2_trig, m2_echo, fm1_trig, fm1_echo, fm2_trig, fm2_echo;
};

#endif

