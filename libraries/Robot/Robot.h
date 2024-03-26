#ifndef Robot_h
#define Robot_h


/*Class for the movement states*/

#include "Arduino.h";
#include "Movements.h";
#include "MovementState.h";
#include "FiveSensors.h";

class MovementState;

class Robot {
    public:
        Robot();
        Movements movements;
        FiveSensors fiveSensors;
        void toggle();
	    void setState(MovementState& newState);

    private:
	    MovementState* currentState;

}

#endif
