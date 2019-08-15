#include <Arduino.h>
#include "pinout.h"
#ifndef DRIVE
#define DRIVE

struct Drive{
    Drive();
    void changeMotorSpeed(int speed);
    void lockMotor();
    void unlockMotor();
    bool status;    //TRUE - motor NOT work
};



#endif
