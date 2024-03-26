#include <HCSR04.h>
#include <FiveSensors.h>
#include <Movements.h>
#include <RoboClaw.h>
#include <Dijkstras.h>

//RoboClaw ----- pin S1 -> pin 13, pin S2 -> pin 12
//Pin assignments for Sensors
int fTrig = 7;
int fEcho = 6;

int m2Trig = 9;
int m2Echo = 8;

int m1Trig = 3;
int m1Echo = 2;

int fm2Trig = 11;
int fm2Echo = 10;

int fm1Trig = 5;
int fm1Echo = 4;



FiveSensors fiveSensors(fTrig, fEcho, m2Trig, m2Echo, m1Trig, m1Echo, fm1Trig, fm1Echo, fm2Trig, fm2Echo);
Movements movements; 

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
