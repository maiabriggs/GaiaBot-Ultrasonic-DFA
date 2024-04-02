#pragma once

#include "MovementState.h"
#include "Robot.h"
#include "Movements.h"
#include "FiveSensors.h"


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

class FaceNorth : public MovementState {
    public:
        void enter(Robot* robot);
        static MovementState& getInstance();

    private:
        FaceNorth() {}
        FaceNorth(const FaceNorth& other);
        FaceNorth& operator=(const FaceNorth& other);
};

class FaceSouth : public MovementState {
    public:
        void enter(Robot* robot);
        static MovementState& getInstance();

    private:
        FaceSouth() {}
        FaceSouth(const FaceSouth& other);
        FaceSouth& operator=(const FaceSouth& other);
};

class FaceWest : public MovementState {
    public:
        void enter(Robot* robot);
        static MovementState& getInstance();

    private:
        FaceWest() {}
        FaceWest(const FaceWest& other);
        FaceWest& operator=(const FaceWest& other);
};

class FaceEast : public MovementState {
    public:
        void enter(Robot* robot);
        static MovementState& getInstance();

    private:
        FaceEast() {}
        FaceEast(const FaceEast& other);
        FaceEast& operator=(const FaceEast& other);
};

// class HeadNorth : public MovementState {
//     public:
//         void enter(Robot* robot);
//         static MovementState& getInstance();

//     private:
//         HeadNorth() {}
//         HeadNorth(const HeadNorth& other);
//         HeadNorth& operator=(const HeadNorth& other);
// };

// class HeadSouth : public MovementState {
//     public:
//         void enter(Robot* robot);
//         static MovementState& getInstance();

//     private:
//         HeadSouth() {}
//         HeadSouth(const HeadSouth& other);
//         HeadSouth& operator=(const HeadSouth& other);
// };

// class HeadWest : public MovementState {
//     public:
//         void enter(Robot* robot);
//         static MovementState& getInstance();

//     private:
//         HeadWest() {}
//         HeadWest(const HeadWest& other);
//         HeadWest& operator=(const HeadWest& other);
// };

// class HeadEast : public MovementState {
//     public:
//         void enter(Robot* robot);
//         static MovementState& getInstance();

//     private:
//         HeadEast() {}
//         HeadEast(const HeadEast& other);
//         HeadEast& operator=(const HeadEast& other);
// };


