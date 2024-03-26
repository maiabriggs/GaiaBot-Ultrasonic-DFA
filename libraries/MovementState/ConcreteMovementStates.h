#pragma once

#include "MovementState.h"
#include "Robot.h"
#include "Movements.h"

class Stop : public MovementState {
    public: 
        void enter(Robot* robot);
        static MovementState& getInstance();

    private:
        Stop() {}
        Stop(const Stop& other);
        Stop& operator=(const Stop& other);
};

class TurnLeft : public MovementState {
    public:
        void enter(Robot* robot);
        static MovementState& getInstance();

    private:
        TurnLeft() {}
        TurnLeft(const TurnLeft& other);
        TurnLeft& operator=(const TurnLeft& other);
};

class TurnRight : public MovementState {
    public:
        void enter(Robot* robot);
        static MovementState& getInstance();

    private:
        TurnRight() {}
        TurnRight(const TurnRight& other);
        TurnRight& operator=(const TurnRight& other);
};

class KeepLeft : public MovementState {
    public:
        void enter(Robot* robot);
        static MovementState& getInstance();

    private:
        KeepLeft() {}
        KeepLeft(const KeepLeft& other);
        KeepLeft& operator=(const KeepLeft& other);
};

class KeepRight : public MovementState {
    public:
        void enter(Robot* robot);
        static MovementState& getInstance();

    private:
        KeepRight() {}
        KeepRight(const KeepRight& other);
        KeepRight& operator=(const KeepRight& other);
};
