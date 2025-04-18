//----------------------------------------------------------------------//
// Author:  Hafiz, Sofia, Fadzar, Johan, Vincent       
// Net ID:   muhammadhafiz, fadzarar, Vliem, putriyuandari, johaniswara    
// Date:     08 April 2025      
// Assignment: Lab 4
//----------------------------------------------------------------------//

#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>

// Global variables for timers
volatile unsigned int ms_counter = 0;     // For debouncing (milliseconds)
volatile uint8_t countdown_value = 0;     // Current countdown value (9-0)
volatile uint8_t countdown_active = 0;    // Flag to indicate countdown status

/*
 * Initializes Timer0 for debouncing (millisecond precision)
 */
void initTimer0() {
    // Configure Timer0 in CTC mode (WGM02:0 = 010)
    TCCR0A &= ~(1 << WGM00);  // Clear bit WGM00
    TCCR0A |= (1 << WGM01);   // Set bit WGM01
    TCCR0B &= ~(1 << WGM02);  // Clear bit WGM02
    
    // Set compare value for 1ms intervals (16MHz/64/1000Hz)
    OCR0A = 249;
    
    // Enable interrupt on compare match
    TIMSK0 |= (1 << OCIE0A);
    TIMSK0 &= ~((1 << OCIE0B) | (1 << TOIE0)); // Disable other interrupts
    
    // Timer initially stopped (clear all clock select bits)
    TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00));
}

/*
 * Initializes Timer1 for the countdown
 */
void initTimer1() {
    // Configure Timer1 in CTC mode (WGM13:0 = 0100)
    TCCR1A &= ~((1 << WGM11) | (1 << WGM10));  // Clear WGM11 and WGM10
    TCCR1B |= (1 << WGM12);    // Set WGM12
    TCCR1B &= ~(1 << WGM13);   // Clear WGM13
    
    // Set compare value for 1 second intervals (16MHz/1024/1Hz)
    OCR1A = 15624;
    
    // Enable interrupt on compare match A
    TIMSK1 |= (1 << OCIE1A);
    TIMSK1 &= ~((1 << OCIE1B) | (1 << TOIE1) | (1 << ICIE1)); // Disable other interrupts
    
    // Timer initially stopped (clear all clock select bits)
    TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
}

/*
 * Creates a delay for debouncing
 */
void delayMs(unsigned int delay) {
    ms_counter = 0;
    TCNT0 = 0;  // Clear the timer counter
    
    // Start Timer0 with prescaler 64 (CS02:0 = 011)
    TCCR0B &= ~(1 << CS02);   // Clear CS02
    TCCR0B |= (1 << CS01) | (1 << CS00);  // Set CS01 and CS00
    
    // Wait until desired delay is reached
    while (ms_counter < delay);
    
    // Stop Timer0 (clear all clock select bits)
    TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00));
}

/*
 * Start countdown from 9 to 0
 */
void startCountdown() {
    // Set initial countdown value
    countdown_value = 9;
    countdown_active = 1;
    
    // Reset Timer1
    TCNT1 = 0;
    
    // Start Timer1 with prescaler 1024 (CS12:0 = 101)
    TCCR1B &= ~(1 << CS11);   // Clear CS11
    TCCR1B |= (1 << CS12) | (1 << CS10);  // Set CS12 and CS10
}

/*
 * Returns current countdown value
 */
uint8_t getCountdownValue() {
    return countdown_value;
}

/*
 * Returns if countdown is active
 */
uint8_t isCountdownActive() {
    return countdown_active;
}

// Timer0 ISR for debouncing - just count milliseconds
ISR(TIMER0_COMPA_vect) {
    ms_counter++;
}

// Timer1 ISR for countdown - decrements countdown value every second
ISR(TIMER1_COMPA_vect) {
    if (countdown_value > 0) {
        countdown_value--;
    } else {
        // Countdown reached zero, stop timer
        TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
        countdown_active = 0;
    }
}   