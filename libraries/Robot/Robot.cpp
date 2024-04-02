#include "Arduino.h"
#include "Robot.h"
#include "RoboClaw.h"
#include "MovementState.h"
#include "Movements.h"
#include <FiveSensors.h>
#include "ConcreteMovementStates.h"
#include "Dijkstras.h" 

//RoboClaw is plugged into ->


//IMU INCLUDES
#include "AK09918.h"
#include "ICM20600.h"
#include <Wire.h>

Movements movements;
FiveSensors fiveSensors;

bool dontCheckLeft;
bool dontCheckRight;

//IMU 
AK09918_err_type_t err;
int32_t x, y, z;
AK09918 ak09918;
ICM20600 icm20600(true);
int16_t acc_x, acc_y, acc_z;
int16_t gyro_x, gyro_y, gyro_z;
int32_t offset_x, offset_y, offset_z;
double roll, pitch;
// Find the magnetic declination at your location
// http://www.magnetic-declination.com/
double declination_shenzhen = -0.45;

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
    fiveSensors.begin(f_trigPin, f_echoPin, m2_trigPin, m2_echoPin, m1_trigPin, m1_echoPin, fm1_trigPin, fm1_echoPin, fm2_trigPin, fm2_echoPin);
	//Robot is initially still
	currentState = &Stop::getInstance();
    dontCheckLeft = false;
    dontCheckRight = false;
    dontCheckStraight = false;
}

void Robot::setupIMU(){
    Wire.begin();

    err = ak09918.initialize();
    icm20600.initialize();
    ak09918.switchMode(AK09918_POWER_DOWN);
    ak09918.switchMode(AK09918_CONTINUOUS_100HZ);
    Serial.begin(9600);

    err = ak09918.isDataReady();
    while (err != AK09918_ERR_OK) {
        Serial.println("Re-plug in IMU I can't detect it");
        delay(100);
        err = ak09918.isDataReady();
    }

    Serial.println("Start figure-8 calibration after 2 seconds.");
    delay(2000);
    movements.rotateRight();
    calibrate(10000, &offset_x, &offset_y, &offset_z);
    movements.stop();
    Serial.println("");
    movements.stop();
    moveToStartPosition();
}

void Robot::calibrate(uint32_t timeout, int32_t* offsetx, int32_t* offsety, int32_t* offsetz) {
    int32_t value_x_min = 0;
    int32_t value_x_max = 0;
    int32_t value_y_min = 0;
    int32_t value_y_max = 0;
    int32_t value_z_min = 0;
    int32_t value_z_max = 0;
    uint32_t timeStart = 0;

    ak09918.getData(&x, &y, &z);

    value_x_min = x;
    value_x_max = x;
    value_y_min = y;
    value_y_max = y;
    value_z_min = z;
    value_z_max = z;
    delay(100);

    timeStart = millis();
    int count = 0;
    while ((millis() - timeStart) < timeout) {
        
        ak09918.getData(&x, &y, &z);
        /* Update x-Axis max/min value */
        if (value_x_min > x) {
            value_x_min = x;
            // Serial.print("Update value_x_min: ");
            // Serial.println(value_x_min);

        } else if (value_x_max < x) {
            value_x_max = x;
            // Serial.print("update value_x_max: ");
            // Serial.println(value_x_max);
        }

        /* Update y-Axis max/min value */
        if (value_y_min > y) {
            value_y_min = y;
            // Serial.print("Update value_y_min: ");
            // Serial.println(value_y_min);

        } else if (value_y_max < y) {
            value_y_max = y;
            // Serial.print("update value_y_max: ");
            // Serial.println(value_y_max);
        }

        /* Update z-Axis max/min value */
        if (value_z_min > z) {
            value_z_min = z;
            // Serial.print("Update value_z_min: ");
            // Serial.println(value_z_min);

        } else if (value_z_max < z) {
            value_z_max = z;
            // Serial.print("update value_z_max: ");
            // Serial.println(value_z_max);
        }
        
        Serial.print(".");
        delay(100);
    }
    movements.stop();

    *offsetx = value_x_min + (value_x_max - value_x_min) / 2;
    *offsety = value_y_min + (value_y_max - value_y_min) / 2;
    *offsetz = value_z_min + (value_z_max - value_z_min) / 2;
}

void Robot::moveToStartPosition() {
    while (getHeading() < 355){
        movements.rotateLeft();
    }
    movements.stop();
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

		//0 -> 1
        case 0:
            dontCheckLeft = false;
            dontCheckRight = false;
            dontCheckStraight = false;
            // Define the states for node 1
            toggle(&FaceSouth::getInstance());
            toggle(&KeepLeft::getInstance());
			toggle(&FaceEast::getInstance());
            toggle(&Stop::getInstance());
            break;

		//1 -> 2
        case 1:
            dontCheckLeft = false;
            dontCheckRight = true;
            dontCheckStraight = true;
            toggle(&FaceEast::getInstance());
            toggle(&KeepRight::getInstance());
			toggle(&FaceNorth::getInstance());
            toggle(&KeepLeft::getInstance());
            toggle(&Stop::getInstance());
            break;

		//1 -> 6
		case 2:
            dontCheckLeft = true;
            dontCheckRight = false;
            dontCheckStraight = false;
            toggle(&FaceEast::getInstance());
            toggle(&KeepRight::getInstance());
			toggle(&FaceNorth::getInstance());
			toggle(&Stop::getInstance());
            break;

		//2 -> 1
		case 3:
            dontCheckLeft = true;
            dontCheckRight = false;
            dontCheckStraight = false;
            toggle(&FaceSouth::getInstance());
			toggle(&KeepRight::getInstance());
            toggle(&FaceWest::getInstance());
            toggle(&KeepLeft::getInstance());
			toggle(&Stop::getInstance());
            break;
		
		//6 -> 1
		case 4:
            dontCheckLeft = false;
            dontCheckRight = true;
            dontCheckStraight = false;
            toggle(&FaceWest::getInstance());
            toggle(&KeepLeft::getInstance());
			toggle(&Stop::getInstance());
            break;

		//2 -> 3
		case 5:
            dontCheckLeft = true;
            dontCheckRight = true;
            dontCheckStraight = false;
            toggle(&FaceEast::getInstance());
			toggle(&KeepLeft::getInstance());
			toggle(&Stop::getInstance());
            break;

		//3 -> 2
		case 6:
            dontCheckLeft = false;
            dontCheckRight = false;
            dontCheckStraight = false;
            toggle(&FaceWest::getInstance());
            toggle(&KeepLeft::getInstance());
			toggle(&Stop::getInstance());
            //DOUBLE CHECK - PIN
            break;
		
		//3 -> 4
		case 7:
            dontCheckLeft = false;
            dontCheckRight = true;
            dontCheckStraight = false;
            toggle(&FaceSouth::getInstance());
			toggle(&KeepLeft::getInstance());
			toggle(&Stop::getInstance());
            break;
		
		//4 -> 3
		case 8:
            dontCheckLeft = true;
            dontCheckRight = true;
            dontCheckStraight = false;
            toggle(&FaceNorth::getInstance());
			toggle(&KeepRight::getInstance());
			toggle(&Stop::getInstance());
            break;
		
		//5 -> 4
		case 9:	
            dontCheckLeft = true;
            dontCheckRight = false;
            dontCheckStraight = false;
			toggle(&FaceWest::getInstance());
			toggle(&KeepRight::getInstance());
			toggle(&Stop::getInstance());
            break;
		
		//4 -> 5
		case 10:
            dontCheckLeft = false;
            dontCheckRight = true;
            dontCheckStraight = false;
            toggle(&FaceEast::getInstance());
			toggle(&KeepLeft::getInstance());
			toggle(&Stop::getInstance());
            break;

		//6 -> 5
		case 11:
            dontCheckLeft = true;
            dontCheckRight = true;
            dontCheckStraight = false;
            toggle(&FaceNorth::getInstance());
			toggle(&KeepRight::getInstance());
			toggle(&Stop::getInstance());
            break;

		//5 -> 6
		case 12:
            dontCheckLeft = false;
            dontCheckRight = false;
            dontCheckStraight = false;
            toggle(&FaceSouth::getInstance());
			toggle(&KeepLeft::getInstance());
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

void Robot::navigate(int startNode, int endNode) {
    // Use Dijkstra's algorithm to find the shortest path
    Dijkstras dijkstras(7); // Assuming there are 7 nodes in the graph
    dijkstras.addEdge(0, 1, 1);
    dijkstras.addEdge(1, 0, 1);
    dijkstras.addEdge(1, 2, 1);
    dijkstras.addEdge(2, 1, 1);
    dijkstras.addEdge(2, 3, 1);
    dijkstras.addEdge(3, 2, 1);
    dijkstras.addEdge(2, 0, 1);
    dijkstras.addEdge(1, 6, 1);
    dijkstras.addEdge(6, 1, 1);
    dijkstras.addEdge(3, 4, 1);
    dijkstras.addEdge(4, 3, 1);
    dijkstras.addEdge(4, 5, 1);
    dijkstras.addEdge(4, 5, 1);
    dijkstras.addEdge(5, 6, 1);
    dijkstras.addEdge(6, 5, 1);

    // Find the shortest path from the startNode to the endNode
    dijkstras.shortestPath(startNode, endNode);

	// Get the shortest path array
    int* shortestPath = dijkstras.getShortestPathList(startNode, endNode);

    int pathLength = dijkstras.getPathLength(startNode, endNode) + 1;

    for (int i = 0; i < pathLength - 1; ++i) {
        // Check if the current vertex in the shortest path array is valid
        if (shortestPath[i] != -1) {
			Serial.print("Going from node ");
			Serial.print(shortestPath[i]);
			Serial.print(" to ");
			Serial.println(shortestPath[i+1]);
			traverseToNode(shortestPath[i], shortestPath[i+1]);
        }
    }

    // Free memory allocated for the shortest path array
    delete[] shortestPath;
}

float Robot::getSensorM2() {
    return fiveSensors.getM2SensorDist();
}

double Robot::getHeading() {
    acc_x = icm20600.getAccelerationX();
    acc_y = icm20600.getAccelerationY();
    acc_z = icm20600.getAccelerationZ();

    gyro_x = icm20600.getGyroscopeX();
    gyro_y = icm20600.getGyroscopeY();
    gyro_z = icm20600.getGyroscopeZ();

    ak09918.getData(&x, &y, &z);
    x = x - offset_x;
    y = y - offset_y;
    z = z - offset_z;
    
    roll = atan2((float)acc_y, (float)acc_z);
    pitch = atan2(-(float)acc_x, sqrt((float)acc_y * acc_y + (float)acc_z * acc_z));

    double Xheading = x * cos(pitch) + y * sin(roll) * sin(pitch) + z * cos(roll) * sin(pitch);
    double Yheading = y * cos(roll) - z * sin(pitch);


    double heading = 180 + 57.3 * atan2(Yheading, Xheading) + declination_shenzhen;

    return heading;
}

