# Lab 4: DC Motor Control with Potentiometer and Countdown Display

![DC Motor Control with Display](https://github.com/user-attachments/assets/b11ffc76-3463-437d-8446-4eb129294faa)

## 🔧 Overview

This project brings together analog input, PWM-based motor control, external interrupts, timers, and a seven-segment display driven via a shift register. A **DC motor** is controlled using a **potentiometer**, with the direction and speed dynamically mapped based on analog voltage. Pressing a button stops the motor and triggers a **countdown timer**, which is displayed on a **seven-segment display**.

The system showcases multiple core embedded concepts, including:
* Analog-to-digital conversion
* PWM signal generation
* Shift register usage
* External interrupts and debouncing
* Multitimer coordination

## 🎯 Project Behavior

* **Motor Speed and Direction Control**:
   * Controlled by a **potentiometer** (ADC input from A0).
   * **0V–2.5V** → Clockwise, speed decreases toward center.
   * **2.5V** → Motor stops.
   * **2.5V–5V** → Counterclockwise, speed increases.
* **Button Press Behavior**:
   * Pressing the button (PD0) **stops the motor** immediately.
   * Triggers a **countdown from 9 to 0** displayed on a 7-segment display.
   * **Motor and button disabled** during countdown.
   * Once countdown ends, **motor resumes**, and display clears.

## ⚙️ Functional Breakdown

### ✅ Motor Control with PWM
* Uses **Timer3** in Fast PWM mode (10-bit resolution).
* Motor direction controlled via **PH3 and PH4**.
* `changeDutyCycle()` interprets ADC value and maps to speed/direction.

### ✅ Analog Input via ADC
* ADC0 (pin A0) reads potentiometer voltage.
* ADC configured with AVCC reference and prescaler of 128 for 16MHz.

### ✅ Button & Debouncing with INT0
* Button connected to PD0 using **external interrupt (INT0)**.
* State machine ensures clean press/release handling with **30ms debounce**.

### ✅ Countdown via Timer1
* **Timer1** set to interrupt every 1 second.
* Triggers countdown from 9 to 0, with `startCountdown()`.

### ✅ Seven-Segment Display (Shift Register)
* Output handled through **74HC595** or similar shift register.
* Displays countdown values using bitmapped segment patterns.
* `displayDigitShift()` and `clearDisplayShift()` manage visuals.

## 🛠️ Key Features

* Analog input interpreted with ADC
* PWM motor direction and speed control
* External interrupt and debounced input handling
* Countdown logic using Timer1
* Shift register interface for 7-segment display output
* Modular and well-commented embedded codebase

## 📁 File Structure

```
├── adc.c / adc.h          # Analog-to-digital converter setup and usage
├── pwm.c / pwm.h          # Motor control via PWM and direction pins
├── shiftregister.c / .h   # Seven-segment display with shift register
├── switch.c / switch.h    # Button input via INT0
├── timer.c / timer.h      # Timer0 (debounce) and Timer1 (countdown)
├── main.c                 # Central state machine and application logic
```

## 🧠 Concepts in Use

* PWM signal generation with Timer3
* ADC voltage reading and mapping
* Shift register bit shifting and display control
* Interrupt-driven countdown and button handling
* Multi-state control logic using a finite state machine


## 🔌 Hardware Requirements

* AVR ATmega2560 microcontroller
* DC motor with H-bridge driver
* Potentiometer connected to ADC0
* Push button connected to PD0 (INT0)
* 7-segment display connected via 74HC595 shift register
* Power supply (5V)
