#include "shiftregister.h"
#include <util/delay.h>

// Define the pins connected to shift register
#define DATA_PIN    PB0    // Serial data pin (SER) 
#define CLOCK_PIN   PB1    // Clock pin (SRCLK)
#define LATCH_PIN   PB2    // Latch pin (RCLK)
#define SR_PORT     PORTB  // Using PORTB for all shift register control pins
#define SR_DDR      DDRB   // Direction register for PORTB

// Array for common cathode 7-segment display patterns (0-9)
// Each bit corresponds to a segment (a-g):
// Bit 0 = a, Bit 1 = b, ..., Bit 6 = g, Bit 7 = dp (not used)
// 0x3F = 0b00111111 = segments a,b,c,d,e,f for digit 0
// 0x06 = 0b00000110 = segments b,c for digit 1
// etc.
const uint8_t SEGMENT_MAP[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

// Initialize the shift register pins
void initShiftRegister(void) {
    // Set the data, clock and latch pins as outputs
    SR_DDR |= (1 << DATA_PIN) | (1 << CLOCK_PIN) | (1 << LATCH_PIN);
    
    // Initialize pins to low
    SR_PORT &= ~((1 << DATA_PIN) | (1 << CLOCK_PIN) | (1 << LATCH_PIN));
}

// Shift out 8 bits of data to the shift register
void shiftOut(uint8_t data) {
    // Pull latch LOW to start data sending
    SR_PORT &= ~(1 << LATCH_PIN);
    
    // Send each bit of data, MSB first
    for (int8_t i = 7; i >= 0; i--) {
        // Clear clock
        SR_PORT &= ~(1 << CLOCK_PIN);
        
        // Set data bit (1 or 0)
        if (data & (1 << i)) {
            SR_PORT |= (1 << DATA_PIN);    // Set data pin HIGH
        } else {
            SR_PORT &= ~(1 << DATA_PIN);   // Set data pin LOW
        }
        
        // Pulse clock to shift in the bit
        SR_PORT |= (1 << CLOCK_PIN);      // Clock HIGH
        _delay_us(1);                     // Short delay for stability
        SR_PORT &= ~(1 << CLOCK_PIN);     // Clock LOW
    }
    
    // Pulse latch to put data on outputs (transfer from shift register to storage register)
    SR_PORT |= (1 << LATCH_PIN);
    _delay_us(1);  // Short delay for stability
}

// Display a single digit (0-9) on the seven segment display
void displayDigitShift(uint8_t digit) {
    if (digit < 10) {
        // Send the corresponding segment pattern to the shift register
        shiftOut(SEGMENT_MAP[digit]);
    }
}

// Clear the display by turning off all segments
void clearDisplayShift(void) {
    // Clear the display by sending 0 (all segments off)
    shiftOut(0x00);
}
