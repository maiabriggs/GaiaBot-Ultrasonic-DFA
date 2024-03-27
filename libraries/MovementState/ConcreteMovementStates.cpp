#include "ConcreteMovementStates.h"
#include "Robot.h"

void Stop::enter(Robot* robot)
{
	//Stop all motors
	Serial.println("Stopping");
    robot->movements.stop();
}

MovementState& Stop::getInstance()
{
	static Stop singleton;
	return singleton;
}


void TurnLeft::enter(Robot* robot)
{
	Serial.println("Turning left");
    robot->movements.left90();
}

MovementState& TurnLeft::getInstance()
{
	static TurnLeft singleton;
	return singleton;
}

void TurnRight::enter(Robot* robot)
{
	Serial.println("Turning right");
    robot->movements.right90();
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

void KeepRight::enter(Robot* robot)
{
	Serial.println("Keeping right");
    while (((fiveSensors.getFM1SensorDist !> 150) || (fiveSensors.getFM2SensorDist !> 150) || (fiveSensors.getFrontSensorDist !< 20))) {
        robot->movements.forward();
        if (fiveSensors.getM1SensorDist() < (15)) {
            Serial.println("I'm too close to the wall");
            robot->movements.veerLeft();
        } 
        else if (fiveSensors.getM1SensorDist() > (17)) {
            Serial.println("I'm too far from the wall");
            robot->movements.veerRight();
        }
    }
  }


void KeepLeft::enter(Robot* robot)
{
	Serial.println("Keeping left");
    while (((fiveSensors.getFM1SensorDist !> 150) || (fiveSensors.getFM2SensorDist !> 150) || (fiveSensors.getFrontSensorDist !< 20))) {
        robot->movements.forward();
        if (fiveSensors.getM2SensorDist() < (15)) {
            Serial.println("I'm too close to the wall");
            robot->movements.veerRight();
        }
        else if (fiveSensors.getM2SensorDist() > (17)) {
            Serial.println("I'm too far from the wall");
            robot->movements.veerLeft();
        }
    }
}


