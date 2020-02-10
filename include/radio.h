#ifndef RF
#define RF
    #include <Arduino.h>
    #include <RF24.h>
    #include <SPI.h>
    #include "radioDataStruct.h"
    #include "pinout.h"
    //#include <printf.h>
    void setupRadio(RF24&  radio);
    bool sendData(RF24 &radio, char* str);
    void sendDataStructure(RF24& radio, sterringData &structure_to_send);
    String receiveData(RF24 *radio);
    void receiveDataStructure(RF24& radio, sterringData &structure_to_modify);
#endif