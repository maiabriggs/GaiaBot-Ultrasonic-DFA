#ifndef Robot_h
#define Robot_h


/*Class for the movement states*/

#include "Arduino.h";
#include "Movements.h";
#include "MovementState.h";
#include "ConcreteMovementStates.h";
#include "Dijkstras.h" 


class MovementState;

class Robot {
    public:
        Robot(int f_trigPin, int f_echoPin, int m2_trigPin, int m2_echoPin, int m1_trigPin, int m1_echoPin, int fm1_trigPin, int fm1_echoPin, int fm2_trigPin, int fm2_echoPin);
        Movements movements;
        void toggle(MovementState* newState);
	    void setState(MovementState& newState);
        void initStateListForNode(int scenario);
        void traverseToNode(int currNode, int nextNode);
        void navigate(int startNode, int endNode);

    private:
	    MovementState* currentState;

};

#endif
