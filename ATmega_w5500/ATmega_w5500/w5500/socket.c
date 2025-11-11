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

void w5500_Init(W5500_Config_t *config)
{
	w5500_CS_Enable();
	
	// Soft Reset
	w5500_WriteByte(W5500_BSB_COMMON, W5500_MODE, 0x80);
		
	w5500_WriteBuff(W5500_BSB_COMMON, W5500_SOURCE_IP_ADDR,		  config->ip	  , 4);
	w5500_WriteBuff(W5500_BSB_COMMON, W5500_SOURCE_HAREWARE_ADDR, config->mac	  , 6);
	w5500_WriteBuff(W5500_BSB_COMMON, W5500_GATEWAY_ADDR,		  config->gateway , 4);
	w5500_WriteBuff(W5500_BSB_COMMON, W5500_SUBNET_MASK_ADDR,	  config->subnet  , 4);
	
	uint8_t port_arr[2];
	u16_to_arr2(arr2_to_u16(config->port), port_arr);
}

Sn_Status_t Socket_Open(uint8_t socket, Sn_Mode_t mode, uint16_t port)
{
	w5500_WriteByte(W5500_BSB_Sn_REG(socket), W5500_Sn_MR, (uint8_t)mode);
	
	uint8_t port_arr[2];
	u16_to_arr2(port, port_arr);
	w5500_WriteBuff(W5500_BSB_Sn_REG(socket), W5500_Sn_PORT, port_arr, 2);
	
	w5500_WriteByte(W5500_BSB_Sn_REG(socket), W5500_Sn_CR, OPEN);
	
	while (w5500_ReadByte(W5500_BSB_Sn_REG(0), W5500_Sn_CR) != 0);
	
	return w5500_ReadByte(W5500_BSB_Sn_REG(0), W5500_Sn_SR);
}

Sn_Status_t Socket_Connect(uint8_t socket, Dest_Config_t dest)
{
	uint8_t port_arr[2];
	u16_to_arr2(dest.port, port_arr);
	
	w5500_WriteBuff(W5500_BSB_Sn_REG(socket), W5500_Sn_DPORT, port_arr, 2);
	w5500_WriteBuff(W5500_BSB_Sn_REG(socket), W5500_Sn_DIPR, dest.ip, 4);
	
	w5500_WriteByte(W5500_BSB_Sn_REG(socket), W5500_Sn_CR, CONNECT);
	while (w5500_ReadByte(W5500_BSB_Sn_REG(0), W5500_Sn_CR) != 0);
	
	return w5500_ReadByte(W5500_BSB_Sn_REG(0), W5500_Sn_SR);
}

// 미완성 함수
Sn_Status_t Socket_Listen(uint8_t socket)
{
	w5500_WriteByte(W5500_BSB_Sn_REG(socket), W5500_Sn_CR, LISTEN);
	while (w5500_ReadByte(W5500_BSB_Sn_REG(0), W5500_Sn_CR) != 0);
	
	return w5500_ReadByte(W5500_BSB_Sn_REG(0), W5500_Sn_SR);
}

Sn_Status_t Socket_Close(uint8_t socket) 
{
	w5500_WriteByte(W5500_BSB_Sn_REG(socket), W5500_Sn_CR, CLOSE);
	while (w5500_ReadByte(W5500_BSB_Sn_REG(0), W5500_Sn_CR) != 0);
	
	return w5500_ReadByte(W5500_BSB_Sn_REG(0), W5500_Sn_SR);
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

void Socket_Transmit(uint8_t socket, uint8_t* data, uint8_t len)
{
	uint8_t buff[2];
	uint16_t fsr = 0;
	static uint16_t wr = 0;
	
	getSnTX_FSR(socket, buff);
	
	fsr = arr2_to_u16(buff);
	//uart0_printf("fsr : %d\n", fsr);
	
	getSnTX_WR(socket, buff);
	wr = arr2_to_u16(buff);
	//uart0_printf("wr : %d\n", wr);
	
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
	uint16_t v1 = arr2_to_u16(buff);
	getSnRX_RSR(socket, buff);
	uint16_t v2 = arr2_to_u16(buff);
	
	while (v1 != v2)
	{
		v1 = v2;
		getSnRX_RSR(socket, buff);
		v2 = arr2_to_u16(buff);
	}
	rsr = v2;
	//uart0_printf("rsr : %d\n", rsr);
	
	if (rsr == 0)	return 0;
	
	getSnRX_RD(socket, buff);
	rd = arr2_to_u16(buff);
	//uart0_printf("rd : %d\n", rd);
		
	w5500_ReadBuff(W5500_BSB_Sn_RX(socket), rd, data, rsr);
	rd += rsr;
	u16_to_arr2(rd, buff);
	setSnRX_RD(socket, buff);
		
	w5500_WriteByte(W5500_BSB_Sn_REG(socket), W5500_Sn_CR, RECV);
	
	return 1;
}