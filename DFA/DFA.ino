#include "Robot.h"
// #include "FiveSensors.h"

// Pin configuration for the robot's sensors
int fTrig = 7;
int fEcho = 6;

int m2Trig = 9;
int m2Echo = 8;

int m1Trig = 3;
int m1Echo = 2;

int fm2Trig = 10;
int fm2Echo = 11;

int fm1Trig = 5;
int fm1Echo = 4;

// Define the start and end nodes for navigation
const int startNode = 0; // Start node
const int endNode = 6;   // End node

// Create an instance of the Robot class
Robot myRobot(fTrig, fEcho, m2Trig, m2Echo, m1Trig, m1Echo, fm1Trig, fm1Echo, fm2Trig, fm2Echo);

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  // fiveSensors.begin(fTrig, fEcho, m2Trig, m2Echo, m1Trig, m1Echo, fm1Trig, fm1Echo, fm2Trig, fm2Echo);
  // Serial.println(fiveSensors.getM2SensorDist());
  myRobot.setupIMU();
  // Call the navigate function to find the shortest path and traverse it
  myRobot.navigate(startNode, endNode);
}

void loop() {
  // Empty loop
}
