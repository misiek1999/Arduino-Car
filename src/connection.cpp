#include "connection.h"

Connector::Connector() : radio(CEpin, CSpin)
{
    type_of_connection = connection_types::NO_CONNECTED;
}

bool Connector::setup()
{
    received_sterring_data.pad_main_servo =90;
    received_sterring_data.pad_power = 0;
    received_sterring_data.selected_gear = gear_mode::g1;
    // Ble serial initialization
    Serial1.begin(9600);
    //Setup nrf24 module
    setupRadio(radio);
    if (radio.isChipConnected())
    {
        type_of_connection = connection_types::RF24;
        return true;
    }
    type_of_connection = connection_types::RF24;
        return true;
        
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
        //Serial.println("BLE");
        if (Serial1.available())
        {
            ind_buff = Serial1.readBytesUntil('*', buff, sizeof(buff));
            buff[ind_buff] = '\0';
            Serial.println(buff);
        }
        else
        {
            return false;
        }
        if (buff[0] == '\0')
            return true;
        else
            read_data_and_do_action_BLE();
        return true;

    }
    else if (type_of_connection == connection_types::RF24)
    {
        if(radio.available())
        {
            receiveDataStructure(radio, received_sterring_data);
            save_last_connection_time();
            //Serial.println("data received");
            read_data_and_do_action_RF24();
        }
    }

    // No receive any data from master
    return false;
}

const connection_types Connector::get_connection_type() const
{
    return type_of_connection;
}
#define MAX_BUFF_ITR 10
void Connector::read_data_and_do_action_BLE()
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
                if (buff_itr > MAX_BUFF_ITR)
                    continue;
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
                if (buff_itr > MAX_BUFF_ITR)
                    continue;
            }
            if (negative_number)
                pad_y *= -1;
            if (buff_itr > MAX_BUFF_ITR)
                return;

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
                if (buff_itr > MAX_BUFF_ITR)
                    continue;
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
                if (buff_itr > MAX_BUFF_ITR)
                    continue;
            }
            if (negative_number)
                pad_y *= -1;
            if (buff_itr > MAX_BUFF_ITR)
                return;
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


void Connector::read_data_and_do_action_RF24()
{
    motor.changeMotorSpeed(received_sterring_data.pad_power);
    main_servo.write(received_sterring_data.pad_main_servo);
    if(received_sterring_data.selected_gear != gear_mode::automatic)
        Gbox.changeGear(uint8(received_sterring_data.selected_gear));
    else
    {

    }
    

}

bool Connector::is_chip_connected(){
    return radio.isChipConnected();
}

void Connector::reset(){
    if(type_of_connection == connection_types::RF24)
        setupRadio(radio);
}

void Connector::save_last_connection_time(){
    last_time = millis();
}


unsigned long Connector::last_received_data_time(){
    return last_time;
}