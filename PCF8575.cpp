#include "PCF8575.h"

/*********************************************
Function: PCF8575()
Purpose:  Constructor to PCF8575 class
Input:    Reference to TWI class & address of PCF8575
Return:   None
*********************************************/
PCF8575::PCF8575(__TWI__* twi, const uint8_t address)
{
    this->twi = twi;
    this->address = address;
}

/*********************************************
Function: begin()
Purpose:  Begin communication with device
Input:    TWI address of device
Return:   State of communication with device is successful or not
*********************************************/
uint8_t PCF8575::begin(void)
{
    this->twi->begin();
    return (this->isConnected());
}

/*********************************************
Function: isConnected()
Purpose:  Check communication status with device
Input:    None
Return:   Status of communication
*********************************************/
uint8_t PCF8575::isConnected(void)
{
    uint8_t state = this->twi->beginTransmission(address);
    this->twi->endTransmission();
    return (state);
}

void PCF8575::pinMode(uint8_t pin, uint8_t mode)
{
    if (pin > 15) return;
    this->direction = (mode == INPUT) ? (this->direction | (1 << pin)) : (this->direction & ~(1 << pin));
    PCF8575::write16(this->direction);
}

/*********************************************
Function: read16()
Purpose:  Read 16 bits of data from device
Input:    None
Return:   16 bits of data from device
*********************************************/
uint16_t PCF8575::read16(void)
{
    if (this->twi->requestFrom(address, 2) != 2) return(0);
    this->input = (uint8_t)this->twi->read();
    this->input |= ((uint8_t)this->twi->read() << 8);
    this->twi->endTransmission();
    return (this->input);
}

/*********************************************
Function: writeAll()
Purpose:  Write 16 bits of data to device
Input:    16 bits of data to device
Return:   None
*********************************************/
void PCF8575::write16(uint16_t data)
{
    this->output = data;
    this->twi->beginTransmission(address);
    this->twi->write((uint8_t)(this->output & 0xFF));
    this->twi->write((uint8_t)(this->output >> 8));
    this->twi->endTransmission();
}

/*********************************************
Function: read()
Purpose:  Read specific pin from device
Input:    None
Return:   Specific pin from device
*********************************************/
uint8_t PCF8575::read(uint8_t pin)
{
    if (pin > 15) return (0);
    this->read16();
    return ((this->input >> pin) & 1);
}

/*********************************************
Function: write()
Purpose:  Write specific pin to device
Input:    Data and specific pin to be written
Return:   None
*********************************************/
void PCF8575::write(uint8_t pin, uint8_t state)
{
    if (pin > 15) return;
    this->output = (state == HIGH) ? (this->output | (1 << pin)) : (this->output & ~(1 << pin));
    this->write16(output);
}

/*********************************************
Function: shiftLeft()
Purpose:  Shift bits in output buffer to the left
Input:    Shifting index
Return:   None
*********************************************/
void PCF8575::shiftLeft(uint8_t n)
{
    if ((!n) || (!this->output)) return;
    this->output = (n > 15) ? (0) : (this->output << n);
    this->write16(this->output);
}

/*********************************************
Function: shiftRight()
Purpose:  Shift bits in output buffer to the right
Input:    Shifting index
Return:   None
*********************************************/
void PCF8575::shiftRight(uint8_t n)
{
    if ((!n) || (!this->output)) return;
    this->output = (n > 15) ? (0) : (this->output >> n);
    this->write16(this->output);
}

/*********************************************
Function: rotateLeft()
Purpose:  Rotate bits in output buffer to the left
Input:    Rotating index
Return:   None
*********************************************/
void PCF8575::rotateLeft(uint8_t n)
{
    this->rotateRight(16 - (n & 15));
}

/*********************************************
Function: rotateRight()
Purpose:  Rotate bits in output buffer to the right
Input:    Rotating index
Return:   None
*********************************************/
void PCF8575::rotateRight(uint8_t n)
{
    n &= 15;
    if (!n) return;
    this->output = (this->output >> n) | (this->output << (15 - n));
    this->write16(this->output);
}

/*********************************************
Function: reverse()
Purpose:  Reverse all bits in output buffer
Input:    None
Return:   None
*********************************************/
void PCF8575::reverse(void)
{
    uint16_t x = output;                             //  x = 0123456789ABCDEF
    x = (((x & 0xAAAA) >> 1) | ((x & 0x5555) << 1)); //  x = 1032547698BADCFE
    x = (((x & 0xCCCC) >> 2) | ((x & 0x3333) << 2)); //  x = 32107654BA98FEDC
    x = (((x & 0xF0F0) >> 4) | ((x & 0x0F0F) << 4)); //  x = 76543210FEDCBA98
    x = (x >> 8) | ( x << 8);                        //  x = FEDCBA9876543210
    this->write16(x);
}
