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
int startNode; // Start node
int endNode;   // End node

// Create an instance of the Robot class
Robot myRobot(fTrig, fEcho, m2Trig, m2Echo, m1Trig, m1Echo, fm1Trig, fm1Echo, fm2Trig, fm2Echo);

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  myRobot.setupIMU();
}

void loop() {
  bool validInput = false;
  
  // Prompt user to input start and end nodes
  Serial.println("Enter start node:");
  while (!validInput) {
    // Wait for user input
    while (!Serial.available()) {
      // Allow other tasks to execute while waiting for input
      delay(10);
    }
    // Read start node from serial monitor
    startNode = Serial.parseInt();
    if (Serial.read() == '\n') {
      validInput = true;
    }
    // Clear input buffer
    while (Serial.available()) {
      Serial.read();
    }
  }

  validInput = false;

  Serial.println("Enter end node:");
  while (!validInput) {
    // Wait for user input
    while (!Serial.available()) {
      // Allow other tasks to execute while waiting for input
      delay(10);
    }
    // Read end node from serial monitor
    endNode = Serial.parseInt();
    if (Serial.read() == '\n') {
      validInput = true;
    }
    // Clear input buffer
    while (Serial.available()) {
      Serial.read();
    }
  }

  // Call the navigate function to find the shortest path and traverse it
  myRobot.navigate(startNode, endNode);

  // Wait for user input to continue
  Serial.println("Navigation complete. Press any key to continue.");
  while (!Serial.available()) {
    // Allow other tasks to execute while waiting for input
    delay(10);
  }
  // Clear input buffer
  while (Serial.available()) {
    Serial.read();
  }
}
