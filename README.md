/**
 * @file timer.h
 * @brief Timer setup and delay functions
 * 
 * This file contains declarations for setting up timers and
 * providing delay functions with millisecond and microsecond
 * precision.
 */

#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

/**
 * @brief Initialize Timer0 for millisecond timing
 * 
 * Configures Timer0 in CTC mode to generate interrupts
 * every 1 millisecond for general timing purposes.
 */
void initTimer0(void);

/**
 * @brief Initialize Timer1 for second-based countdown
 * 
 * Configures Timer1 in CTC mode to generate interrupts
 * every 1 second for countdown functionality.
 */
void initTimer1(void);

/**
 * @brief Get current millisecond counter value
 * 
 * @return Current millisecond count
 * 
 * Returns the current millisecond counter value,
 * which increments every millisecond from system startup.
 */
uint32_t getMilliseconds(void);

/**
 * @brief Wait for a specific number of milliseconds
 * 
 * @param ms Number of milliseconds to wait
 * 
 * Blocks execution for the specified number of milliseconds.
 */
void delayMs(uint16_t ms);

/**
 * @brief Wait for a specific number of microseconds
 * 
 * @param us Number of microseconds to wait
 * 
 * Delays for the specified number of microseconds.
 * Maximum delay is 16383 microseconds.
 */
void delayUs(uint16_t us);

/**
 * @brief Start the countdown timer
 * 
 * @param seconds The countdown duration in seconds
 * 
 * Initializes and starts a countdown from the specified
 * value to zero, using Timer1 for second-based timing.
 */
void startCountdown(uint
