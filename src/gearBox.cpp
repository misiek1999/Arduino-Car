#include "gearBox.h"


gearBox::gearBox(){
selectedGear = 0;
    servoG.attach(gearboxServoPin);

}
void gearBox::stepUP(){
    if (selectedGear != 3) 
        ++selectedGear;
    servoG.write(selectedGear*45);

}
void gearBox::stepDown(){
    if (selectedGear != 0) 
        --selectedGear;
    servoG.write(selectedGear*45);
}

void gearBox::changeGear(byte selected){
    switch (selected)
    {
    case 2:
        selectedGear =2;
        servoG.write(45);
        break;
    case 3:
    selectedGear =3;
        servoG.write(90);
        break;
    case 4:
        selectedGear =4;
        servoG.write(135);
        break;

    default:
        selectedGear =1;
        servoG.write(0);
        break;
    }


}
