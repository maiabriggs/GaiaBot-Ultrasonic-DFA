#include "Arduino.h"
#include "Robot.h"
#include "RoboClaw.h"
#include "MovementState.h"
#include "Movements.h"
#include <FiveSensors.h>
#include "ConcreteMovementStates.h"

Movements movements;


Robot::Robot(int f_trigPin, int f_echoPin, int m2_trigPin, int m2_echoPin, int m1_trigPin, int m1_echoPin, int fm1_trigPin, int fm1_echoPin, int fm2_trigPin, int fm2_echoPin)
{
    movements.begin();

	//Robot is initially still
	currentState = &Stop::getInstance();
   
}

void Robot::setState(MovementState& newState)
{
	currentState->exit(this);  // do something before we change state
	currentState = &newState;  // actually change states now
	currentState->enter(this); // do something after we change state
}

void Robot::toggle(MovementState& nextState)
{
	// Delegate the task of determining the next state to the current state
	currentState->toggle(this, nextState);
}
