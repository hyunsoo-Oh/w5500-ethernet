/*
 * uart.h
 *
 * Created: 2025-10-30 오후 8:59:45
 *  Author: hyunsoo-Oh
 */ 


#ifndef UART_H_
#define UART_H_

#include "../main.h"

void uart0_Init(uint8_t ubrr);

void uart0_Write(uint8_t data);
uint8_t uart0_Read(void);

void uart0_WriteString(uint8_t* str);
void uart0_printf(const char *fmt, ...);

#endif /* UART_H_ */