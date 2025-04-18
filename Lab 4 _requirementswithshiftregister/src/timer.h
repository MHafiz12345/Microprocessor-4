//----------------------------------------------------------------------//
// Author:  Hafiz, Sofia, Fadzar, Johan, Vincent       
// Net ID:   muhammadhafiz, fadzarar, Vliem, putriyuandari, johaniswara       
// Date:     08 April 2025      
// Assignment: Lab 4
//----------------------------------------------------------------------//

#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>

// Initializes Timer0 for millisecond precision timing
// - Configures Timer0 in CTC mode with OCR0A = 249
// - Used for debouncing the switch
// - Timer is initially stopped
void initTimer0();

// Initializes Timer1 for second precision timing
// - Configures Timer1 in CTC mode with OCR1A = 15624
// - Used for countdown from 9 to 0 seconds
// - Timer is initially stopped
void initTimer1();

// Creates a precise millisecond delay using Timer0
// - Starts Timer0 with prescaler 64
// - Waits for the specified number of milliseconds
// - Stops Timer0 when done
// Parameters:
//   delay - number of milliseconds to wait
void delayMs(unsigned int delay);

// Starts a countdown from 9 to 0 seconds
// - Sets countdown_value to 9
// - Activates countdown_active flag
// - Starts Timer1 with prescaler 1024
void startCountdown();

// Checks if the countdown is currently active
// Returns:
//   1 if countdown is active, 0 if not
uint8_t isCountdownActive();

// Gets the current countdown value
// Returns:
//   Current countdown value (9 to 0)
uint8_t getCountdownValue();

#endif // TIMER_H