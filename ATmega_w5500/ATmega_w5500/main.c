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
#include "w5500/socket.h"

#define F_CPU	16000000UL
#define LED_BUILTIN		PB5		

Socket_t sock = {
	.ip		 = { 169, 254, 202, 177 },
	.port	 = { 0x13, 0x88 },
	.gateway = { 0, 0, 0, 0 },
	.subnet  = { 255, 255, 0, 0 },
	.mac	 = { 0x00, 0x08, 0xDC, 0x01, 0x02, 0x03 }
};

uint8_t gateway_addr[4] = { 192, 128, 1, 1 };
uint8_t dest_addr[4] = { 169, 254, 202, 190 };

int main(void)
{
	uart0_Init(103); // 9600bps
	w5500_Init();
	
	_delay_ms(500);
	
	uint8_t data[4];
	uint8_t status = SOCK_CLOSED;
	uint8_t length[2] = { 0, 0 };
	
	// Soft Reset
	w5500_WriteByte(W5500_BSB_COMMON, W5500_MODE, 0x80);
	
	// IP Address Setting
	w5500_WriteBuff(W5500_BSB_COMMON, W5500_SOURCE_IP_ADDR, sock.ip, 4);
	
	// Socket Setting
	w5500_WriteByte(W5500_BSB_Sn_REG(0), W5500_Sn_MR, 0x01); 
	w5500_WriteBuff(W5500_BSB_Sn_REG(0), W5500_Sn_DIPR, dest_addr, 4);
	w5500_WriteBuff(W5500_BSB_Sn_REG(0), W5500_Sn_PORT, sock.port, 2);
	w5500_WriteBuff(W5500_BSB_Sn_REG(0), W5500_Sn_DPORT, sock.port, 2);
	
	w5500_WriteByte(W5500_BSB_Sn_REG(0), W5500_Sn_CR, OPEN);

	while (w5500_ReadByte(W5500_BSB_Sn_REG(0), W5500_Sn_CR) != 0);
	while (w5500_ReadByte(W5500_BSB_Sn_REG(0), W5500_Sn_SR) != SOCK_INIT);
	
	// Connect
	w5500_WriteByte(W5500_BSB_Sn_REG(0), W5500_Sn_CR, CONNECT);
	while (w5500_ReadByte(W5500_BSB_Sn_REG(0), W5500_Sn_CR) != 0);
	do
	{
		_delay_ms(1000);
		status = w5500_ReadByte(W5500_BSB_Sn_REG(0), W5500_Sn_SR);
		uart0_printf("status = %d\n", status);
	} while (status != SOCK_ESTABLISHED);
	while (w5500_ReadByte(W5500_BSB_Sn_REG(0), W5500_Sn_CR) != 0);
	uart0_printf("Test5\n");
	
    /* Replace with your application code */
    while (1) 
    {
		if (getSnRX_RSR(0, length))
		{
			uart0_printf("RSR Length %d, %d\n", length[0], length[1]);	
		}
		_delay_ms(2000);
    }
}

