#include "Arduino.h"
#include "Robot.h"
#include "RoboClaw.h"
#include "MovementState.h"
#include "Movements.h"
#include "FiveSensors.h"
#include "ConcreteMovementStates.h"

Movements movements;
FiveSensors fiveSensors;


Robot::Robot(int f_trigPin, int f_echoPin, int m2_trigPin, int m2_echoPin, int m1_trigPin, int m1_echoPin, int fm1_trigPin, int fm1_echoPin, int fm2_trigPin, int fm2_echoPin)
{
    movements.begin();
	fiveSensors.begin(f_trigPin, f_echoPin, m2_trigPin, m2_echoPin, m1_trigPin, m1_echoPin, fm1_trigPin, fm1_echoPin, fm2_trigPin, fm2_echoPin);

	//Robot is initially still
	currentState = &Stop::getInstance();
   
}

void Robot::begin(MovementState states[]) {
  f_trig = f_trigPin;
  f_echo = f_echoPin;

  m2_trig = m2_trigPin;
  m2_echo = m2_echoPin;

  m1_trig = m1_trigPin;
  m1_echo = m1_echoPin;

  fm2_trig = fm2_trigPin;
  fm2_echo = fm2_echoPin;

  fm1_trig = fm1_trigPin;
  fm1_echo = fm1_echoPin;
  
  //Initialising front sensor
  pinMode(f_trig, OUTPUT);
  pinMode(f_echo, INPUT);
  Serial.begin(9600);
  
  //Initialising left sensor
  pinMode(m2_trig, OUTPUT);
  pinMode(m2_echo, INPUT);
  Serial.begin(9600);
   
  //Initialising right sensor
  pinMode(m1_trig, OUTPUT);
  pinMode(m1_echo, INPUT);
  Serial.begin(9600);

  //Initialising front right sensor
  pinMode(fm1_trig, OUTPUT);
  pinMode(fm1_echo, INPUT);
  Serial.begin(9600);

  //Initialising front left sensor
  pinMode(fm2_trig, OUTPUT);
  pinMode(fm2_echo, INPUT);
  Serial.begin(9600);
}

void Robot::setState(MovementState& newState)
{
	currentState->exit(this);  // do something before we change state
	currentState = &newState;  // actually change states now
	currentState->enter(this); // do something after we change state
	currentState->checkSensor(this)
}

void Robot::toggle(MovementState& nextState)
{
	// Delegate the task of determining the next state to the current state
	currentState->toggle(this, nextState);
}
