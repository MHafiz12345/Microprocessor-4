//----------------------------------------------------------------------//
// Author:  Hafiz, Sofia, Fadzar, Johan, Vincent       
// Net ID:   muhammadhafiz, fadzarar, Vliem, putriyuandari, johaniswara       
// Date:     08 April 2025      
// Assignment: Lab 4 
//----------------------------------------------------------------------//

#include "switch.h"
#include <avr/io.h>
#include <avr/interrupt.h>

// Initializes PD0 as an input for external interrupt INT0
void initSwitchPD0(){
    // Set PD0 as input
    DDRD &= ~(1 << DDD0);

    // Enable pull-up resistor on PD0
    PORTD |= (1 << PORTD0);

    // Configure INT0 to trigger on any logical change (rising or falling edge)
    // ISC01 = 0, ISC00 = 1 for any logical change
    EICRA &= ~(1 << ISC01);
    EICRA |= (1 << ISC00);

    // Enable external interrupt INT0
    EIMSK |= (1 << INT0);
}