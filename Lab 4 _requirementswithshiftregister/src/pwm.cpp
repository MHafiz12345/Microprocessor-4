#include "pwm.h"
#include <avr/io.h>

// Initialize PWM on Timer 3 for DC motor control
void initPWM() {
    // Set direction control pins as output
    DDRH |= (1 << PH3) | (1 << PH4);
    
    // Set PWM pin (OC3A) as output
    DDRE |= (1 << PE3);

    // Configure Timer3 for Fast PWM mode with TOP = ICR3 (Mode 14)
    TCCR3A |= (1 << COM3A1);        // Clear OC3A on Compare Match, set at BOTTOM
    TCCR3A |= (1 << WGM31);         // Fast PWM mode
    TCCR3B |= (1 << WGM33) | (1 << WGM32);  // Fast PWM mode with TOP = ICR3
    
    // Set prescaler to 64
    TCCR3B |= (1 << CS31) | (1 << CS30);
    
    // Set TOP value for PWM resolution
    ICR3 = 1023;  // 10-bit resolution to match ADC
    
    // Initial duty cycle
    OCR3A = 0;
}

// Set the motor direction using the direction control pins
// direction: 0 for clockwise, 1 for counterclockwise
void setMotorDirection(unsigned int direction) {
    if (direction == 0) {
        // Set PH3 (pin 6) to high and PH4 (pin 7) to low for clockwise rotation
        PORTH |= (1 << PH3);
        PORTH &= ~(1 << PH4);
    } else {
        // Set PH4 (pin 7) to high and PH3 (pin 6) to low for counterclockwise rotation
        PORTH |= (1 << PH4);
        PORTH &= ~(1 << PH3);
    }
}

// Change PWM duty cycle and motor direction based on ADC result
// result: 10-bit ADC value (0-1023) representing potentiometer position
void changeDutyCycle(unsigned int result) {
    // If in the dead zone (approximately 2.5V), stop the motor
    if (result >= 462 && result <= 562) {
        // Turn off both direction control pins to disable the motor
        PORTH &= ~(1 << PH3);
        PORTH &= ~(1 << PH4);
        // Set PWM to 0
        OCR3A = 0;
    }
    // If less than ~2.5V, clockwise rotation
    else if (result < 462) {
        setMotorDirection(0);
        
        // This will give a duty cycle that decreases linearly from 100% to 0%
        // Map the range 0-462 to 1023-0 for PWM
        OCR3A = (462 - result) * 2;
    }
    // If more than ~2.5V, counterclockwise rotation
    else { // result > 562
        setMotorDirection(1);
        
        // This will give a duty cycle that increases linearly from 0% to 100%
        // Map the range 562-1023 to 0-1023 for PWM
        OCR3A = (result - 562) * 2;
    }
}
