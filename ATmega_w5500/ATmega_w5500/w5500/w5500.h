/*
 * w5500.h
 *
 * Created: 2025-10-29 오후 11:38:29
 *  Author: hyunsoo-Oh
 */ 


#ifndef W5500_H_
#define W5500_H_

#include "../main.h"
#include "w5500_register.h"

#define W5500_ADDR_VERSIONR			0x0039
#define W5500_VERSION_VALUE			0x04

#define RWB_READ					0
#define RWB_WRITE					1

#define W5500_CTRL_BSB(bsb)			((uint8_t)((bsb) << 3))
#define W5500_CTRL_RWB(rw)			(rw << 2)
#define	W5500_CTRL_OM(om)			(om & 0x03)

#define W5500_BSB_Sn_REG(n)			(((n) << 2) + 0x01)   // 0:1, 1:5, 2:9...
#define W5500_BSB_Sn_TX(n)			(((n) << 2) + 0x02)
#define W5500_BSB_Sn_RX(n)			(((n) << 2) + 0x03)

#define W5500_CTRL(bsb, rw, om)		( W5500_CTRL_BSB(bsb) | W5500_CTRL_RWB(rw) | W5500_CTRL_OM(om) )

typedef struct {
	uint8_t ip[4];
	uint8_t port[2];
	uint8_t gateway[4];
	uint8_t subnet[4];
	uint8_t mac[6];
} Socket_t;

void w5500_Init(void);

uint8_t w5500_ReadVersion(void);

uint8_t w5500_ReadByte(uint8_t bsb, uint16_t addr);
void w5500_WriteByte(uint8_t bsb, uint16_t addr, uint8_t data);

uint8_t w5500_ReadBuff(uint8_t bsb, uint16_t addr, uint8_t* data, uint8_t len);
uint8_t w5500_WriteBuff(uint8_t bsb, uint16_t addr, uint8_t* data, uint8_t len);

#endif /* W5500_H_ */