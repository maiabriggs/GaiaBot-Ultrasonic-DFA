#include <HCSR04.h>
#include <FiveSensors.h>
#include <Movements.h>
#include <RoboClaw.h>
#include <Robot.h>
#include <MovementState.h>
#include "ConcreteMovementStates.h"

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

Robot robot(fTrig, fEcho, m2Trig, m2Echo, m1Trig, m1Echo, fm1Trig, fm1Echo, fm2Trig, fm2Echo);

void setup() {
    // Initialize serial communication for debugging
    Serial.begin(9600);
    
    // Add any additional setup code here
}

void loop() {
    // Example: Switch from Stop to TurnLeft state
    // Define the next state to switch to
    MovementState& nextTurnLeftState = TurnLeft::getInstance();
    
    // Toggle to the next state
    robot.toggle(nextTurnLeftState);
    
    // Add a delay or other code here if needed
    delay(1000); // Delay for 1 second
    
    // After the switch, you can continue with other operations or switch to another state
    
    // Example: Switch back to Stop state
    MovementState& nextStopState = Stop::getInstance();
    robot.toggle(nextStopState);
    
    // Add a delay or other code here if needed
    delay(1000); // Delay for 1 second
    
    // Loop continues, performing state transitions or other operations
}
