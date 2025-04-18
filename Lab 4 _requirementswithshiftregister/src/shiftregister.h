#ifndef SHIFTREGISTER_H
#define SHIFTREGISTER_H

#include <avr/io.h>

// Initialize shift register pins
// - Sets up data, clock, and latch pins as outputs
// - Initializes all pins to low state
void initShiftRegister(void);

// Send a byte to the shift register 
// - Shifts out 8 bits serially, MSB first
// - Controls data, clock, and latch pins to transfer data
// - data: 8-bit value to send to the shift register
void shiftOut(uint8_t data);

// Display a digit (0-9) on the seven segment display using shift register
// - Converts digit to appropriate segment pattern for common cathode display
// - Uses shiftOut to send pattern to shift register
// - digit: Value between 0-9 to display
void displayDigitShift(uint8_t digit);

// Clear the display
// - Turns off all segments by sending 0x00 to the shift register
void clearDisplayShift(void);

#endif // SHIFTREGISTER_H
