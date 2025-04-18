#ifndef SWITCH_H
#define SWITCH_H

#include <avr/io.h>

// Initializes PD0 as an input with pull-up resistor and configures external interrupt
// - Sets PD0 as input with internal pull-up resistor enabled
// - Configures INT0 to trigger on any logical change (rising or falling edge)
// - Enables external interrupt INT0
// This function must be called once before using the button for motor control
void initSwitchPD0();

#endif // SWITCH_H
