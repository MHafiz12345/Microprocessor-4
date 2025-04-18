//----------------------------------------------------------------------//
// Author:  Hafiz, Sofia, Fadzar, Johan, Vincent       
// Net ID:   muhammadhafiz, fadzarar, Vliem, putriyuandari, johaniswara     
// Date:     08 April 2025      
// Assignment: Lab 4 
//----------------------------------------------------------------------//

#ifndef ADC_H
#define ADC_H

#include <avr/io.h>

// Initializes the Analog-to-Digital Converter
// - Sets reference voltage to AVCC (5V)
// - Selects ADC0 (A0 pin) as input channel
// - Disables digital input buffer on ADC0 to reduce power consumption
// - Sets ADC clock prescaler to 128 (125kHz at 16MHz system clock)
// Must be called once before using readADC()
void initADC();

// Reads the current value from the ADC
// - Starts a conversion and waits for it to complete
// - Returns the 10-bit result (0-1023 range)
// Returns: unsigned int containing the 10-bit ADC conversion result
unsigned int readADC();

#endif // ADC_H