# PCF8575
PCF8585 implementation fro AVR platform

## PCF8585 is a 16 bit IO Expander(multiplexer & demultiplexer) capable of communicating with the MCU via a TWI bus

## Key features
- connection checking (sends a TWI acknowledgement request and returns the status of that request)
- pinMode logic
- port or bit read and write operations (can read or write entire port or specific bit)
- bit manipulation algorithms (left or right shifting, rotating and fast bit reversing)

## Tested on
- ATmega328P
