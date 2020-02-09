#include "radio.h"

void setupRadio(RF24 &radio)
{
    // 0 =  transmitter, 1 = robot
    bool radioNumber = 1;

    radio = RF24(CEpin, CSpin);

    byte addresses[][6] = {"1Node", "2Node"};
    //printf_begin();
    radio.begin();
    //radio.setAutoAck(false);
    radio.setDataRate(RF24_250KBPS);
    // Set the PA Level low to prevent power supply related issues since this is a
    // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
    //radio.setPALevel(RF24_PA_LOW);
    radio.setPALevel(RF24_PA_MAX);
    // Open a writing and reading pipe on each radio, with opposite addresses
    if (radioNumber)
    {
        radio.openWritingPipe(addresses[1]);
        radio.openReadingPipe(1, addresses[0]);
    }
    else
    {
        radio.openWritingPipe(addresses[0]);
        radio.openReadingPipe(1, addresses[1]);
    }
    radio.printDetails();
    //
    // Start the radio listening for data
    radio.startListening();
    radio.printDetails();
    Serial.print("OK \n");
}

bool sendData(RF24 radio, char str[])
{
    radio.stopListening(); // First, stop listening so we can talk.
    Serial.print(F("Now sending  "));
    Serial.println(str);
    Serial.println(strlen(str));
    if (!radio.write(&str, strlen(str)))
    {
        Serial.println(F("send error!"));
        return false;
    }
    else
        Serial.println("Send succesful");
    radio.startListening();
    return true;
}

String receiveData(RF24 *radio)
{
    char buff[32];
    if (!(*radio).isChipConnected())
    {
        Serial.println("Not connected");
        return "Error";
    }
    Serial.println(sizeof(buff));
    if ((*radio).available())
    {
        // Variable for the received timestamp
        while ((*radio).available())
        {                            // While there is data ready
            (*radio).read(buff, 32); // Get the payload
            Serial.println(buff);
            return String(buff);
        }
    }
    else
    {
        Serial.println("Radio not avalible");
        return "Error";
    }
    return "Error";
}