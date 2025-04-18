//----------------------------------------------------------------------//
// Author:  Hafiz, Sofia, Fadzar, Johan, Vincent       
// Net ID:   muhammadhafiz, fadzarar, Vliem, putriyuandari, johaniswara       
// Date:     08 April 2025      
// Assignment: Lab 4 
//----------------------------------------------------------------------//

#include "adc.h"
#include <avr/io.h>

// Initialize the ADC to read from A0 pin
void initADC() {
    // Set the reference voltage to AVCC (5V)
    ADMUX = (1 << REFS0);
    ADMUX &= ~(1 << REFS1);
    
    // Select ADC0 channel (default, so we can just clear MUX bits)
    ADCSRB &= ~(1 << MUX5);
    ADMUX &= ~((1 << MUX0) | (1 << MUX1) | (1 << MUX2) | (1 << MUX3) | (1 << MUX4));
   
    // Disable digital input buffer on ADC0 to reduce power consumption
    DIDR0 |= (1 << ADC0D);
    
    // Enable ADC and set prescaler to 128 for 16MHz clock
    // 16MHz/128 = 125kHz (ADC clock should be 50-200kHz)
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

// Read a value from the ADC
unsigned int readADC() {
    // Start conversion
    ADCSRA |= (1 << ADSC);
    
    // Wait for conversion to complete
    while (ADCSRA & (1 << ADSC));
    
    // Return the 10-bit ADC result (combines ADCL and ADCH automatically)
    return ADC;
}