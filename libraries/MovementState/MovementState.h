#pragma once

#ifndef MovementState_h
#define MovementState_h
#include "Arduino.h";

/*Class for the movement states*/

class Robot;


class MovementState {
    public:
        virtual void enter(Robot* robot) = 0;
        virtual void toggle(Robot* robot, MovementState& nextState);
        virtual void exit(Robot* robot);
        virtual ~MovementState() {}   
};

#endif
