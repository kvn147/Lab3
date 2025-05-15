/*
 * Copyright @ 2025 Kevin Nguyen and Patrick Rung.
 * Header file for Lab 3 Task 1b. Defines GPIO registers
 * such as ADC, user switches, and timer.
 */
#ifndef _Lab3_Task1a_H_
#define _Lab3_Task1a_H_

#include <stdint.h>

// Port N registers (for LED1 and LED2)
#define GPIODIR_N (*((volatile uint32_t *)0x40064400))
#define GPIODEN_N (*((volatile uint32_t *)0x4006451C))
#define GPIODATA_N (*((volatile uint32_t *)0x400643FC))
// Port F registers (for LED3 and LED4)
#define GPIODIR_F (*((volatile uint32_t *)0x4005D400)) 
#define GPIODEN_F (*((volatile uint32_t *)0x4005D51C))
#define GPIODATA_F (*((volatile uint32_t *)0x4005D3FC))

#define GPIOAFSEL (*((volatile uint32_t *)0x4005D420)) 
#define GPIODEN (*((volatile uint32_t *)0x4005D51C)) 
#define GPIOAMSEL (*((volatile uint32_t *)0x4005D528))

// Clock control register
#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))

// Timer 0A register
#define RCGCTIMER (*((volatile uint32_t *)0x400FE604)) // Enables timer
#define GPTMCFG (*((volatile uint32_t *)0x40030000)) // Configure register
#define GPTMCTL (*((volatile uint32_t *)0x4003000C)) // Control (on/off)
#define GPTMTAMR (*((volatile uint32_t *)0x40030004)) // Timer A mode
#define GPTMAILR (*((volatile uint32_t *)0x40030028)) // Interval load
#define GPTMRIS (*((volatile uint32_t *)0x4003001C)) // Monitor flag
#define GPTMICR (*((volatile uint32_t *)0x40030024)) // Clear flag
#define GPTMIMR (*((volatile uint32_t *)0x40030018)) // Interupt mask
#define GPTMCC  (*((volatile uint32_t *)0x40030FC8)) // 
#define GPTMADCEV (*((volatile uint32_t *)0x40030070)) 

#define NVIC_EN0 (*((volatile uint32_t *)0xE000E100)) // Enable interrupt in NVIC

// Port E registers (for AIN0 pin wired to potentiometer)
#define RCGCGPIO_E (*((volatile uint32_t *)0x400FE618))
#define GPIODIR_E (*((volatile uint32_t *)0x4005C400))
#define GPIODATA_E (*((volatile uint32_t *)0x4005C3FC))
#define GPIODEN_E (*((volatile uint32_t *)0x4005C51C))
#define GPIOAFSEL_E (*((volatile uint32_t *)0x4005C420))
#define GPIOAMSEL_E (*((volatile uint32_t *)0x4005C528))

// ADC registers
#define ADCCC (*((volatile uint32_t *)0x40038FC8)) // ADC Clock configuration
#define RCGCADC (*((volatile uint32_t *)0x400FE638)) // ADC clock control

// ADC0 registers
#define ADC0_EMUX (*((volatile uint32_t *)0x40038014)) // Event multiplexer
#define ADC0_ACTSS (*((volatile uint32_t *)0x40038000)) // sample sequencer 3
#define ADC0_IM (*((volatile uint32_t *)0x40038008)) // Interrupt mask

// ADC0 sample sequencer 3 registers
#define ADC0_SSMUX3 (*((volatile uint32_t *)0x400380A0))
#define ADC0_SSCTL3 (*((volatile uint32_t *)0x400380A4))
#define ADC0_SSFIFO3 (*((volatile uint32_t *)0x400380A8))
#define ADC0_ISC (*((volatile uint32_t *)0x4003800C))

// Set up data for Button J
#define GPIOPUR_J (*((volatile uint32_t *)0x40060510))
#define GPIODIR_J (*((volatile uint32_t *)0x40060400))
#define GPIODEN_J (*((volatile uint32_t *)0x4006051C))
#define GPIODATA_J (*((volatile uint32_t *)0x4006000C))

#endif // _Lab3_Task1a_H_