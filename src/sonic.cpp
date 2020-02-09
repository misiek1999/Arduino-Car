#include "sonic.h"
Sonic * Sonic::instance_(NULL);
int Sonic::getDistanceInCM(){
    if (this->finished)
        return (end_time - start_time)/constSonicTimeToCM;
    return SONIC_ERROR_CODE;
}

Sonic::Sonic(){
    if (instance_ == NULL)
        instance_ = this;
}
void Sonic::attachSonic(){
    pinMode(trigPin, OUTPUT);
    digitalWrite(trigPin, LOW);
    pinMode(echoPin, INPUT);
    digitalWrite(echoPin, LOW);
    attachInterrupt(echoPin, intteruptEchoPin, CHANGE);
}

void Sonic::sendImpulse(){
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
}

void Sonic::intteruptEchoPin(){
    Sonic* this_ = Sonic::instance();
    if (digitalRead(echoPin) == HIGH){
        this_->finished = false;
        this_->start_time = micros();
    }else{
        this_->end_time = micros();
        this_->finished = true;
    }

}
