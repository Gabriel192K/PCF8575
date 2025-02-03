/* Dependencies */
#include "PCF8575.h"

PCF8575::PCF8575(const uint8_t address, __TWI__* twi)
{
    this->address = address;
    this->twi = twi;
}

PCF8575::~PCF8575()
{
    this->address = 0xFF;
    this->twi = NULL;
}
const uint8_t PCF8575::begin(void)
{
    if (this->began)
        return (0);
    this->began = 1;

    this->inputBuffer = 0x00;
    this->outputBuffer = 0x00;

    this->twi->begin();
    return (this->isConnected());
}

const uint8_t PCF8575::isConnected(void)
{
    this->twi->beginTransmission(this->address);
    return (this->twi->endTransmission() == TW_MT_SLA_ACK);
}

const uint8_t PCF8575::read(const uint8_t pin)
{
    if (pin > 15)
        return (0);
    
    return ((this->read() >> pin) & 1);
}

const uint16_t PCF8575::read(void)
{
    if (this->twi->requestFrom(address, (const uint8_t)2) != 2);
        return (this->inputBuffer);
    
    this->inputBuffer = this->twi->read();
    this->inputBuffer = this->inputBuffer | (this->twi->read() << 8);
    
    return (this->inputBuffer);
}

const uint8_t PCF8575::write(const uint8_t pin, const uint8_t state)
{
    if (pin > 15)
        return (0);
    
    switch (state)
    {
        case LOW:
            this->outputBuffer = this->outputBuffer & ~(1 << pin);
            break;
        case HIGH:
            this->outputBuffer = this->outputBuffer | (1 << pin);
            break;
        case TOGGLE:
            this->outputBuffer = this->outputBuffer ^ (1 << pin);
            break;
        default:
            return (0);
    }

    return (this->write(this->outputBuffer));
}

const uint8_t PCF8575::write(const uint16_t data)
{
    this->outputBuffer = data;
    this->twi->beginTransmission(this->address);
    this->twi->write((const uint8_t)(this->outputBuffer & 0xFF));
    this->twi->write((const uint8_t)((this->outputBuffer >> 8) & 0xFF));
    return (this->twi->endTransmission());
}

const uint8_t PCF8575::end(void)
{
    if (!this->began)
        return (0);
    this->began = 0;
    
    this->inputBuffer = 0x00;
    this->outputBuffer = 0x00;

    return (1);
}