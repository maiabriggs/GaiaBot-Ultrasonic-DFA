/*
 * Class for retrieving information from three HC-SR04 Sensors
 *
 * Referenced from Isaac100 HC-SR04 example sketch
 * https://create.arduino.cc/projecthub/Isaac100/getting-started-with-the-hc-sr04-ultrasonic-sensor-036380
 * Adapted for three sensor control
 */

#include "Arduino.h"
#include "FiveSensors.h"

int f_trig;
int f_echo;

int m1_trig; //M1 is right
int m1_echo;

int m2_trig; //M2 is Left
int m2_echo;

int fm2_trig;
int fm2_echo;


int fm1_trig;
int fm1_echo;


float getFrontSensorDist();

float getM2SensorDist();
float getM1ensorDist();

float getFM2SensorDist();
float getFM1ensorDist();

FiveSensors::FiveSensors() {}

void FiveSensors::begin(int f_trigPin, int f_echoPin, int m2_trigPin, int m2_echoPin, int m1_trigPin, int m1_echoPin, int fm1_trigPin, int fm1_echoPin, int fm2_trigPin, int fm2_echoPin) {
  f_trig = f_trigPin;
  f_echo = f_echoPin;

  m2_trig = m2_trigPin;
  m2_echo = m2_echoPin;

  m1_trig = m1_trigPin;
  m1_echo = m1_echoPin;

  fm2_trig = fm2_trigPin;
  fm2_echo = fm2_echoPin;

  fm1_trig = fm1_trigPin;
  fm1_echo = fm1_echoPin;
  
  //Initialising front sensor
  pinMode(f_trig, OUTPUT);
  pinMode(f_echo, INPUT);
  Serial.begin(9600);
  
  //Initialising left sensor
  pinMode(m2_trig, OUTPUT);
  pinMode(m2_echo, INPUT);
  Serial.begin(9600);
   
  //Initialising right sensor
  pinMode(m1_trig, OUTPUT);
  pinMode(m1_echo, INPUT);
  Serial.begin(9600);

  //Initialising front right sensor
  pinMode(fm1_trig, OUTPUT);
  pinMode(fm1_echo, INPUT);
  Serial.begin(9600);

  //Initialising front left sensor
  pinMode(fm2_trig, OUTPUT);
  pinMode(fm2_echo, INPUT);
  Serial.begin(9600);
}

float FiveSensors::getFrontSensorDist() {
  //Front sensor
  digitalWrite(f_trig, LOW);
  delayMicroseconds(2);
  digitalWrite(f_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(f_trig, LOW);

  float f_duration = pulseIn(f_echo, HIGH);
  float f_distance = (f_duration*.0343)/2;
  //Serial.print("Front Distance: ");
  //Serial.println(f_distance);
  delay(100);

  return f_distance;
}

float FiveSensors::getM2SensorDist() {
  //Left sensor
  digitalWrite(m2_trig, LOW);
  delayMicroseconds(2);
  digitalWrite(m2_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(m2_trig, LOW);

  float m2_duration = pulseIn(m2_echo, HIGH);
  float m2_distance = (m2_duration*.0343)/2;
  delay(100);

  return m2_distance;
}

float FiveSensors::getM1SensorDist() {
  //Right sensor
  digitalWrite(m1_trig, LOW);
  delayMicroseconds(2);
  digitalWrite(m1_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(m1_trig, LOW);

  float m1_duration = pulseIn(m1_echo, HIGH);
  float m1_distance = (m1_duration*.0343)/2;
  //Serial.print("Right Distance: ");
  //Serial.println(r_distance);
  delay(100);

  return m1_distance;
}

float FiveSensors::getFM1SensorDist() {
  //Right sensor
  digitalWrite(fm1_trig, LOW);
  delayMicroseconds(2);
  digitalWrite(fm1_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(fm1_trig, LOW);

  float fm1_duration = pulseIn(fm1_echo, HIGH);
  float fm1_distance = (fm1_duration*.0343)/2;
  //Serial.print("Right Distance: ");
  //Serial.println(r_distance);
  delay(100);

  return fm1_distance;
}

float FiveSensors::getFM2SensorDist() {
  //Left sensor
  digitalWrite(fm2_trig, LOW);
  delayMicroseconds(2);
  digitalWrite(fm2_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(fm2_trig, LOW);

  float fm2_duration = pulseIn(fm2_echo, HIGH);
  float fm2_distance = (fm2_duration*.0343)/2;
  delay(100);

  return fm2_distance;
}


float FiveSensors::checkSensor(int sensor) {
  if (sensor = 0) {
    return getFrontSensorDist();
  }
  else if (sensor = 1) {
    return getM1SensorDist();
  }
  else if (sensor = 2) {
    return getM2SensorDist();
  }
  else if (sensor = 3) {
    return getFM1SensorDist();
  }
  else {
    return getFM2SensorDist();
  }
}

bool FiveSensors::checkAllSensors() {
  if ((getFrontSensorDist() != 0) && (getFM1SensorDist() != 0) && (getFM2SensorDist() != 0) && (getM1SensorDist() != 0) && (getM2SensorDist() != 0)) {
    return true;
  }
  else {
    return false;
  }
}

