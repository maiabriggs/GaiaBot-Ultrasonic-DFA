#include "Arduino.h"
#include "Robot.h"
#include "RoboClaw.h"
#include "MovementState.h"
#include "Movements.h"
#include <FiveSensors.h>
#include "ConcreteMovementStates.h"


Movements movements;

int sitch[13][2] = {
    {0, 1},
    {1, 2},
    {1, 6},
    {2, 1},
    {6, 1},
    {2, 3},
    {3, 2},
    {3, 4},
    {4, 3},
    {5, 4},
    {4, 5},
    {6, 5},
    {5, 6}
};



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

void Robot::toggle(MovementState* nextState)
{
    // Delegate the task of determining the next state to the current state
    currentState->toggle(this, *nextState);
}


//------STATE STORAGE-------



// Define a function to initialize a StateList structure for a given node
void Robot::initStateListForNode(int scenario) {

    // Define the sequence of states based on the node

    switch (scenario) {

		//Start -> 1
        case 0:
            // Define the states for node 1
            toggle(&KeepLeft::getInstance());
            toggle(&TurnLeft::getInstance());
			toggle(&Stop::getInstance());
            break;

		//1 -> 2
        case 1:
            toggle(&TurnLeft::getInstance());
            toggle(&KeepLeft::getInstance());
			toggle(&Stop::getInstance());
            break;

		//1 -> 6
		case 2:
            toggle(&KeepRight::getInstance());
			toggle(&TurnLeft::getInstance());
			toggle(&Stop::getInstance());
            break;

		//2 -> 1
		case 3:
            toggle(&KeepRight::getInstance());
			toggle(&TurnRight::getInstance());
			toggle(&Stop::getInstance());
            break;
		
		//6 -> 1
		case 4:
            toggle(&TurnRight::getInstance());
			toggle(&Stop::getInstance());
            break;

		//2 -> 3
		case 5:
            toggle(&KeepLeft::getInstance());
			toggle(&TurnRight::getInstance());
			toggle(&Stop::getInstance());
            break;

		//3 -> 2
		case 6:
            toggle(&TurnRight::getInstance());
			toggle(&Stop::getInstance());
            break;
		
		//3 -> 4
		case 7:
            toggle(&KeepLeft::getInstance());
			toggle(&TurnRight::getInstance());
			toggle(&Stop::getInstance());
            break;
		
		//4 -> 3
		case 8:
            toggle(&KeepRight::getInstance());
			toggle(&TurnLeft::getInstance());
			toggle(&Stop::getInstance());
            break;
		
		//5 -> 4
		case 9:	
			toggle(&KeepRight::getInstance());
			toggle(&TurnLeft::getInstance());
			toggle(&Stop::getInstance());
            break;
		
		//4 -> 5
		case 10:
            toggle(&KeepLeft::getInstance());
			toggle(&TurnRight::getInstance());
			toggle(&Stop::getInstance());
            break;

		//6 -> 5
		case 11:
            toggle(&KeepRight::getInstance());
			toggle(&TurnLeft::getInstance());
			toggle(&Stop::getInstance());
            break;

		//5 -> 6
		case 12:
            toggle(&KeepLeft::getInstance());
			toggle(&TurnRight::getInstance());
			toggle(&Stop::getInstance());
            break;

        default:
            toggle(&Stop::getInstance());
            break;
    }
}

void Robot::traverseToNode(int currNode, int nextNode) {
	int scenario = 14;

    // Iterate through the list of states and perform actions
    for (int i = 0; i < 13; ++i) {
		if ((sitch[i][0] == currNode && sitch[i][1] == nextNode)) {
			scenario = i;
		}
    }
	initStateListForNode(scenario);
}

