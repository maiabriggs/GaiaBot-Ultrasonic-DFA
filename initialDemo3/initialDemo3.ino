#include <HCSR04.h>
#include <FiveSensors.h>
#include <Movements.h>
#include <RoboClaw.h>
#include <Adafruit_NeoPixel.h>

int fTrig = 7;
int fEcho = 6;

int m2Trig = 9;
int m2Echo = 8;

int m1Trig = 3;
int m1Echo = 2;

int fm2Trig = 11;
int fm2Echo = 10;

int fm1Trig = 5;
int fm1Echo = 4;


float initM1Dist;
float initM2Dist;

float threshold = 3;

float turnThresh = 100;

int choice; // 1 is yes
bool state;
String dir;

int lastTurn = 0; // 0 if no turns, 1 if left, 2 if right

FiveSensors fiveSensors(fTrig, fEcho, m2Trig, m2Echo, m1Trig, m1Echo, fm1Trig, fm1Echo, fm2Trig, fm2Echo);
Movements movements; 

float f_distance, m1_distance, m2_distance, fm1_distance, fm2_distance; 
String currCommand;


void setup() {
  fiveSensors.begin();
  movements.begin();
  initM1Dist = fiveSensors.getM1SensorDist();
  initM2Dist = fiveSensors.getM2SensorDist();

  // initFM1Dis = fiveSensors.getFM1SensorDist();
  // initFM2Dis = fiveSensors.getFM2SensorDist();
}

void loop() {
  while (!fiveSensors.checkAllSensors()) {
    Serial.println("Not all sensors are plugged in!!!!");
  }

  Serial.println("Am I okay to start?");
  //Wait for user input
  while (Serial.available() == 0) {}
  choice = Serial.parseInt();
  if (choice == 1) {
    Serial.println("I'm headed off");
    state = true;
    while (state) {
      Serial.println("Moving forward");
      movements.forward();
      Serial.println("Left Sensor:");
      Serial.println(fiveSensors.getM2SensorDist());
      Serial.println("right Sensor:");
      Serial.println(fiveSensors.getM1SensorDist());
      if (checkForLeftPath()) {
        movements.stop();
        movements.left90();
        movements.stop();
        lastTurn = 1;
        allignM2();
      }
      else if (checkForRightPath()) {
        movements.stop();
        movements.right90();
        movements.stop();
        lastTurn = 2;
        allignM1();
      }
      checkPosition();
      stopFunc(); 
    }
  }
}
 

void checkPositionLeft() {
  Serial.println("Checking my position");
  if (fiveSensors.getM2SensorDist() < (initM2Dist - threshold)) {
    Serial.println("I'm too close to the wall");
    movements.veerRight();
  }
  else if (fiveSensors.getM2SensorDist() > (initM2Dist + threshold)) {
    Serial.println("I'm too far from the wall");
    movements.veerLeft();
  }
}

void checkPositionRight() {
  Serial.println("Checking my position");
  if (fiveSensors.getM1SensorDist() < (initM1Dist - threshold)) {
    Serial.println("I'm too close to the wall");
    movements.veerLeft();
  } 
  else if (fiveSensors.getM1SensorDist() > (initM1Dist + threshold)) {
   Serial.println("I'm too far from the wall");
    movements.veerRight();
  }
}

bool m1SensorsAreClose() {
  return abs(fiveSensors.getFM1SensorDist() - fiveSensors.getM1SensorDist()) <= 2;
}

bool m2SensorsAreClose() {
  return abs(fiveSensors.getFM2SensorDist() - fiveSensors.getM2SensorDist()) <= 2;
}

void allignM1() {
  Serial.println("alligning right side");
  if (fiveSensors.getFM1SensorDist() > fiveSensors.getM1SensorDist()) {
    Serial.println("rotating right");
    movements.stop();
    while (!m1SensorsAreClose()) {
      movements.rotateRight();
    }
    movements.stop();
  }
  else if (fiveSensors.getFM1SensorDist() < fiveSensors.getM1SensorDist()) {
    Serial.println("rotating left");
    movements.stop();
    while (!m1SensorsAreClose()) {
      movements.rotateLeft();
    }
    movements.stop();
  }
}

void allignM2() {
  Serial.println("alligning left side");
  if (fiveSensors.getFM2SensorDist() < fiveSensors.getM2SensorDist()) {
    Serial.println("rotating right");
    movements.stop();
    while (!m2SensorsAreClose()) {
      movements.rotateRight();
    }
    movements.stop();
  }
  else if (fiveSensors.getFM2SensorDist() > fiveSensors.getM2SensorDist()) {
    Serial.println("rotating left");
    movements.stop();
    while (!m2SensorsAreClose()) {
      movements.rotateLeft();
    }
    movements.stop();
  }
}

bool checkForLeftPath() {
  if (fiveSensors.getFM2SensorDist() > turnThresh) {
    movements.stop();
    delay(1500);
    Serial.println("Left might be clear, double-checking");
    if (fiveSensors.getFM2SensorDist() > turnThresh) {
      return true; // Left path available
    }
  }
  else {
    return false;
  }
}

bool checkForRightPath() {
  if (fiveSensors.getFM1SensorDist() > turnThresh) {
    movements.stop();
    delay(1500);
    Serial.println("Right might be clear, double-checking");
    if (fiveSensors.getFM1SensorDist() > turnThresh) {
      return true; // Right path available
    }
  }
  else {
    return false;
  }
}

bool frontClear() {
  return fiveSensors.getFrontSensorDist() > 30;
}

void stopFunc() {
  while (!frontClear()) {
        movements.stop();
        delay(500);
        Serial.print("There is something ");
        Serial.print(fiveSensors.getFrontSensorDist());
        Serial.println(" away");
  }
}

void checkPosition() {
  if (lastTurn == 1) {
    checkPositionLeft();
  }
  else if (lastTurn == 2) {
    checkPositionRight();
  }
}

void allign() {
  if (!m1SensorsAreClose()) {
    movements.stop();
    allignM1();
    }
  if (!m2SensorsAreClose()) {
    movements.stop();
    allignM2();
  }
}



