#include "Robot.h"

// Define the pins for your robot's sensors and motors
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

// Create an instance of the Robot class
Robot robot(f_trigPin, f_echoPin, m2_trigPin, m2_echoPin, m1_trigPin, m1_echoPin, fm1_trigPin, fm1_echoPin, fm2_trigPin, fm2_echoPin);

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Test state traversal from node 1 to node 2
  Serial.println("Traversing from node 1 to node 2:");
  robot.traverseToNode(1, 2);
  delay(2000);

  // Test state traversal from node 2 to node 1
  Serial.println("Traversing from node 2 to node 1:");
  robot.traverseToNode(2, 1);
  delay(2000);

  // Test state traversal from node 3 to node 4
  Serial.println("Traversing from node 3 to node 4:");
  robot.traverseToNode(3, 4);
  delay(2000);

  // Add more test cases as needed
  
}
