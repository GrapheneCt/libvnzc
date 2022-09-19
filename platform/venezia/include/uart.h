#ifndef _PDCLIB_UART_H
#define _PDCLIB_UART_H _PDCLIB_UART_H

#define UART_TX_BUS 0

#define UART_REG_BASE_ADDR		0xE2030000
#define UARTCLKGEN_REG_BASE_ADDR	0xE3105000

#define UART_REGS(i)			((void *)(UART_REG_BASE_ADDR + (i) * 0x10000))
#define UARTCLKGEN_REGS(i)		((void *)(UARTCLKGEN_REG_BASE_ADDR + (i) * 4))

void uart_init(int bus);
void uart_write(int bus, unsigned int data);
void uart_print(int bus, char* str);
void uart_printn(int bus, char* str, int n);

#endif