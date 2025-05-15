/**
/*
 * Copyright @ 2025 Kevin Nguyen and Patrick Rungruengwatanachai
 * 
 * Main file for Lab 3 Task 2a. Initializes buttons, timers, ADC, and UART.
 * Toggle clock speeds by buttons and reads temperature from ADC and sends it over UART.
 */

#include <stdint.h>
#include <stdio.h>

#include "Lab3Task2_Inits.h"
#include "Lab3_Task2a.h"

uint32_t ADC_value;

// Initialize and configure the buttons for SW 1 and SW 2
void Init_Buttons();

// Get the status of whether SW1 is pressed or not
unsigned long Get_SW1();

// Get the status of whether SWw is pressed or not
unsigned long Get_SW2();

int main(void) {
  // Select system clock frequency preset
  enum frequency freq = PRESET2; // 60 MHz
  PLL_Init(freq);        // Set system clock frequency to 60 MHz
  ADCReadTemp_Init();     // Initialize ADC0 to read from the potentiometer
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
  Init_Buttons();  // Init buttons L
  UART_Init();
  while(1) {
    GPTMICR = 0x1; // Clear any timeout flag
    if(Get_SW1()) { //SW1
      PLL_Init(PRESET3);  // set freq to 12
    }
    if(Get_SW2()) { // SW2
      PLL_Init(PRESET1); // set freq to 120
    }
  }
  return 0;
}

void Init_Buttons() {
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
  ADC0_ISC |= 0x1;
  ADC_value = ADC0_SSFIFO3;

  char tempBuffer[100];
  float temp =  147.5f - ((247.5 * ADC_value) / 4096.0f);

  snprintf(tempBuffer, sizeof(tempBuffer), "temp: %f\r\n", temp);
  int TxIndex = 0;
  while(TxIndex < 100 && tempBuffer[TxIndex] != '\0') {
    if(UARTFR_A & 0x80) {
      UARTDR_A = tempBuffer[TxIndex];
      TxIndex++;
    }
  }
}
