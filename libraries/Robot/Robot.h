#ifndef Robot_h
#define Robot_h


/*Class for the movement states*/

#include "Arduino.h";
#include "Movements.h";
#include "MovementState.h";
#include "ConcreteMovementStates.h";
#include "Dijkstras.h" 
#include "FiveSensors.h"

//IMU Includes
#include "AK09918.h"
#include "ICM20600.h"
#include <Wire.h>

class MovementState;

class Robot {
    public:
        Robot(int f_trigPin, int f_echoPin, int m2_trigPin, int m2_echoPin, int m1_trigPin, int m1_echoPin, int fm1_trigPin, int fm1_echoPin, int fm2_trigPin, int fm2_echoPin);
        Movements movements;
        FiveSensors fiveSensors;
        void toggle(MovementState* newState);
	    void setState(MovementState& newState);
        void initStateListForNode(int scenario);
        void traverseToNode(int currNode, int nextNode);
        void navigate(int startNode, int endNode);
        float getSensorM2();
        bool dontCheckLeft;
        bool dontCheckRight;
        bool dontCheckStraight;
        void moveToStartPosition();

        //IMU
        AK09918_err_type_t err;
        int32_t x, y, z;
        AK09918 ak09918;
        ICM20600 icm20600;
        int16_t acc_x, acc_y, acc_z;
        int16_t gyro_x, gyro_y, gyro_z;
        int32_t offset_x, offset_y, offset_z;
        double roll, pitch;
        // Find the magnetic declination at your location
        // http://www.magnetic-declination.com/
        double declination_shenzhen ;

        void setupIMU();
        void calibrate(uint32_t timeout, int32_t* offsetx, int32_t* offsety, int32_t* offsetz);
        double getHeading();

    private:
	    MovementState* currentState;

};

#endif