//----------------------------------------------------------------------//
// Author:  Hafiz, Sofia, Fadzar, Johan, Vincent       
// Net ID:   muhammadhafiz, fadzarar, Vliem, putriyuandari, johaniswara      
// Date:     08 April 2025      
// Assignment: Lab 4 
//----------------------------------------------------------------------//

#ifndef PWM_H
#define PWM_H

#include <avr/io.h>

// Initializes Timer 3 for PWM output and configures direction control pins
// - Configures Timer 3 in Fast PWM mode with TOP = ICR3
// - Sets up PE3 (OC3A) as PWM output
// - Sets up PH3 and PH4 as direction control pins
void initPWM();

// Sets the motor direction using the L293D control pins
// - direction: 0 for clockwise, 1 for counterclockwise
void setMotorDirection(unsigned int direction);

// Changes PWM duty cycle and motor direction based on ADC result
// - Maps ADC result (0-1023) to appropriate motor speed and direction
// - Implements dead zone around 2.5V (ADC value ~512) to ensure motor stops
// - For values < ~2.5V: clockwise with speed proportional to the alue
// - For values > ~2.5V: counterclockwise with speed proportional to value
void changeDutyCycle(unsigned int result);

#endif // PWM_H