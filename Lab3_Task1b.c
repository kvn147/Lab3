/*
 * Copyright @2025 Kevin Nguyen and Patrick Rung
 * EE/CSE 474: Lab3 Task1b main function
 */

#include <stdlib.h>
#include <stdint.h>
#include "Lab3_Inits.h"

// STEP 0b: Include your header file here
// YOUR CUSTOM HEADER FILE HERE
#include "Lab3_Task1a.h"

// Port J registers (for PJ0 and PJ1) for switches
#define GPIODIR_J (*((volatile uint32_t *)0x40060400))
#define GPIODEN_J (*((volatile uint32_t *)0x4006051C))
#define GPIOPUR_J (*((volatile uint32_t *)0x40060510))
#define GPIODATA_J (*((volatile uint32_t *)0x400603FC))

uint32_t ADC_value;

int main(void) {
  enum frequency freq = PRESET2; // 60 MHz
  LED_Init();            // Initialize the 4 onboard LEDs (GPIO)
  ADCReadPot_Init();     // Initialize ADC0 to read from the potentiometer
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
  float resistance;
  while (1) {
    if (!(GPIODATA_J & 0x01)) {    // SW1 was pressed
      freq = PRESET3; // 12 MHz
    }
    if (!(GPIODATA_J & 0x02)) {    // SW2 was pressed
      freq = PRESET1; // 120 MHz
    }

    PLL_Init(freq);        // Set system clock frequency to freq

    // calculate temperature
    float temperature = 
    resistance = ADC_value / 4095.0 * 10.0; // Convert ADC value to voltage
    
    // clear LEDs
    GPIODATA_N &= ~0x03; // Turn off LED1 and LED2
    GPIODATA_F &= ~0x11; // Turn off LED3 and LED4

    // 5.2: Change the pattern of LEDs based on the resistance
    if (resistance < 2.5) {
      GPIODATA_N |= 0x02; // LED1 on (PN1)
    } else if (resistance < 5.0) {
      GPIODATA_N |= 0x03; // LED2 and LED1 on (PN0 and PN1)
    } else if (resistance < 7.5) {
      GPIODATA_F |= 0x10; // LED3 on (PF4)
      GPIODATA_N |= 0x03; // LED2 and LED1 on (PN0 and PN1)
    } else {
      GPIODATA_F |= 0x11; // LED4 and LED3 on (PF0 and PF4)
      GPIODATA_N |= 0x03; // LED2 and LED1 on (PN0 and PN1)
    }
  }
  return 0;
}

#pragma call_graph_root = "interrupt"
void ADC0SS3_Handler(void) {
  // STEP 4: Implement the ADC ISR.
  // 4.1: Clear the ADC0 interrupt flag
  ADC0_ISC |= 0x8;
  // 4.2: Save the ADC value to global variable ADC_value
  ADC_value = ADC0_SSFIFO3;
}
