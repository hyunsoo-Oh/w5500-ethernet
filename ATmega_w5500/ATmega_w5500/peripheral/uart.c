/*
 * uart.c
 *
 * Created: 2025-10-30 오후 8:59:55
 *  Author: hyunsoo-Oh
 */ 
#include <stdarg.h>

#include "uart.h"

void uart0_Init(uint8_t ubrr)
{
	/* Baudrate Setting */
	UBRR0H = (uint8_t)(ubrr >> 8);
	UBRR0L = (uint8_t)(ubrr);
	
	/* Enable Rx & Tx, frame format (8-bit, None, 1 stop) */
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	UCSR0C = (3 << UCSZ00);
}

void uart0_Write(uint8_t data)
{
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

uint8_t uart0_Read(void)
{
	while (!(UCSR0A & (1 << RXC0)));
	return UDR0;
}

void uart0_WriteString(uint8_t* str)
{
	while (*str != '\n')
	{
		uart0_Write(*str);
		str++;
	}
	uart0_Write('\n');
}

void uart0_printf(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	
	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt++;
			switch (*fmt)
			{
				case 'c':
				{
					int ch = va_arg(ap, int);
					uart0_Write((uint8_t)ch);
					break;
				}
				case 's':
				{
					const char *s = va_arg(ap, const char *);
					while (*s)
					{
						uart0_Write((uint8_t)(*s++));
					}
					break;
				}
				case 'd':
				{
					int n = va_arg(ap, int);
					char buff[12];
					int i = 0;
					if (n == 0)
					{
						uart0_Write('0');
						break;
					}
					if (n < 0)
					{
						uart0_Write('-');
						n = -n;
					}
					while (n > 0)
					{
						buff[i++] = (uint8_t)('0' + (n % 10));
						n /= 10;
					}
					while (i > 0)
					{
						uart0_Write(buff[--i]);
					}
					break;
				}
				case '%':
				{
					uart0_Write('%');
					break;
				}
			}
		}
		else
		{
			uart0_Write((uint8_t)(*fmt));
		}
		fmt++;
	}
	va_end(ap);
}