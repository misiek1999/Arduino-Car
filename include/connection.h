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
        sterringData received_sterring_data;
        void read_data_and_do_action_BLE();
        void read_data_and_do_action_RF24();
        unsigned long last_time;
        void save_last_connection_time();
    public:
        Connector();
        bool setup();
        bool run();
        const connection_types get_connection_type()const;
        bool is_chip_connected();
        void reset();
        unsigned long last_received_data_time();
    };


#endif