#include <Arduino.h>
#include <printf.h>
#include "pinout.h"
//Include mpu6050 settings and variables
#include "Wire.h"
//MPU 6050 lib
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
// MPU control/status vars
//      #define MPU_DEBUG_SERIAL
MPU6050 mpu;
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container

// packet structure for InvenSense teapot demo
uint8_t teapotPacket[14] = { '$', 0x02, 0,0, 0,0, 0,0, 0,0, 0x00, 0x00, '\r', '\n' };

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
    mpuInterrupt = true;
}
// Include main servo
#include "main_servo.h"
//Ultrasonic module hc-sr04
#include "sonic.h"
Sonic sonic_radar1;
//Hbridge main motor
#include "drive.h"
//check rotation speed of main motor
//#include "Speedmeter.h"
// Include ecu -
#include "ECU.h"
Ecu ecu;
#include "connection.h"
Connector connection;
unsigned long reset_time;
#include <TinyGPS++.h>
TinyGPSPlus gps;
int counter = 0;
void increaseRotation()
{
    counter++;
}

uint8 tickWithoutRotation = 0;
#define MAX_TiCK_WITHOUT_ROTATION 20

// Send euler position
// #define TIME_BETWEEN_EULER_SEND 500000 //micro
// time_t saved_time;
// bool send_euler_position(float euler[3]){
//     if (micros() - saved_time >= TIME_BETWEEN_EULER_SEND){
//         saved_time  =micros();
//         Serial1.print("A");
//         Serial1.print()
//         return true;
//     }
//     return false;
// }
void setup()
{
    // Debug serial initialization
    Serial.begin(115200);
    if(!connection.setup())
        return;
    // Mpu initialization
    Serial.println(F("Start init mpu"));
    Wire.begin();
    Wire.setClock(400000);
    mpu.initialize();
    pinMode(INTERRUPT_PIN, INPUT);
    // verify connection
    Serial.println(F("Testing connections"));
    Serial.println(mpu.testConnection() ? F("MPU6050 S") : F("MPU6050 F"));

    // load and configure the DMP
    Serial.println(F("Initializing DMP..."));
    devStatus = mpu.dmpInitialize();

    // supply your own gyro offsets here, scaled for min sensitivity
    mpu.setXGyroOffset(220);
    mpu.setYGyroOffset(76);
    mpu.setZGyroOffset(-85);
    mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

    // make sure it worked (returns 0 if so)
    if (devStatus == 0) {
        // Calibration Time: generate offsets and calibrate our MPU6050
        mpu.PrintActiveOffsets();
        // turn on the DMP, now that it's ready
        Serial.println(F("Enabling DMP..."));
        mpu.setDMPEnabled(true);

        // enable Arduino interrupt detection
    Serial.print(digitalPinToInterrupt(INTERRUPT_PIN));
        attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();
        dmpReady = true;

        // get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();
    } else {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        // (if it's going to break, usually the code will be 1)
        Serial.print(F("DMP-fail"));
        Serial.print(devStatus);
    }

    // Sonic sensor initialization
    sonic_radar1.attachSonic();
    // Main servo initialization
    main_servo.attach(mainServoPin);
    //speedmeter pin and funtion initialization
    printf_begin();
    //Setup first time setup reset_time
    reset_time = 0;
}
void loop()
{

    sonic_radar1.sendImpulse();

    // wait for MPU interrupt or extra packet(s) available
    while (!mpuInterrupt && fifoCount < packetSize) {
        if (mpuInterrupt && fifoCount < packetSize) {
          // try to get out of the infinite loop 
          fifoCount = mpu.getFIFOCount();
        }  
        // other program behavior stuff here
        // .
        // .
        // .
        // if you are really paranoid you can frequently test in between other
        // stuff to see bif mpuInterrupt is true, and if so, "break;" from the
        // while() loop to immediately process the MPU data
        // .
        // .
        // .
    }

    // reset interrupt flag and get INT_STATUS byte
    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();

    // get current FIFO count
    fifoCount = mpu.getFIFOCount();
	if(fifoCount < packetSize){
	        //Lets go back and wait for another interrupt. We shouldn't be here, we got an interrupt from another event
			// This is blocking so don't do it   while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();
	}
    // check for overflow (this should never happen unless our code is too inefficient)
    else if ((mpuIntStatus & _BV(MPU6050_INTERRUPT_FIFO_OFLOW_BIT)) || fifoCount >= 1024) {
        // reset so we can continue cleanly
        mpu.resetFIFO();
      //  fifoCount = mpu.getFIFOCount();  // will be zero after reset no need to ask
        Serial.println(F("FIFO!"));

    // otherwise, check for DMP data ready interrupt (this should happen frequently)
    } else if (mpuIntStatus & _BV(MPU6050_INTERRUPT_DMP_INT_BIT)) {

        // read a packet from FIFO
	while(fifoCount >= packetSize){ // Lets catch up to NOW, someone is using the dreaded delay()!
		mpu.getFIFOBytes(fifoBuffer, packetSize);
		// track FIFO count here in case there is > 1 packet available
		// (this lets us immediately read more without waiting for an interrupt)
		fifoCount -= packetSize;
	}
        // display Euler angles in degrees
        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetEuler(euler, &q);
        #ifdef MPU_DEBUG_SERIAL
            Serial.print("euler\t");
            Serial.print(euler[0] * 180/M_PI);
            Serial.print("\t");
            Serial.print(euler[1] * 180/M_PI);
            Serial.print("\t");
            Serial.println(euler[2] * 180/M_PI);
        #endif
    }

    // Receive data and do action
    //receiveDataAndDoAction();
    connection.run();
    // Tactital delay 
    delay(10);
    // Read sonic sensor distance and potential lock motor 
    ecu.lastDistanceToBarrier = sonic_radar1.getDistanceInCM();
    ecu.run();
    //Serial.println("itr");
    if(connection.get_connection_type() ==connection_types::RF24 && millis() - reset_time > 1000 && (!connection.is_chip_connected() ||  millis() - connection.last_received_data_time() > 1000))
    {
        connection.reset();
        Serial.println("Hard reset");
        reset_time = millis();
    }

}   