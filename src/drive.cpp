#include "drive.h"
Drive::Drive(){
    pinMode(motorFirstRotationRight, OUTPUT);
    pinMode(motorFirstRotationLeft, OUTPUT);
    pinMode(motorFirstPWM, OUTPUT);
    status = false;
}

void Drive::changeMotorSpeed(int speed){
    if (speed > 0 && !status){
        digitalWrite(motorFirstRotationRight, HIGH);
        digitalWrite(motorFirstRotationLeft, LOW);
        analogWrite(motorFirstPWM, 128 + speed);
    } else if (speed < 0){
        digitalWrite(motorFirstRotationLeft, HIGH);
        digitalWrite(motorFirstRotationRight, LOW);
        analogWrite(motorFirstPWM, 127 - speed); 
    }
}

void Drive::lockMotor(){

    if (!status){
        changeMotorSpeed(0);
        status =true;
    }       
}


void Drive::unlockMotor(){
    if (status)
        status =false;

}
