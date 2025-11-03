/*
 * w5500_register.h
 *
 * Created: 2025-11-03 오후 10:03:43
 *  Author: hyunsoo-Oh
 */ 


#ifndef W5500_REGISTER_H_
#define W5500_REGISTER_H_

#define W5500_BSB_COMMON			0x00

/* Common Register List */
#define W5500_MODE					0x0000

#define W5500_GATEWAY_ADDR			0x0001
#define W5500_SUBNET_MASK_ADDR		0x0005
#define W5500_SOURCE_HAREWARE_ADDR	0x0009
#define W5500_SOURCE_IP_ADDR		0x000F

#define W5500_RETRY_TIME			0x0019
#define W5500_RETRY_COUNT			0x001B

/* Socket Register List */
#define W5500_Sn_MODE				0x0000

#define W5500_Sn_COMMAND			0x0001
#define W5500_Sn_SOURCE_PORT		0x0004

#endif /* W5500_REGISTER_H_ */