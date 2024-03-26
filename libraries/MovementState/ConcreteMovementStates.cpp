#include "ConcreteMovementStates.h"

void Stop::enter(Robot* robot)
{
	//Stop all motors
    robot->movements.stop();
}

MovementState& Stop::getInstance()
{
	static Stop singleton;
	return singleton;
}


void TurnLeft::enter(Robot* robot)
{
    robot->movements.left();
}

MovementState& TurnLeft::getInstance()
{
	static TurnLeft singleton;
	return singleton;
}

void TurnRight::enter(Robot* robot)
{
    robot->movements.right();
}

MovementState& TurnRight::getInstance()
{
	static TurnRight singleton;
	return singleton;
}


MovementState& KeepLeft::getInstance()
{
	static KeepLeft singleton;
	return singleton;
}

MovementState& KeepRight::getInstance()
{
	static KeepRight singleton;
	return singleton;
}