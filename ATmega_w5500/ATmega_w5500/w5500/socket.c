/*
 * socket.c
 *
 * Created: 2025-11-04 오후 10:25:52
 *  Author: hyunsoo-Oh
 */ 

#include "w5500.h"

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

uint8_t setSnRX_RD(uint8_t socket, uint8_t* data)
{
		uint8_t ret;
		ret = w5500_WriteBuff(W5500_BSB_Sn_REG(socket), W5500_Sn_RX_RD, data, 2);
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