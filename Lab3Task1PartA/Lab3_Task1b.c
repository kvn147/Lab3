/*
 * Copyright @2025 Kevin Nguyen and Patrick Rungruengwatanachai.
 * EE/CSE 474: Lab 3 Task 1b main function. Initializes
 * buttons, timers, ADC, and ISR. Toggles clock speeds by buttons
 * and reads temperature from ADC and prints it to terminal I/O.
 */

// NOTE: This is the main function for Task 1a. You should start by
// implementing Lab3_Driver.c (STEP 0a, 1-3) and then come back to finish
// the ISR and the main function (STEP 0b, 4-5).

#include <stdint.h>
#include <stdio.h>
#include "Lab3_Initsb.h"

// STEP 0b: Include your header file here
// YOUR CUSTOM HEADER FILE HERE
#include "Lab3_Task1b.h"

uint32_t ADC_value;

// Initialize and configure the buttons for SW 1 and SW 2
void initButtons();

// Get the status of whether SW1 is pressed or not
unsigned long Get_SW1();

// Get the status of whether SWw is pressed or not
unsigned long Get_SW2();

int main(void) {
  // Select system clock frequency preset
  enum frequency freq = PRESET2; // 60 MHz
  PLL_Init(freq);        // Set system clock frequency to 60 MHz
  LED_Init();            // Initialize the 4 onboard LEDs (GPIO)
  ADCReadTemp_Init();     // Initialize ADC0 to read temperature
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
  initButtons();  // Init buttons L
  float temp;
  while(1) {
    GPTMICR = 0x1; // Clear any timeout flag
    temp =  147.5f - ((247.5 * ADC_value) / 4096.0f);
    printf("%f\n", temp);

    if(Get_SW1()) { //SW1
      PLL_Init(PRESET3);  // set freq to 12
    }

    if(Get_SW2()) { // SW2
      PLL_Init(PRESET1); // set freq to 120
    }
  }
  return 0;
}

void initButtons() {
  volatile unsigned short delay = 0;
  RCGCGPIO |= 0x0100; 
  delay++;
  delay++;
  GPIODIR_J = 0x00;
  GPIODEN_J = 0x03;
  GPIOPUR_J = 0x03;
}

unsigned long Get_SW1() {
  return !(GPIODATA_J & 0x1);
}

unsigned long Get_SW2() {
  return !(GPIODATA_J & 0x2);
}

void ADC0SS3_Handler(void) {
  // STEP 4: Implement the ADC ISR.
  // 4.1: Clear the ADC0 interrupt flag
  ADC0_ISC |= 0x1;
  // 4.2: Save the ADC value to global variable ADC_value
  ADC_value = ADC0_SSFIFO3;
}
