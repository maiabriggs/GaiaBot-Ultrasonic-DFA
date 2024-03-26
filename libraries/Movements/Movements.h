#ifndef Movements_h
#define Movements_h

#include "Arduino.h"
#include "RoboClaw.h"

class Movements
{
  public:
    Movements();
    void begin();
    void forward();
    void backward();
    void stop();
    void left90();
    void right90();
    void left180();
    void right180();
    void right();
    void left();
    void veerLeft();
    void veerRight();
    void rotateLeft();
    void rotateRight();
};

#endif
