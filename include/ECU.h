#include <Arduino.h>
//#include <radio.h>
//#include <RF24.h>
#include "gearBox.h"
#include "drive.h"
#ifndef ECU
#define ECU
    

    

    struct Ecu
    {
        Ecu();
        bool automaticGearboxIsSelected;
        int lastDistanceToBarrier;
        bool gearboxIsBlocked;
        void run();
    };
    
extern Ecu main_ecu;
#endif