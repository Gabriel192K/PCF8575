# PCF8575
- PCF8575 library for PCF8575 IO Expander control.

## Key features
- Compatible with `Arduino IDE` & `Microchip Studio IDE`.
- Basic ```read()``` and ```write()``` functions to easily control the `GPIOs`.
- Able to set `LOW`, `HIGH`, `TOGGLE` output state.
- If required to use a `GPIO` as `INPUT` we need to ```write()``` a logic 1 then ```read()```, otherwise use it as an `OPEN DRAIN OUTPUT`.

## Tested on
- `ATmega328P` @16MHz using `Microchip Studio IDE` and `Arduino IDE`.
