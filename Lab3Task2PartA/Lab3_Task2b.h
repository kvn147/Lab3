/*
 * Copyright @ 2025 Kevin Nguyen and Patrick Rung
 * 
 * Header file for Lab 3 Task 2b. Defines GPIO A and UART2 registers.
 */
#ifndef _LAB3_TASK2B_H_
#define _LAB3_TASK2B_H_
#include "Lab3_Task2a.h"
#include <stdint.h>

// Peripheral enable
#define RCGCGPIO_R  (*((volatile uint32_t *)0x400FE608)) // GPIO peripheral clock control
#define RCGCUART_R  (*((volatile uint32_t *)0x400FE618)) // UART peripheral clock control
#define PRGPIO_R   (*((volatile uint32_t *)0x400FEA08)) // GPIO peripheral ready
#define PRUART_R   (*((volatile uint32_t *)0x400FEA18)) // UART peripheral ready

// GPIO A Registers for Port A
#define GPIO_PORTA_AFSEL_R (*((volatile uint32_t *)0x40058420)) // GPIO Alternate Function Select
#define GPIO_PORTA_PCTL_R  (*((volatile uint32_t *)0x4005852C)) // GPIO Port Control
#define GPIO_PORTA_DEN_R   (*((volatile uint32_t *)0x4005851C)) // GPIO Digital Enable
#define GPIO_PORTA_AMSEL_R  (*((volatile uint32_t *)0x40058528)) // GPIO Analog Mode Select

// UART2 Registers
#define UART2_DR_R   (*((volatile uint32_t *)0x4000E000)) // UART2 Data Register
#define UART2_FR_R   (*((volatile uint32_t *)0x4000E018)) // UART2 Flag Register
#define UART2_IBRD_R (*((volatile uint32_t *)0x4000E024)) // UART2 Integer Baud Rate Divisor
#define UART2_FBRD_R (*((volatile uint32_t *)0x4000E028)) // UART2 Fractional Baud Rate Divisor
#define UART2_LCRH_R (*((volatile uint32_t *)0x4000E02C)) // UART2 Line Control
#define UART2_CTL_R  (*((volatile uint32_t *)0x4000E030)) // UART2 Control
#define UART2_CC_R   (*((volatile uint32_t *)0x4000EFC8)) // UART2 Clock Configuration

// UART Flags and Control
#define UART_FR_RXFE     0x00000010 // Receive FIFO Empty
#define UART_FR_TXFF     0x00000020 // Transmit FIFO Full
#define UART_CTL_UARTEN  0x00000001 // UART Enable
#define UART_CTL_TXE     0x00000100 // Transmit Enable
#define UART_CTL_RXE     0x00000004 // Receive Enable
#define UART_LCRH_WLEN_8 0x00000060 // 8-bit word length

#endif // _LAB3_TASK2B_H_