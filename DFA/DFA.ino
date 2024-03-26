#include <HCSR04.h>
#include <FiveSensors.h>
#include <Movements.h>
#include <RoboClaw.h>
#include <Dijkstras.h>
#include <ArduinoSTL.h>


Robot robot(fTrig, fEcho, m2Trig, m2Echo, m1Trig, m1Echo, fm1Trig, fm1Echo, fm2Trig, fm2Echo);
Movements movements; 

void setup() {
    // Initialize serial communication for debugging
    Serial.begin(9600);
    
    // Add any additional setup code here
 Serial.begin(9600);
}

void loop() {
    // Example: Switch from Stop to TurnLeft state
    // Define the next state to switch to
    TurnLeft& nextTurnLeftState = TurnLeft::getInstance();
    
    // Toggle to the next state
    robot.toggle(nextTurnLeftState);
    
    // Add a delay or other code here if needed
    delay(1000); // Delay for 1 second
    
    // After the switch, you can continue with other operations or switch to another state
    
    // Example: Switch back to Stop state
    Stop& nextStopState = Stop::getInstance();
    robot.toggle(nextStopState);
    
    // Add a delay or other code here if needed
    delay(1000); // Delay for 1 second
    
    // Loop continues, performing state transitions or other operations
}
