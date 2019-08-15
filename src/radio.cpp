#include "radio.h"

Radio::Radio():
radio(9,10),
pipe(0xE8E8F0F0E1LL)
{
    radio.begin();
    radio.openReadingPipe(MESSAGE_LENGHT, pipe);
    radio.startListening();
}


int* Radio::getMessage(){   
    if (radio.available())
    {
    bool done = false;    
        while (!done)
            radio.read(msg, MESSAGE_LENGHT);      
        Serial.println(msg[0]);
    }
    else
    {
        Serial.println("Radio nie dostępne");
    }
    return msg;
}