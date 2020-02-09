#include "radio.h"
void setupRadio(RF24 &radio_)
{
    // 0 =  transmitter, 1 = robot
    bool radioNumber = 1;

    radio_ = RF24(CEpin, CSpin);

    byte addresses[][6] = {"1Node", "2Node"};
    //printf_begin();
    radio_.begin();
    //radio.setAutoAck(false);
    radio_.setDataRate(RF24_250KBPS);
    // Set the PA Level low to prevent power supply related issues since this is a
    // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
    //radio.setPALevel(RF24_PA_LOW);
    radio_.setPALevel(RF24_PA_MAX);
    // Open a writing and reading pipe on each radio, with opposite addresses
    if (radioNumber)
    {
        radio_.openWritingPipe(addresses[1]);
        radio_.openReadingPipe(1, addresses[0]);
    }
    else
    {
        radio_.openWritingPipe(addresses[0]);
        radio_.openReadingPipe(1, addresses[1]);
    }
    radio_.printDetails();
    //
    // Start the radio listening for data
    radio_.startListening();
    radio_.printDetails();
    Serial.print("OK \n");
}

bool sendData(RF24 &radio_, char str[])
{
    radio_.stopListening(); // First, stop listening so we can talk.
    Serial.println(str);
    Serial.println(strlen(str));
    if (!radio_.write(&str, strlen(str)))
    {
        Serial.println(F("err!"));
        return false;
    }
    else
        Serial.println("Sucf");
    radio_.startListening();
    return true;
}

String receiveData(RF24 *radio_)
{
    char buff[32];
    if (!(*radio_).isChipConnected())
    {
        Serial.println("NC");
        return String('\0');
    }
    Serial.println(sizeof(buff));
    if ((*radio_).available())
    {
        // Variable for the received timestamp
        while ((*radio_).available())
        {                            // While there is data ready
            (*radio_).read(buff, 32); // Get the payload
            Serial.println(buff);
            return String(buff);
        }
    }
    else
    {
        Serial.println("Radio not avalible");
        return  String('\0');
    }
    return  String('\0');
}