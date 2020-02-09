 #ifndef MPU_
 #define MPU_ 
    #include "Arduino.h"
     #include "Wire.h"
    //MPU 6050 lib
    #include "I2Cdev.h"
    //#include "MPU6050.h"
    #include "MPU6050_6Axis_MotionApps20.h"

    //MPU 6050 A4 and A5
    extern MPU6050 mpu;
    // MPU control/status vars
    extern bool dmpReady;  // set true if DMP init was successful
    extern uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
    extern uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
    extern uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
    extern uint16_t fifoCount;     // count of all bytes currently in FIFO
    extern uint8_t fifoBuffer[64]; // FIFO storage buffer

    // orientation/motion vars
    extern Quaternion q;        // [w, x, y, z]         quaternion container
    extern VectorInt16 aa;      // [x, y, z]            accel sensor measurements
    extern VectorInt16 aaReal;  // [x, y, z]            gravity-free accel sensor measurements
    extern VectorInt16 aaWorld; // [x, y, z]            world-frame accel sensor measurements

    extern float euler[3]; // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

    // packet structure for InvenSense teapot demo
    extern uint8_t teapotPacket[14];
    extern bool mpuInterrupt; // indicates whether MPU interrupt pin has gone high
    void dmpDataReady();

#endif