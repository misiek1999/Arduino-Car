#include "pinout.h"
//MPU 6050 lib
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
//MPU 6050 A4 and A5
MPU6050 accelgyro;
//Global variable of mpu
int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t nax, nay, naz;
int16_t ngx, ngy, ngz;
//500
#define rangePerDigit 0.000061f
#define dpsPerDigit  0.007633f

//Servo pin

//Servo connected to pin A1

#include <Servo.h>
//Sterring connected to pin A0
Servo sterring;

//Ultrasonic module hc-sr04
#include "sonic.h"
//Hbridge main motor 


//check rotation of our vehicle
#include "Speedmeter.h"
//Radio communication
#include "radio.h"
#include "radioCommand.h"
Radio radio;
#include "ECU.h"
Ecu ecu;
// uncomment "OUTPUT_READABLE_ACCELGYRO" if you want to see a tab-separated
// list of the accel X/Y/Z and then gyro X/Y/Z values in decimal. Easy to read,
// not so easy to parse, and slow(er) over UART.
#define OUTPUT_READABLE_ACCELGYRO
//#define OUTPUT_READABLE_YAWPITCHROLL
// uncomment "OUTPUT_BINARY_ACCELGYRO" to send all 6 axes of data as 16-bit
// binary, one right after the other. This is very fast (as fast as possible
// without compression or data loss), and easy to parse, but impossible to read
// for a human.
//#define OUTPUT_BINARY_ACCELGYRO

//eint8_t threshold, count; 
    int counter = 0;
void increaseRotation(){
        counter++;
}
char tickWithoutRotation =0;
#define MAX_TiCK_WITHOUT_ROTATION 20
//Dabble
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>


void setup() {
    // join I2C bus (I2Cdev library doesn't do this automatically)
    Wire.begin();

    // initialize serial communication
    // (38400 chosen because it works as well at 8MHz as it does at 16MHz, but
    // it's really up to you depending on your project)
    Serial.begin(115200);

    // initialize device
    Serial.println("Initializing I2C");
    accelgyro.initialize();
    accelgyro.setFullScaleGyroRange(MPU6050_GYRO_FS_500);
    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
    //accelgyro.setIntZeroMotionEnabled(true);
    //accelgyro.setIntFreefallEnabled(true);
    accelgyro.setDHPFMode(1);
    //Motion detection setup
    accelgyro.setMotionDetectionThreshold(1);
    accelgyro.setMotionDetectionDuration(5);

   // accelgyro.setIntMotionEnabled(true);
    //No motion
    accelgyro.setZeroMotionDetectionThreshold(4);
    accelgyro.setZeroMotionDetectionDuration(2);

    accelgyro.getMotion6(&nax, &nay, &naz, &ngx, &ngy, &ngz);

    //Gearbox
    
    //Servo to sterring
    sterring.attach(servoPin);
    //Sonic
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);


    attachInterrupt(digitalPinToInterrupt(interruptPin), increaseRotation, CHANGE );
    Dabble.begin(115200, RX_BLE, TX_BLE);
}
///////////////////////////////////////// L    O    O    P   ////////////////////////////////////////
void loop() {
    counter =0;
    // read raw accel/gyro measurements from device
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    // these methods (and a few others) are also available
    //accelgyro.getAcceleration(&ax, &ay, &az);
    //accelgyro.getRotation(&gx, &gy, &gz);

        // display tab-separated accel/gyro x/y/z values
     //   Serial.print("a/g:\t");
        Serial.print(ax *rangePerDigit * 9.80665f); Serial.print("\t");
        Serial.print(ay*rangePerDigit * 9.80665f); Serial.print("\t");
        Serial.print(az*rangePerDigit * 9.80665f); Serial.println("\t");

        Serial.print(gx *dpsPerDigit); Serial.print("\t");
        Serial.print(gy *dpsPerDigit); Serial.print("\t");
        Serial.println(gz *dpsPerDigit);
    
    Serial.println("Distance:");
    Serial.println(getDistanceInCM());
    /*
    for ( int i =-128;i < 127;  i ++){
         motor.changeMotorSpeed(i);
         delay(100);
    }
    */
   //Totation detect
   /*
    if (counter== 0){
        tickWithoutRotation++;
        if (counter >= 20)
            ecu.gearboxIsBlocked = true;
    }
    else
        tickWithoutRotation = 0;
    
*/
    Dabble.processInput();
  int angle = GamePad.getAngle();
  int radius = GamePad.getRadius();
  float xAxis = GamePad.getx_axis();
  float yAxis = GamePad.gety_axis();

  if (GamePad.isSquarePressed())
  {
    Serial.print("Square");
  }

  if (GamePad.isCirclePressed())
  {
    Serial.print("Circle");
  }

  if (GamePad.isCrossPressed())
  {
    Serial.print("Cross");
  }

  if (GamePad.isTrianglePressed())
  {
    Serial.print("Triangle");
  }

  if (GamePad.isStartPressed())
  {
    Serial.print("Start");
  }

  if (GamePad.isSelectPressed())
  {
    Serial.print("Select");
  }
    delay(30);
}
