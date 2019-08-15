#include <Arduino.h>
#include <radio.h>
#include <RF24.h>
#include "gearBox.h"
#include "drive.h"
#ifndef ECU
#define ECU
    extern gearBox Gbox;

    extern Drive motor;

    struct Ecu
    {
        Ecu();
        bool automaticGearboxIsSelected;
        int lastDistanceToBarrier;
        bool gearboxIsBlocked;
        void go();
    };
    

#endif