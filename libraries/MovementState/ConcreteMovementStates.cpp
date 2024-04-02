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
    while ((!(robot->fiveSensors.getFM1SensorDist() > 150) && robot->dontCheckRight == false) | (!(robot->fiveSensors.getFM2SensorDist() > 150) && robot->dontCheckLeft == false) | (!(robot->fiveSensors.getFrontSensorDist() < 70) && robot->dontCheckStraight == false)) {
        robot->movements.forward();
        if (robot->fiveSensors.getM1SensorDist() < (15)) {
			delay(100);
			Serial.println(robot->fiveSensors.getM1SensorDist());
			if (robot->fiveSensors.getM1SensorDist() < (15)) {
				robot->movements.stop();
				Serial.println("I'm too far from the wall");
				Serial.println(robot->fiveSensors.getM1SensorDist());
				robot->movements.veerLeft();
			}
        } 
        else if ((robot->fiveSensors.getM1SensorDist() > 40) && (robot->fiveSensors.getM1SensorDist() < 80)) {
			delay(100);
			if ((robot->fiveSensors.getM1SensorDist() > 40) && (robot->fiveSensors.getM1SensorDist() < 80)) {
				robot->movements.stop();
				Serial.println("I'm too far from the wall");
				Serial.println(robot->fiveSensors.getM1SensorDist());
				robot->movements.veerRight();
			}
        }
		else if (( ((robot->fiveSensors.getFM1SensorDist() > 150) && robot->dontCheckRight == false) | ((robot->fiveSensors.getFM2SensorDist() > 150) && robot->dontCheckLeft == false)) | ((robot->fiveSensors.getFrontSensorDist() < 70) && robot->dontCheckStraight == false)) {
			robot->movements.stop();
			delay(1000);
			break;
		}
    }
  }


void KeepLeft::enter(Robot* robot)
{
	Serial.println("Keeping left");
    while ((!(robot->fiveSensors.getFM1SensorDist() > 150) && robot->dontCheckRight == false) | (!(robot->fiveSensors.getFM2SensorDist() > 150) && robot->dontCheckLeft == false) | (!(robot->fiveSensors.getFrontSensorDist() < 70) && robot->dontCheckStraight == false)) {
		robot->movements.forward();
        if (robot->getSensorM2() < (20)) {

			delay(100);
			if (robot->getSensorM2() < (20)) {
				Serial.println("I'm too close to the wall");
				Serial.println(robot->getSensorM2());
            	robot->movements.veerRight();
			}
        }
        else if (robot->getSensorM2() > (25) && robot->getSensorM2() < 80) {
			delay(100);
			if (robot->getSensorM2() > (25) && robot->getSensorM2() < 80) {
				Serial.println("I'm too far from the wall");
				Serial.println(robot->getSensorM2());
				robot->movements.veerLeft();
			}
        }
		else if (( ((robot->fiveSensors.getFM1SensorDist() > 150) && robot->dontCheckRight == false) | ((robot->fiveSensors.getFM2SensorDist() > 150) && robot->dontCheckLeft == false)) | ((robot->fiveSensors.getFrontSensorDist() < 70) && robot->dontCheckStraight == false)) {
			robot->movements.stop();
			delay(1000);
			break;
		}
    }
}

//Towards Informatics Forum
void FaceNorth::enter(Robot* robot)
{
	Serial.println("Facing North");
	while (true) {
		if (robot->getHeading() > 169 && robot->getHeading() < 176) {
			robot->movements.stop();
			delay(200);
			if (robot->getHeading() > 160 && robot->getHeading() < 180) {
				break;
			}
		}
		else {
			robot->movements.rotateLeft();
		}

	}
}

MovementState& FaceNorth::getInstance()
{
	static FaceNorth singleton;
	return singleton;
}

void FaceSouth::enter(Robot* robot)
{
	Serial.println("Facing South");
	while (true) {
		if (robot->getHeading() >= 355) {
			robot->movements.stop();
			delay(200);
			if (robot->getHeading() >= 355) {
				break;
			}
		}
		else {
			robot->movements.rotateLeft();
		}
	}
}


MovementState& FaceSouth::getInstance()
{
	static FaceSouth singleton;
	return singleton;
}

void FaceEast::enter(Robot* robot)
{
	Serial.println("Facing East");
	while (true) {
		Serial.println(robot->getHeading());
		if (robot->getHeading() >= 270 && robot->getHeading() <= 300) {
			robot->movements.stop();
			delay(200);
			if (robot->getHeading() >= 270 && robot->getHeading() <= 300) {
				break;
			}
		}
		else {
			robot->movements.rotateLeft();
		}

	}
}

MovementState& FaceEast::getInstance()
{
	static FaceEast singleton;
	return singleton;
}

void FaceWest::enter(Robot* robot)
{
	Serial.println("Facing West");
	while (true) {
		Serial.println(robot->getHeading());
		if (robot->getHeading() >= 50 && robot->getHeading() <= 60) {
			robot->movements.stop();
			delay(200);
			Serial.println(robot->getHeading());
			if (robot->getHeading() >= 40 && robot->getHeading() <= 120) {
				break;
			}
		}
		else {
			robot->movements.rotateLeft();
		}

	}
}

MovementState& FaceWest::getInstance()
{
	static FaceWest singleton;
	return singleton;
}