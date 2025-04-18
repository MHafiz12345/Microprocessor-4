//----------------------------------------------------------------------//
// Author:  Hafiz, Sofia, Fadzar, Johan, Vincent       
// Net ID:   muhammadhafiz, fadzarar, Vliem, putriyuandari, johaniswara        
// Date:     08 April 2025      
// Assignment: Lab 4
//----------------------------------------------------------------------//

#include <avr/io.h>         
#include <avr/interrupt.h>  
#include "pwm.h"            
#include "switch.h"         
#include "timer.h"
#include "shiftregister.h"  // Using shift register for seven-segment display (extra credit)
#include "adc.h"

/* 
 * States for button handling state machine
 * This implements requirement #4: "A state machine is used to implement 
 * the bulk of the functionality of the program"
 */
typedef enum {
    WAIT_PRESS,         // Waiting for button to be pressed
    DEBOUNCE_PRESS,     // Wait a bit after button press to avoid bounce
    WAIT_RELEASE,       // Waiting for button to be released
    DEBOUNCE_RELEASE    // Wait a bit after release to avoid bounce
} ButtonState;

// Global variables
volatile uint8_t button_pressed = 0;    // Flag for button press
ButtonState buttonState = WAIT_PRESS;   // Start in WAIT_PRESS state
volatile uint8_t motor_active = 1;      // Motor status flag (1 = active, 0 = off)
volatile uint8_t countdown_started = 0; // Flag to track if countdown has been started

int main() {
    // Initialize all hardware components
    // Note: All SFR manipulations are wrapped in functions with meaningful names
    // as required by specification #3
    initPWM();              // Configure PWM for motor control
    initSwitchPD0();        // Configure button on PD0 with external interrupt
    initTimer0();           // Set up Timer0 for debouncing
    initTimer1();           // Set up Timer1 for countdown
    initShiftRegister();    // Set up shift register for seven-segment display
    initADC();              // Set up ADC for potentiometer reading on A0
    
    // Enable global interrupts
    sei();

    clearDisplayShift();    // Ensure display is initially blank
    
    // Main program loop
    while (1) {
        // Button state machine - handles debouncing and button press detection
        switch (buttonState) {
            case WAIT_PRESS:
                // Check if button press was detected by interrupt
                if (button_pressed) {
                    // Immediate action on button press - stop motor
                    if (motor_active) {
                        // Turn off motor
                        changeDutyCycle(512);  // 512 is midpoint (motor off)
                        motor_active = 0;
                        
                        // Disable external interrupt during countdown
                        // This fulfills the requirement that "external interrupt should not work
                        // while the timer and seven segment display is counting down"
                        EIMSK &= ~(1 << INT0);
                    }
                    
                    buttonState = DEBOUNCE_PRESS;
                    button_pressed = 0;  // Reset flag for next time
                }
                break;
                
            case DEBOUNCE_PRESS:
                // Wait 30ms to avoid false triggers from button bounce
                delayMs(30);
                
                // Start countdown only once per button press
                if (motor_active == 0 && countdown_started == 0) {
                    // Start countdown from 9 to 0
                    startCountdown();
                    countdown_started = 1;
                }
                
                // Proceed to wait for button release
                buttonState = WAIT_RELEASE;
                break;
                
            case WAIT_RELEASE:
                // Check if button is released (pin reads HIGH due to pull-up)
                if (PIND & (1 << PIND0)) {
                    buttonState = DEBOUNCE_RELEASE;
                }
                break;
                
            case DEBOUNCE_RELEASE:
                // Wait 30ms for button release to stabilize
                delayMs(30);
                
                // Ready for next press
                buttonState = WAIT_PRESS;
                break;
        }
        
        // Motor and countdown handling
        if (motor_active) {
            // Read potentiometer value (0-1023 range)
            unsigned int adcValue = readADC();
            
            // Update motor speed and direction based on potentiometer value
            // The potentiometer controls both speed and direction according to the lab spec:
            // - 0V-2.5V: Clockwise rotation with decreasing speed as voltage increases
            // - 2.5V: Motor stopped
            // - 2.5V-5V: Counterclockwise rotation with increasing speed as voltage increases
            changeDutyCycle(adcValue);
        } 
        else {
            // In countdown mode, update display with current value using shift register
            displayDigitShift(getCountdownValue());
            
            // Check if countdown has finished
            if (!isCountdownActive() && countdown_started) {
                // Clear the display once countdown reaches zero
                clearDisplayShift();
                
                // Re-enable motor operation
                motor_active = 1;
                countdown_started = 0;
                
                // Re-enable external interrupt
                EIMSK |= (1 << INT0);
            }
        }
    }
    
    return 0;  // Will never reach here
}

/* 
 * Interrupt Service Routine for INT0
 * Triggered when button is pressed (any logical change on INT0)
 * Used for switch debouncing as required by the lab spec
 */
ISR(INT0_vect) {
    // Only register a button press when pin is LOW (button pressed) and not already counting down
    if (!(PIND & (1 << PIND0)) && !countdown_started) {
        button_pressed = 1;
    }
}