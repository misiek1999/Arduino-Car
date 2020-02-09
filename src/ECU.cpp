#include "ECU.h"

    
    
 
Ecu::Ecu(){
    gearboxIsBlocked = false;
    automaticGearboxIsSelected = false;
    lastDistanceToBarrier = 0;
}

void Ecu::go(){
    if(automaticGearboxIsSelected &&  gearboxIsBlocked){
       Gbox.stepDown();
    }
    
    if (lastDistanceToBarrier > 2 && lastDistanceToBarrier < 8)
        motor.lockMotor();
    else
    {
        motor.unlockMotor();
    }
    
    

}
Ecu main_ecu;