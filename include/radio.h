#ifndef RF
#define RF
    #include <Arduino.h>
    #include <RF24.h>
    #include <pinout.h>
    #include <SPI.h>
    //#include <printf.h>
    void setupRadio(RF24&  radio);
    bool sendData(RF24 &radio, char* str);
    String receiveData(RF24 *radio);
#endif