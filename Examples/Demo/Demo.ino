#include <PCF8575.h>
#include <UART.h>

PCF8575 pcf8575((const uint8_t)0x20, &TWI0);

void setup(void)
{
    UART0.begin(115200);

    if (pcf8575.begin())
        UART0.print(F("Ok\n"));
    else
    {
        UART0.print(F("Not ok\n"));
        while (1);
    }
}

void loop(void)
{

}
