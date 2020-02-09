#ifndef CONN
#define CONN
    #include <Arduino.h>
    #include <pinout.h>
    // File with function to ble communication
    //#include "bleConnection.h" // Not necessery
    // File with class and function to radio communication via nrf24
    #include "radio.h"
    #include "ECU.h"
    #include "main_servo.h"
    #include "drive.h"
    enum class connection_types{
        BLE =1,
        RF24 =2,
        NO_CONNECTED =3
    };
    class Connector{
        connection_types type_of_connection;
        RF24 radio;
        // Buffer for received data
        char buff[32];
        void read_data_and_do_action();
    public:
        Connector();
        bool setup();
        bool run();
        const connection_types get_connection_type()const;
    };


#endif