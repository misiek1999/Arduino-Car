#include <Arduino.h>
#include <RF24.h>
#include <pinout.h>
#include <SPI.h>
#ifndef RF
#define RF
#define MESSAGE_LENGHT 2
    class Radio
    {   
        RF24 radio;
        int msg[MESSAGE_LENGHT];
        const uint64_t pipe ;
        Radio();

        //void init();
        int* getMessage();

    };

#endif