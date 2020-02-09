
#include "bleConnection.h"

char BluetoothData;
int pad_x;
int pad_y;


void receiveDataAndDoAction()
{
    if (Serial.available())
        Serial1.write(Serial.read());
    if (Serial1.available())
    {
        BluetoothData = Serial1.read();
        Serial.println(BluetoothData);
        switch (BluetoothData)
        {
            // FIRST PAD 
        case 'P':
            while (BluetoothData != 'X')
            {
                BluetoothData = Serial1.read();
            }

            pad_x = Serial1.parseInt();
            while (BluetoothData != '*')
            {
                if (Serial1.available())
                {
                    BluetoothData = Serial1.read(); //Get next character from bluetooth
                    if (BluetoothData == 'Y')
                        pad_y = -Serial1.parseInt();
                }
            }
            Serial.println(pad_x);
            Serial.println(pad_y);
            // Change speed of main motor
            motor.changeMotorSpeed(pad_y);
            break;
        // Secornd PAD
        case 'R':
            while (BluetoothData != 'X')
            {
                BluetoothData = Serial1.read();
            }

            pad_x = Serial1.parseInt();
            while (BluetoothData != '*')
            {
                if (Serial1.available())
                {
                    BluetoothData = Serial1.read(); //Get next character from bluetooth
                    if (BluetoothData == 'Y')
                        pad_y = -Serial1.parseInt();
                }
            }
            Serial.println(pad_x);
            Serial.println(pad_y);
            main_servo.write(pad_x);
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
            //4
            motor.changeMotorSpeed(0);
            break;
        default:
            Serial.println("E - Data not definied");
            break;
        }
    }

    // TODO you loop code
    // use the RemoteXY structure for data transfer
}