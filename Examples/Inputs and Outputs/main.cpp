/*
 * Inputs and Outputs.cpp
 *
 * Created: 2/15/2023 10:17:01 AM
 * Author : Office 5
 */ 

#include "USART\USART.h"
#include "PCF8575\PCF8575.h"

PCF8575 pcf(&TWI, 0x20);

int main(void)
{
    USART.begin(115200);
    if (!(pcf.begin()))
    {
        USART.printP(PSTR("IO Expander not working\n"));
        while (1);
    }
    USART.printP(PSTR("Testing Inputs and Outputs\n"));
    for (uint8_t i = 0; i < 8; i++)
    {
        pcf.pinMode(i, INPUT);
        pcf.pinMode(i + 8, OUTPUT);
    }
    while (1) 
    {
        for (uint8_t i = 0; i < 8; i++)
            pcf.write(i + 8, (pcf.read(i) ? HIGH : LOW));
    }
}

