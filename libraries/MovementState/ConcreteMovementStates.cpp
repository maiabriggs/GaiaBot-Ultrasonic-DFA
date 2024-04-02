#include "ConcreteMovementStates.h"
#include "Robot.h"
#include "Movements.h"
#include "FiveSensors.h"

const int leftCheckDist = 150;
const int rightCheckDist = 150;
const int frontCheckDist = 70;
const int fLeftCheckDist = 25;
const int fRightCheckDist = 25;

const int WEST = 75;
const int EAST = 285;
const int NORTH = 170;
const int SOUTH = 358;

const int WEST_LOWER = 50;
const int EAST_LOWER = 275;
const int NORTH_LOWER = 160;
const int SOUTH_LOWER = 355;

const int WEST_HIGHER = 80;
const int EAST_HIGHER = 290;
const int NORTH_HIGHER = 180;
const int SOUTH_HIGHER = 4;

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
	//Initial forward movement to clear any open space
	robot->movements.forward();
	delay(100);
    while ((!(robot->fiveSensors.getM1SensorDist() > rightCheckDist) && robot->dontCheckRight == false) | (!(robot->fiveSensors.getM2SensorDist() > leftCheckDist) && robot->dontCheckLeft == false) | (!(robot->fiveSensors.getFrontSensorDist() < frontCheckDist) && robot->dontCheckStraight == false)) {
        robot->movements.forward();

		//NORTH
		if (robot->dir == 0 && robot->inRange(NORTH_LOWER, WEST_HIGHER, robot->getHeading())) {
			delay(10);
			if (robot->dir == 0 && robot->inRange(NORTH_LOWER, WEST_HIGHER, robot->getHeading())) {
				Serial.println("veering left to head north");
				robot->movements.veerLeft();
			}
			
		}
		else if (robot->dir == 0 && robot->inRange(NORTH_HIGHER, EAST_LOWER, robot->getHeading())) {
			delay(10);
			if (robot->dir == 0 && robot->inRange(NORTH_HIGHER, EAST_LOWER, robot->getHeading())){
				Serial.println("veering right to head north");
				robot->movements.veerRight();
			}
		}
		//SOUTH
		else if (robot->dir == 1 && robot->inRange(SOUTH_LOWER, EAST_HIGHER, robot->getHeading())) {
			delay(10);
			if (robot->dir == 1 && robot->inRange(SOUTH_LOWER, EAST_HIGHER, robot->getHeading())) {
				Serial.println("veering left to head south");
				robot->movements.veerLeft();
			}
			
		}
		else if (robot->dir == 1 && robot->inRange(SOUTH_HIGHER, WEST_LOWER, robot->getHeading())) {
			delay(10);
			if (robot->dir == 1 && robot->inRange(SOUTH_HIGHER, WEST_LOWER, robot->getHeading())){
				Serial.println("veering right to head south");
				robot->movements.veerRight();
			}
		}

		//EAST
		else if (robot->dir == 2 && robot->inRange(EAST_LOWER, SOUTH_HIGHER, robot->getHeading())) {
			delay(10);
			if (robot->dir == 2 && robot->inRange(EAST_LOWER, SOUTH_HIGHER, robot->getHeading())) {
				Serial.println("veering left to head East");
				robot->movements.veerLeft();
			}
			
		}
		else if (robot->dir == 2 && robot->inRange(EAST_HIGHER, NORTH_LOWER, robot->getHeading())) {
			delay(10);
			if (robot->dir == 2 && robot->inRange(EAST_HIGHER, NORTH_LOWER, robot->getHeading())){
				Serial.println("veering right to head East");
				robot->movements.veerRight();
			}
		}

		//WEST
		else if (robot->dir == 2 && robot->inRange(WEST_LOWER, NORTH_HIGHER, robot->getHeading())) {
			delay(10);
			if (robot->dir == 2 && robot->inRange(WEST_LOWER, NORTH_HIGHER, robot->getHeading())) {
				Serial.println("veering left to head west");
				robot->movements.veerLeft();
			}
			
		}
		else if (robot->dir == 2 && robot->inRange(WEST_HIGHER, SOUTH_LOWER, robot->getHeading())) {
			delay(10);
			if (robot->dir == 2 && robot->inRange(WEST_HIGHER, SOUTH_LOWER, robot->getHeading())){
				Serial.println("veering right to head west");
				robot->movements.veerRight();
			}
		}
        
		//----SENSOR WALL CHECKING-----
		else if (robot->fiveSensors.getM1SensorDist() < (20)) {
			delay(10);
			Serial.println(robot->fiveSensors.getM1SensorDist());
			if (robot->fiveSensors.getM1SensorDist() < (20)) {
				Serial.println("I'm too close to the Right wall");
				Serial.println(robot->fiveSensors.getM1SensorDist());
				robot->movements.veerLeft();
			}
        } 
        // else if ((robot->fiveSensors.getM1SensorDist() > 25) && (robot->fiveSensors.getM1SensorDist() < 80)) {
		// 	delay(10);
		// 	if ((robot->fiveSensors.getM1SensorDist() > 25) && (robot->fiveSensors.getM1SensorDist() < 80)) {
		// 		Serial.println("I'm too far from the wall");
		// 		Serial.println(robot->fiveSensors.getM1SensorDist());
		// 		robot->movements.veerRight();
		// 	}
        // }

		else if (robot->fiveSensors.getM2SensorDist() < (20)) {
			delay(10);
			Serial.println(robot->fiveSensors.getM2SensorDist());
			if (robot->fiveSensors.getM2SensorDist() < (20)) {
				Serial.println("I'm too close to the Left wall");
				Serial.println(robot->fiveSensors.getM2SensorDist());
				robot->movements.veerRight();
			}
        } 
		
		//----END CHECK------
		else if ( ( ((robot->fiveSensors.getM1SensorDist() > rightCheckDist) && robot->dontCheckRight == false && robot->fiveSensors.getFM1SensorDist() <= fRightCheckDist) | ((robot->fiveSensors.getM2SensorDist() > leftCheckDist) && robot->dontCheckLeft == false && robot->fiveSensors.getFM2SensorDist() <= fLeftCheckDist) | ((robot->fiveSensors.getFrontSensorDist() < frontCheckDist) && robot->dontCheckStraight == false) ) ) {
			robot->movements.stop();
			delay(1000);
			break;
		}
    }
  }


void KeepLeft::enter(Robot* robot)
{
	Serial.println("Keeping left");
	//Initial forward movement to clear any open space
	robot->movements.forward();
	delay(100);
    while ((!(robot->fiveSensors.getM1SensorDist() > rightCheckDist) && robot->dontCheckRight == false) | (!(robot->fiveSensors.getM2SensorDist() > leftCheckDist) && robot->dontCheckLeft == false) | (!(robot->fiveSensors.getFrontSensorDist() < frontCheckDist) && robot->dontCheckStraight == false)) {
		robot->movements.forward();
		//NORTH
		if (robot->dir == 0 && robot->inRange(NORTH_LOWER, WEST_HIGHER, robot->getHeading())) {
			delay(10);
			if (robot->dir == 0 && robot->inRange(NORTH_LOWER, WEST_HIGHER, robot->getHeading())) {
				Serial.println("veering right to head north");
				robot->movements.veerRight();
			}
			
		}
		else if (robot->dir == 0 && robot->inRange(NORTH_HIGHER, EAST_LOWER, robot->getHeading())) {
			delay(10);
			if (robot->dir == 0 && robot->inRange(NORTH_HIGHER, EAST_LOWER, robot->getHeading())){
				Serial.println("veering left to head north");
				robot->movements.veerLeft();
			}
		}
		//SOUTH
		else if (robot->dir == 1 && robot->inRange(SOUTH_LOWER, EAST_HIGHER, robot->getHeading())) {
			delay(10);
			if (robot->dir == 1 && robot->inRange(SOUTH_LOWER, EAST_HIGHER, robot->getHeading())) {
				Serial.println("veering right to head south");
				robot->movements.veerRight();
			}
			
		}
		else if (robot->dir == 1 && robot->inRange(SOUTH_HIGHER, WEST_LOWER, robot->getHeading())) {
			delay(10);
			if (robot->dir == 1 && robot->inRange(SOUTH_HIGHER, WEST_LOWER, robot->getHeading())){
				Serial.println("veering Left to head south");
				robot->movements.veerLeft();
			}
		}

		//EAST
		else if (robot->dir == 2 && robot->inRange(EAST_LOWER, SOUTH_HIGHER, robot->getHeading())) {
			delay(10);
			if (robot->dir == 2 && robot->inRange(EAST_LOWER, SOUTH_HIGHER, robot->getHeading())) {
				Serial.println("veering left to head East");
				robot->movements.veerLeft();
			}
			
		}
		else if (robot->dir == 2 && robot->inRange(EAST_HIGHER, NORTH_LOWER, robot->getHeading())) {
			delay(10);
			if (robot->dir == 2 && robot->inRange(EAST_HIGHER, NORTH_LOWER, robot->getHeading())){
				Serial.println("veering right to head East");
				robot->movements.veerRight();
			}
		}

		//WEST
		else if (robot->dir == 2 && robot->inRange(WEST_LOWER, NORTH_HIGHER, robot->getHeading())) {
			delay(10);
			if (robot->dir == 2 && robot->inRange(WEST_LOWER, NORTH_HIGHER, robot->getHeading())) {
				Serial.println("veering left to head west");
				robot->movements.veerLeft();
			}
			
		}
		else if (robot->dir == 2 && robot->inRange(WEST_HIGHER, SOUTH_LOWER, robot->getHeading())) {
			delay(10);
			if (robot->dir == 2 && robot->inRange(WEST_HIGHER, SOUTH_LOWER, robot->getHeading())){
				Serial.println("veering right to head west");
				robot->movements.veerRight();
			}
		}

		//SENSORS
        else if (robot->getSensorM2() < (20)) {
			delay(10);
			if (robot->getSensorM2() < (20)) {
				Serial.println("I'm too close to the left wall");
				Serial.println(robot->getSensorM2());
            	robot->movements.veerRight();
			}
        }

		//----SENSOR WALL CHECKING-----
		else if (robot->fiveSensors.getM1SensorDist() < (20)) {
			delay(10);
			Serial.println(robot->fiveSensors.getM1SensorDist());
			if (robot->fiveSensors.getM1SensorDist() < (20)) {
				Serial.println("I'm too close to the Right wall");
				Serial.println(robot->fiveSensors.getM1SensorDist());
				robot->movements.veerLeft();
			}
        } 

        // else if (robot->getSensorM2() > (25) && robot->getSensorM2() < 80) {
		// 	delay(10);
		// 	if (robot->getSensorM2() > (25) && robot->getSensorM2() < 80) {
		// 		Serial.println("I'm too far from the wall");
		// 		Serial.println(robot->getSensorM2());
		// 		robot->movements.veerLeft();
		// 	}
		
        // //----END CHECK------
		// }
		else if (( ((robot->fiveSensors.getM1SensorDist() > rightCheckDist) && robot->dontCheckRight == false && robot->fiveSensors.getFM1SensorDist() <= fRightCheckDist) | ((robot->fiveSensors.getM2SensorDist() > leftCheckDist) && robot->dontCheckLeft == false && robot->fiveSensors.getFM2SensorDist() <= leftCheckDist) | ((robot->fiveSensors.getFrontSensorDist() < frontCheckDist) && robot->dontCheckStraight == false) )) {
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

