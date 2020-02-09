#include "connection.h"

Connector::Connector() : radio(CEpin, CSpin)
{
    type_of_connection = connection_types::NO_CONNECTED;
}

bool Connector::setup()
{
    // Ble serial initialization
    Serial1.begin(9600);
    //Setup nrf24 module
    setupRadio(radio);
    if (radio.isChipConnected())
    {
        type_of_connection = connection_types::RF24;
        return true;
    }
    //TODO: solve this problem
    if (Serial1) // Its always true i know -_-
    {
        type_of_connection = connection_types::BLE;
        return true;
    }
    type_of_connection = connection_types::NO_CONNECTED;
    return false;
}

//TODO: add receive data from radio
bool Connector::run()
{

    uint8 ind_buff = 0;
    buff[0] = '\0';
    if (type_of_connection == connection_types::BLE)
    {
        if (Serial1.available())
        {
            ind_buff = Serial1.readBytesUntil('*', buff, sizeof(buff));
            buff[ind_buff] = '\0';
            Serial.println(buff);
        }
        else
        {
            buff[0] = '\0';
        }
    }
    else if (type_of_connection == connection_types::RF24)
    {
        String data = receiveData(&radio);
        strcpy(buff, data.c_str());
    }
    else
        return false;
    // No receive any data from master
    if (buff[0] == '\0')
        return true;
    else
        read_data_and_do_action();
    return true;
}

const connection_types Connector::get_connection_type() const
{
    return type_of_connection;
}
#define MAX_INT_LEN 8
void Connector::read_data_and_do_action()
{
    switch (buff[0])
    {
        // FIRST PAD
    case 'P':
        if (buff[1] == 'X')
        {
            uint8_t buff_itr = 2;
            int16_t pad_x = 0;
            bool negative_number = false;
            while (buff[buff_itr] != 'Y')
            {
                if (buff[buff_itr] == '-')
                    negative_number = true;
                else
                {
                    pad_x = pad_x * 10;
                    pad_x += uint8_t(buff[buff_itr]) - 48;
                }
                buff_itr += 1;
            }
            if (negative_number)
                pad_x *= -1;
            int16_t pad_y = 0;
            buff_itr += 1;
            negative_number = false;
            while (buff[buff_itr] != '\0')
            {
                if (buff[buff_itr] == '-')
                    negative_number = true;
                else
                {
                    pad_y = pad_y * 10;
                    pad_y += uint8_t(buff[buff_itr]) - 48;
                }
                buff_itr += 1;
            }
            if (negative_number)
                pad_y *= -1;
        

        Serial.println(pad_x);
        Serial.println(pad_y);
        // Change speed of main motor
        motor.changeMotorSpeed(pad_y);
    }
    break;
// Secornd PAD
case 'R':
        if (buff[1] == 'X')
        {
            uint8_t buff_itr = 2;
            int16_t pad_x = 0;
            bool negative_number = false;
            while (buff[buff_itr] != 'Y')
            {
                if (buff[buff_itr] == '-')
                    negative_number = true;
                else
                {
                    pad_x = pad_x * 10;
                    pad_x += uint8_t(buff[buff_itr]) - 48;
                }
                buff_itr += 1;
            }
            if (negative_number)
                pad_x *= -1;
            int16_t pad_y = 0;
            buff_itr += 1;
            negative_number = false;
            while (buff[buff_itr] != '\0')
            {
                if (buff[buff_itr] == '-')
                    negative_number = true;
                else
                {
                    pad_y = pad_y * 10;
                    pad_y += uint8_t(buff[buff_itr]) - 48;
                }
                buff_itr += 1;
            }
            if (negative_number)
                pad_y *= -1;

        Serial.println(pad_x);
        Serial.println(pad_y);
        // Change speed of main motor
         main_servo.write(pad_x);
    }

    break;
case 'A':
    //Zmienia system na automatyczna zmianie biegów
    Serial.println("A-G");

    break;
case 'B':
    //Manualne biegi, wybiera aktualny bieg

    break;
case '1':
    //1
    Gbox.changeGear(1);
    break;
case '2':
    //2
    Gbox.changeGear(2);
    break;
case '3':
    //3
    Gbox.changeGear(3);
    break;
case '4':
    //4
    Gbox.changeGear(4);
    break;
case 'C':
    //Connected information
    break;
default:
    Serial.println("E - Data not definied");
    break;
}
}
