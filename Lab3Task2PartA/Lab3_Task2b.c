/*
 * 
 *
 * 
 */
#include "Lab3_Task2b.h"

void UART2_Init(void);

int main(void) {
    UART2_Init(); // Initialize UART2
    while (1) {
      while (!(UART2_FR_R & UART_FR_RXFE)) {
        char c = (char)(UART2_DR_R & 0xFF); // Read the character from UART2
        while (UART2_FR_R & UART_FR_TXFF) {}
        UART2_DR_R = c; // Echo character to UART2
      }
    }
    return 0;
}

void UART2_Init(void) {
    RCGCGPIO_R |= (1<<0); // Enable clock for Port A
    while (!(PRGPIO_R & (1<<0))) {} // Wait for clock to stabilize

    RCGCUART_R |= (1<<2); // Enable clock for UART2
    while (!(PRUART_R & (1<<2))) {} // Wait for clock to stabilize

    GPIO_PORTA_AMSEL_R &= ~((1<<6)|(1<<7)); // Disable analog function on PA6 and PA7
    GPIO_PORTA_AFSEL_R |= (1<<6)|(1<<7); // Set PA6 and PA7 to alt function
    GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0x00FFFFFF) | (0x1 << 24) | (0x1 << 28); // Set PA6 and PA7 to UART mode
    GPIO_PORTA_DEN_R |= (1<<6)|(1<<7); // Enable digital function on PA6 and PA7

    UART2_CTL_R &= ~UART_CTL_UARTEN; // Disable UART2 to configure
    UART2_IBRD_R = 104; // Set integer baud rate divisor 9600 baud rate
    UART2_FBRD_R = 11; // Set fractional baud rate divisor
    UART2_LCRH_R = 0x70; // Set line control register (8 data bits, no parity, 1 stop bit)
    UART2_CC_R = 0x5; // Use system clock
    UART2_CTL_R |= (UART_CTL_UARTEN | UART_CTL_TXE | UART_CTL_RXE); // Enable UART2, TXE, RXE
}
