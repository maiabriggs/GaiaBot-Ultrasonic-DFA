#include "ConcreteMovementStates.h"
#include "Robot.h"
#include "Movements.h"
#include "FiveSensors.h"

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
    while (!(robot->fiveSensors.getFM1SensorDist() > 150) | !(robot->fiveSensors.getFM2SensorDist() > 150) | !(robot->fiveSensors.getFrontSensorDist() < 20)) {
        robot->movements.forward();
        if (robot->fiveSensors.getM1SensorDist() < (15)) {
			robot->movements.stop();
			delay(100);
			Serial.println(robot->fiveSensors.getM1SensorDist());
			if (robot->fiveSensors.getM1SensorDist() < (15)) {
				robot->movements.stop();
				Serial.println("I'm too far from the wall");
				Serial.println(robot->fiveSensors.getM1SensorDist());
				robot->movements.veerLeft();
			}
        } 
        else if ((robot->fiveSensors.getM1SensorDist() > 17) && (robot->fiveSensors.getM1SensorDist() < 50)) {
			robot->movements.stop();
			delay(100);
			if ((robot->fiveSensors.getM1SensorDist() > 17) && (robot->fiveSensors.getM1SensorDist() < 50)) {
				robot->movements.stop();
				Serial.println("I'm too far from the wall");
				Serial.println(robot->fiveSensors.getM1SensorDist());
				robot->movements.veerRight();
			}
        }
		else if ((robot->fiveSensors.getFM1SensorDist() > 150) | (robot->fiveSensors.getFM2SensorDist() > 150)){
			robot->movements.stop();
			delay(1000);
			break;
		}
    }
  }


void KeepLeft::enter(Robot* robot)
{
	Serial.println("Keeping left");
    while (!(robot->fiveSensors.getFM1SensorDist() > 150) | !(robot->fiveSensors.getFM2SensorDist() > 150) | !(robot->fiveSensors.getFrontSensorDist() < 20)) {
        robot->movements.forward();
        if (robot->getSensorM2() < (15)) {
			robot->movements.stop();
			delay(100);
			if (robot->getSensorM2() < (15)) {
				Serial.println("I'm too close to the wall");
				Serial.println(robot->getSensorM2());
            	robot->movements.veerRight();
			}
        }
        else if (robot->getSensorM2() > (17) && robot->getSensorM2() < 50) {
			robot->movements.stop();
			delay(100);
			if (robot->getSensorM2() > (17) && robot->getSensorM2() < 50) {
				Serial.println("I'm too far from the wall");
				Serial.println(robot->getSensorM2());
				robot->movements.veerLeft();
			}
        }
		else if ((robot->fiveSensors.getFM1SensorDist() > 150) | (robot->fiveSensors.getFM2SensorDist() > 150)){
			robot->movements.stop();
			delay(1000);
			break;
		}
    }
}