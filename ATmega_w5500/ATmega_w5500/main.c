/*
 * ATmega_w5500.c
 *
 * Created: 2025-10-29 오후 11:37:41
 * Author : hyunsoo-Oh
 */ 

#include "main.h"

#include "peripheral/uart.h"
#include "peripheral/spi.h"
#include "w5500/w5500.h"

#define F_CPU	16000000UL
#define LED_BUILTIN		PB5		

Socket_t sock = {
	.ip[4] = { 169, 254, 202, 177 },
	.port = { 13, 88 },
};

uint8_t gateway_addr[4] = { 192, 128, 1, 1 };

int main(void)
{
	uart0_Init(103); // 9600bps
	w5500_Init();
	
	uint8_t data[4];
	uint8_t check;
	
	w5500_WriteBuff(W5500_BSB_COMMON, W5500_SOURCE_IP_ADDR, sock.ip, 4);
	w5500_WriteBuff(W5500_BSB_Sn_REG(0), W5500_Sn_SOURCE_PORT, sock.port, 2);
	
    /* Replace with your application code */
    while (1) 
    {

    }
}

