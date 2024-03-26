#include "MovementState.h"
#include "Robot.h"

void MovementState::exit(Robot* robot) {
    //The robot will always stop when exitting a state
    robot->movements.stop();
}

void MovementState::toggle(Robot* robot, MovementState& nextState)
{
	// Low -> Medium
	robot->setState(nextState);
}