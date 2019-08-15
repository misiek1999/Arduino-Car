//All board pinout connection
#ifndef PINOUT
    #define PINOUT
    //Servo
    #define servoPin A0
    //Gearbox
    #define gearboxServoPin A1
    //UltraSonic module
    #define trigPin A2
    #define echoPin A3
    // A4 and A5 connected to I2C
        
    //RF 24
    #define mosi 11
    #define miso 12
    #define ss 13
    #define p1 9
    #define p2 10

    //Hbridge Pin
    #define motorFirstRotationRight  A6
    #define motorFirstRotationLeft  A7
    #define motorFirstPWM  5

    //Second hbridge
    #define motorSecondRotationRight 8
    #define motorSecondRotationLeft  7
    #define motorSecondPWM  6
    //GPS
    #define GPStransmitter 1
    #define GPSreceiver 2

    #define interruptPin 3
#endif