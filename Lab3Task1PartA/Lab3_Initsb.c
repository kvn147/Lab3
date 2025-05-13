/**
 * EE/CSE 474: Lab3 drivers starter code
 */

#include "PLL_Header.h"

// STEP 0a: Include your header file here
// YOUR CUSTOM HEADER FILE HERE
#include "Lab3_Task1b.h"

int PLL_Init(enum frequency freq) {
    // Do NOT modify this function.
    MOSCCTL &= ~(0x4);                      // Power up MOSC
    MOSCCTL &= ~(0x8);                      // Enable MOSC
    while ((RIS & 0x100) == 0) {};          // Wait for MOSC to be ready
    RSCLKCFG |= (0x3 << 20);                // Select MOSC as system clock source
    RSCLKCFG |= (0x3 << 24);                // Select MOSC as PLL clock source

    PLLFREQ0 |= 0x60;                       // Set MINT field
    PLLFREQ1 |= 0x4;                        // Set N field

    MEMTIM0 &= ~((0xF << 22) | (0xF << 6));     // Reset FBCHT and EBCHT
    MEMTIM0 &= ~((0xF << 16) | (0xF << 0));     // Reset EWS and FWS
    MEMTIM0 &= ~((0x1 << 21) | (0x1 << 5));     // Reset FBCE and EBCE

    RSCLKCFG &= ~(0x1 << 28);                   // Temporarilly bypass PLL

    switch (freq) {
        case 120:
            MEMTIM0 |= (0x6 << 22) | (0x6 << 6);    // Set FBCHT and EBCHT
            MEMTIM0 |= (0x5 << 16) | (0x5 << 0);    // Set EWS and FWS
            RSCLKCFG |= 0x3;                        // Set PSYSDIV to use 120 MHZ clock
            RSCLKCFG &= ~0x3FC;                     // Update PSYSDIV field
            break;
        case 60:
            MEMTIM0 |= (0x3 << 22) | (0x3 << 6);    // Set FBCHT and EBCHT
            MEMTIM0 |= (0x2 << 16) | (0x2 << 0);    // Set EWS and FWS
            RSCLKCFG |= 0x7;                        // Set PSYSDIV to use 60 MHZ clock
            RSCLKCFG &= ~0x3F8;                     // Update PSYSDIV field
            break;
        case 12:
            MEMTIM0 |= (0x1 << 21) | (0x1 << 5);    // Set FBCE and EBCE
            RSCLKCFG |= 0x27;                       // Set PSYSDIV to use 12 MHZ clock
            RSCLKCFG &= ~0x3D8;                     // Update PSYSDIV field
            break;
        default:
            return -1;
    }

    RSCLKCFG |= (0x1 << 30);                // Enable new PLL settings
    PLLFREQ0 |= (0x1 << 23);                // Power up PLL
    while ((PLLSTAT & 0x1) == 0) {};        // Wait for PLL to lock and stabilize

    RSCLKCFG |= (0x1u << 31) | (0x1 << 28);  // Use PLL and update Memory Timing Register
    return 1;
}

void LED_Init(void) {
  // STEP 1: Initialize the 4 on board LEDs by initializing the corresponding
  // GPIO pins.
  RCGCGPIO |= (1<<5) | (1<<12); // Enable clock for LEDs
  volatile unsigned short delay = 0;
  delay++, delay++; 
  // Set LED pins as outputs
  RCGCGPIO |= 0x1020;
  GPIODIR_F |= 0x11;  // Set PF0 (LED4) and PF4 (LED3) as outputs
  GPIODIR_N |= 0x03;  // Set PN0 (LED2) and PN1 (LED1) as outputs
  // Set LED pins as digital pins
  GPIODEN_F |= 0x11;  // Enable digital for PF0 and PF4
  GPIODEN_N |= 0x03;  // Enable digital for PN0 and PN1
}

void ADCReadPot_Init(void) {
  // STEP 2: Initialize ADC0 SS3.
  // 2.1: Enable the ADC0 clock
  RCGCADC |= 0x1; // Enable ADC0 clock
  // 2.2: Delay for RCGCADC (Refer to page 1073)
  volatile unsigned short delay = 0;
  delay++, delay++;
  // 2.3: Power up the PLL (if not already)
  PLLFREQ0 |= 0x00800000; // we did this for you
  // 2.4: Wait for the PLL to lock
  while (PLLSTAT != 0x1); // we did this for you
  // 2.5: Configure ADCCC to use the clock source defined by ALTCLKCFG
  ADCCC = 0x1; // Set ADC clock to use system clock (60 MHz)
  // 2.6: Enable clock to the appropriate GPIO Modules (Hint: Table 15-1)
  RCGCGPIO |= (1<<4); // Enable clock for Port E
  delay++, delay++;
  // 2.7: Delay for RCGCGPIO
  delay++, delay++;
  // 2.8: Set the GPIOAFSEL bits for the ADC input pins
  GPIOAFSEL_E |= (1<<3);
  // 2.9: Clear the GPIODEN bits for the ADC input pins
  GPIODEN_E &= ~(1<<3); // Disable digital function for PE3 (AIN0)
  // 2.10: Disable the analog isolation circuit for ADC input pins (GPIOAMSEL)
  GPIOAMSEL_E |= (1<<3); // Enable analog function for PE3 (AIN0)
  // 2.11: Disable sample sequencer 3 (SS3)
  ADC0_ACTSS &= ~0x8; // Disable SS3 (bit 3)
  // 2.12: Select timer as the trigger for SS3
  ADC0_EMUX = (ADC0_EMUX & ~0xF000) | (0x5 << 12); // Set bits 15-12 to 0x5 (timer trigger)
  // 2.13: Select the analog input channel for SS3 (Hint: Table 15-1)
  ADC0_SSMUX3 = 0x0;
  // 2.14: Configure ADCSSCTL3 register
  ADC0_SSCTL3 = 0xC; // sample 0 and 1, end of sequence, no interrupts and bit 4 is used for temp
  // 2.15: Set the SS3 interrupt mask
  ADC0_IM |= 0x8; // Enable SS3 interrupt (bit 3)
  // 2.16: Set the corresponding bit for ADC0 SS3 in NVIC
  NVIC_EN0 |= (1 << 17); // Enable ADC0 SS3 interrupt in NVIC (bit 17)
  ADC0_SSTSH3  = 0x4; // Set sample hold width to be 16 for temp
  // 2.17: Enable ADC0 SS3
  ADC0_ACTSS |= 0x8; // Enable SS3

}

void TimerADCTriger_Init(void) {
  // STEP 3: Initialize Timer0A to trigger ADC0 at 1 HZ.
  // Hint: Refer to section 13.3.7 of the datasheet

  // YOUR CODE HERE
  RCGCTIMER |= 0x1; // enable clock for Timer 0 (GPTM0)
  while ((RCGCTIMER & 0x1) == 0) {}
    
  GPTMCTL = 0x0; // Disable timer A for initialization 
  GPTMCTL |= 0x20;
  GPTMCFG = 0x0; // 32-bit timer configuration
  GPTMTAMR |= 0x12; // set to periodic mode and count down
  GPTMAILR = 16000000; // Load for 1 Hz
  GPTMICR |= 0x1; // Clear any timeout flag
  GPTMIMR |= 0x1; // GPTM interupt mask
  GPTMCC |= 0x1; // Hooks up to PLL
  GPTMCTL |= 0x1; // Enable timer A
  GPTMADCEV |= 0x1; 
}

// NEXT STEP: Go to Lab3_Task1a.c and finish implementing ADC0SS3_Handler
