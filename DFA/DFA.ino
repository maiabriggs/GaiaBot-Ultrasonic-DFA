#include "Robot.h"

// Pin configuration for the robot's sensors
const int f_trigPin = 2;
const int f_echoPin = 3;
const int m2_trigPin = 4;
const int m2_echoPin = 5;
const int m1_trigPin = 6;
const int m1_echoPin = 7;
const int fm1_trigPin = 8;
const int fm1_echoPin = 9;
const int fm2_trigPin = 10;
const int fm2_echoPin = 11;

// Define the start and end nodes for navigation
const int startNode = 0; // Start node
const int endNode = 6;   // End node

// Create an instance of the Robot class
Robot myRobot(f_trigPin, f_echoPin, m2_trigPin, m2_echoPin, m1_trigPin, m1_echoPin, fm1_trigPin, fm1_echoPin, fm2_trigPin, fm2_echoPin);

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Call the navigate function to find the shortest path and traverse it
  myRobot.navigate(startNode, endNode);
}

void loop() {
  // Empty loop
}
