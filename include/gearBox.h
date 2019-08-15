 #include <Arduino.h>
 #include <Servo.h>
 #include "pinout.h"
 #ifndef GBOX
 #define GBOX
 

struct gearBox{
    //Constructor
    Servo servoG;

    gearBox();
    void stepUP();
    void stepDown();
    uint8_t selectedGear;
    void changeGear(byte selected);

};



#endif
