/*
 * socket.c
 *
 * Created: 2025-11-04 오후 10:25:52
 *  Author: hyunsoo-Oh
 */ 

#include "w5500.h"
#include "../peripheral/uart.h"		// 디버깅용

static inline void u16_to_arr2(uint16_t v, uint8_t out[2])
{
	out[0] = (uint8_t)(v >> 8);   // 상위 바이트
	out[1] = (uint8_t)(v & 0xFF); // 하위 바이트
}

static inline uint16_t arr2_to_u16(uint8_t in[2])
{
	return (uint16_t)((uint16_t)in[0] << 8) | (uint16_t)in[1];
}

uint8_t getSnTX_FSR(uint8_t socket, uint8_t* data)
{
	uint8_t ret;
	ret = w5500_ReadBuff(W5500_BSB_Sn_REG(socket), W5500_Sn_TX_FSR, data, 2);
	return (ret == 1) ? 1 : 0;
}

uint8_t getSnRX_RSR(uint8_t socket, uint8_t* data)
{
	uint8_t ret;
	ret = w5500_ReadBuff(W5500_BSB_Sn_REG(socket), W5500_Sn_RX_RSR, data, 2);
	return (ret == 1) ? 1 : 0;
}

uint8_t getSnTX_RD(uint8_t socket, uint8_t* data)
{
	uint8_t ret;
	ret = w5500_ReadBuff(W5500_BSB_Sn_REG(socket), W5500_Sn_TX_RD, data, 2);
	return (ret == 1) ? 1 : 0;
}

uint8_t getSnRX_RD(uint8_t socket, uint8_t* data)
{
	uint8_t ret;
	ret = w5500_ReadBuff(W5500_BSB_Sn_REG(socket), W5500_Sn_RX_RD, data, 2);
	return (ret == 1) ? 1 : 0;
}

uint8_t setSnRX_RD(uint8_t socket, uint8_t* data)
{
	uint8_t ret;
	ret = w5500_WriteBuff(W5500_BSB_Sn_REG(socket), W5500_Sn_RX_RD, data, 2);
	return (ret == 1) ? 1 : 0;
}

uint8_t getSnTX_WR(uint8_t socket, uint8_t* data)
{
	uint8_t ret;
	ret = w5500_ReadBuff(W5500_BSB_Sn_REG(socket), W5500_Sn_TX_WR, data, 2);
	return (ret == 1) ? 1 : 0;
}

uint8_t setSnTX_WR(uint8_t socket, uint8_t* data)
{
	uint8_t ret;
	ret = w5500_WriteBuff(W5500_BSB_Sn_REG(socket), W5500_Sn_TX_WR, data, 2);
	return (ret == 1) ? 1 : 0;
}

uint8_t getSnRX_WR(uint8_t socket, uint8_t* data)
{
	uint8_t ret;
	ret = w5500_ReadBuff(W5500_BSB_Sn_REG(socket), W5500_Sn_RX_WR, data, 2);
	return (ret == 1) ? 1 : 0;
}

uint8_t Socket_Transmit(uint8_t socket, uint8_t* data, uint8_t len)
{
	uint8_t buff[2];
	uint16_t fsr = 0;
	static uint16_t wr = 0;
	
	getSnTX_FSR(socket, buff);
	
	fsr = arr2_to_u16(buff);
	uart0_printf("fsr : %d\n", fsr);
	
	getSnTX_WR(socket, buff);
	wr = arr2_to_u16(buff);
	uart0_printf("wr : %d\n", wr);
	
	w5500_WriteBuff(W5500_BSB_Sn_TX(socket), wr, data, len);
	wr += len;
	u16_to_arr2(wr, buff);
	setSnTX_WR(socket, buff);
	
	w5500_WriteByte(W5500_BSB_Sn_REG(socket), W5500_Sn_CR, SEND);
}

uint8_t Socket_Receive(uint8_t socket, uint8_t* data)
{
	uint8_t buff[2];
	uint16_t rsr = 0;
	static uint16_t rd = 0;
	
	getSnRX_RSR(socket, buff);
	
	rsr = arr2_to_u16(buff);
	uart0_printf("rsr : %d\n", rsr);
	
	getSnRX_RD(socket, buff);
	rd = arr2_to_u16(buff);
	uart0_printf("rd : %d\n", rd);
		
	w5500_ReadBuff(W5500_BSB_Sn_RX(socket), rd, data, rsr);
	rd += rsr;
	u16_to_arr2(rd, buff);
	setSnRX_RD(socket, buff);
		
	w5500_WriteByte(W5500_BSB_Sn_REG(socket), W5500_Sn_CR, RECV);
}