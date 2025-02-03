/* Dependencies */
#include <TWI.h>

/* Macros */
#ifndef LOW
#define LOW          (const uint8_t)0
#endif
#ifndef HIGH
#define HIGH         (const uint8_t)1
#endif
#ifndef TOGGLE
#define TOGGLE       (const uint8_t)2
#endif

class PCF8575
{
    public:
        PCF8575(const uint8_t address, __TWI__* twi);
        ~PCF8575();
        const uint8_t  begin      (void);
        const uint8_t  isConnected(void);
        const uint8_t  read       (const uint8_t pin);
        const uint16_t read       (void);
        const uint8_t  write      (const uint8_t pin, const uint8_t state);
        const uint8_t  write      (const uint16_t data);
        const uint8_t  end        (void);
    private:
        uint8_t address;
        __TWI__* twi;
        uint8_t began;
        uint16_t inputBuffer, outputBuffer;
};
