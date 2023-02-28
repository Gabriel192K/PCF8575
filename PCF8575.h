#ifndef __PCF8575_H__

/* ADDRESS TABLE
| INPUTS | PCF8574 |
|   000  |   0x20  |
|   001  |   0x21  |
|   010  |   0x22  |
|   011  |   0x23  |
|   100  |   0x24  |
|   101  |   0x25  |
|   110  |   0x26  |
|   111  |   0x27  |
*/

/* Dependecies */
#include "TWI\TWI.h"

class PCF8575
{
    public:
        PCF8575(__TWI__* twi, const uint8_t address);
        uint8_t  begin      (void);
        uint8_t  isConnected(void);
        void     pinMode    (uint8_t pin, uint8_t mode);
        uint8_t  read       (uint8_t pin);
        uint16_t read16     (void);
        void     write      (uint8_t pin, uint8_t state);
        void     write16    (uint16_t state);
        void     shiftLeft  (uint8_t n);
        void     shiftRight (uint8_t n);
        void     rotateLeft (uint8_t n);
        void     rotateRight(uint8_t n);
        void     reverse    (void);
    private:
        __TWI__* twi;
        uint8_t address;
        uint16_t direction, input, output;

};

#endif