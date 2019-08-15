#include "sonic.h"
int getDistanceInCM(){
    int time;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    time = pulseIn(echoPin, HIGH);
    return time/constSonicTimeToCM;
}