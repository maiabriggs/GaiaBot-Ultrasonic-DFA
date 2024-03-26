#include "Arduino.h"
#include "Movements.h"
#include "RoboClaw.h"
#include "SoftwareSerial.h"

uint8_t address;
SoftwareSerial serial(12,13);
RoboClaw roboclaw(&serial, 10000);

Movements::Movements()
{
    address = 0x80;
}


void Movements::begin()
{
    Serial.begin(9600);
    roboclaw.begin(38400);
}

void Movements::forward()
{
    roboclaw.ForwardM1(address, 30); 
    roboclaw.ForwardM2(address, 30);
}

void Movements::backward()
{
    roboclaw.BackwardM1(address, 30);
    roboclaw.BackwardM2(address, 30);
    delay(500);
}

void Movements::left90()
{
    roboclaw.ForwardM1(address, 30);
    delay(3430); // Might need to changes
}

void Movements::right90()
{
    roboclaw.ForwardM2(address, 30);
    delay(3400); // Might need to changes
}

void Movements::left()
{
    roboclaw.ForwardM1(address, 30);
    delay(10); // Might need to changes
}

void Movements::right()
{
    roboclaw.ForwardM2(address, 30);
    delay(10); // Might need to changes
}

void Movements::left180()
{
    roboclaw.ForwardM1(address, 30);
    delay(6800); // Might need to changes
}

void Movements::right180()
{
    roboclaw.ForwardM2(address, 30);
    delay(6800); // Might need to changes
}

void Movements::stop()
{
    roboclaw.ForwardM1(address,0);
    roboclaw.BackwardM2(address,0);
    delay(500);
}

void Movements::veerRight()
{
    roboclaw.ForwardM1(address, 18); 
    roboclaw.ForwardM2(address, 30);
}

void Movements::veerLeft()
{
    roboclaw.ForwardM1(address, 30); 
    roboclaw.ForwardM2(address, 18);
}

void Movements::rotateLeft()
{
    roboclaw.ForwardM1(address, 30); 
    roboclaw.BackwardM2(address, 30);
}

void Movements::rotateRight()
{
    roboclaw.BackwardM1(address, 30); 
    roboclaw.ForwardM2(address, 30);
}