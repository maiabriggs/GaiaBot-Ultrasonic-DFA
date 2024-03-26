#include "ConcreteMovementStates.h"
#include "Robot.h"

void Stop::enter(Robot* robot)
{
	//Stop all motors
    robot->movements.stop();
}

void Stop::checkSensor(Robot* robot){}

MovementState& Stop::getInstance()
{
	static Stop singleton;
	return singleton;
}


void TurnLeft::enter(Robot* robot)
{
    robot->movements.left90();
}

void TurnLeft::checkSensor(Robot* robot){}


MovementState& TurnLeft::getInstance()
{
	static TurnLeft singleton;
	return singleton;
}

void TurnRight::enter(Robot* robot)
{
    robot->movements.right90();
}

void TurnRight::checkSensor(Robot* robot){}

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

void KeepLeft::checkSensor(Robot* robot){
    Serial.println("Checking my position");
    if (robot->fiveSensors.getM1SensorDist() < (10)) {
        Serial.println("I'm too close to the wall");
        robot->movements.veerLeft();
    } 
    else if ((robot->fiveSensors.getM1SensorDist() > 20) && (robot->fiveSensors.getM1SensorDist() < 150)) {
    Serial.println("I'm too far from the wall");
        robot->movements.veerRight();
    }
    else {
        
    }
}

MovementState& KeepRight::getInstance()
{
	static KeepRight singleton;
	return singleton;
}
