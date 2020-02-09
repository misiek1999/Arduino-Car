    // #include "mpu.h"
    // //MPU 6050 A4 and A5
    // MPU6050 mpu;
    // // MPU control/status vars
    
    // uint8_t mpuIntStatus;  a // holds actual interrupt status byte from MPU
    // uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
    // uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
    // uint16_t fifoCount;     // count of all bytes currently in FIFO
    // uint8_t fifoBuffer[64]; // FIFO storage buffer

    // // orientation/motion vars
    // Quaternion q;        // [w, x, y, z]         quaternion container
    // VectorInt16 aa;      // [x, y, z]            accel sensor measurements
    // VectorInt16 aaReal;  // [x, y, z]            gravity-free accel sensor measurements
    // VectorInt16 aaWorld; // [x, y, z]            world-frame accel sensor measurements

    // float euler[3]; // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

    // // packet structure for InvenSense teapot demo
    // uint8_t teapotPacket[14];
    // void dmpDataReady()
    // {
    //     mpuInterrupt = true;
    // }