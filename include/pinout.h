//All board pinout connection
#ifndef PINOUT
    #define PINOUT
    //Servo
    #include <Servo.h>
    #define SERVO_CLASS Servo   
    #define mainServoPin PB8
    //Gearbox
    #define gearboxServoPin PB9
    //UltraSonic module
    #define trigPin PB4 
    #define echoPin PB5
    // A4 and A5 connected to I2C   MPU6050
    #define SCL1 PB6
    #define SDA1 PB7
    //RF 24
    #define MOSI1 PA7
    #define MISO1 PA6
    #define SCK1 PA5
    #define CEpin PB1
    #define CSpin PB0
    //BLE Android BLE app
    #define TX_BLE PA9  //Default Serial1 pins P
    #define RX_BLE PA10 // --||--

    //Hbridge Pin
    #define motorFirstRotationRight  PA15
    #define motorFirstRotationLeft  PB3
    #define motorFirstPWM  PA0

    //Second hbridge
    #define motorSecondRotationRight PB12
    #define motorSecondRotationLeft PB13
    #define motorSecondPWM  PA1
    //GPS module over serial communication 
    #define GPStransmitter PA2
    #define GPSreceiver PA3
    //Mpu Interupt pin
    #define INTERRUPT_PIN PA8 //mpu...
    #define SpeedmeterInterupt PB15  //Speedmeter
    //I2C for LCD display
    #define SecondI2C_SDA PB11
    #define SecondI2C_SCL PB10
    #define BatterVoltageTest PA4
#endif