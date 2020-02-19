#ifndef RADIO_DATA_STRUCT
    #include <Arduino.h>
    #include <RF24.h>
    #include <SPI.h>
    enum class gear_mode{
        automatic =0,
        g1 = 1,
        g2 = 2
    };
    struct sterringData{
        int8_t pad_power;
        int pad_main_servo;
        gear_mode selected_gear;
        
    };
#endif 