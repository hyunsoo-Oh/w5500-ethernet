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
#define W5500_Sn_MR					0x0000

#define W5500_Sn_CR					0x0001
#define W5500_Sn_SR					0x0003

#define W5500_Sn_PORT				0x0004
#define W5500_Sn_DPORT				0x0010
#define W5500_Sn_DIPR				0x000C
#define W5500_Sn_IR					0x0002
#define W5500_Sn_IMR				0x002C

#define W5500_Sn_TX_FSR				0x0020
#define W5500_Sn_TX_WR				0x0024
#define W5500_Sn_TX_RD				0x0028

#define W5500_Sn_RX_RSR				0x0026
#define W5500_Sn_RX_WR				0x002A
#define W5500_Sn_RX_RD				0x0028

typedef enum {
	TCP = 1, UDP = 2, MACRAW = 3
} Sn_Mode_t;

typedef enum {
	OPEN		= 0x01, 
	LISTEN		= 0x02, 
	CONNECT		= 0x04, 
	DISCONNECT	= 0x08,
	CLOSE		= 0x10,
	SEND		= 0x20,
	SEND_MAC	= 0x21,
	SEND_KEEP	= 0x22,
	RECV		= 0x40
} Sn_Command_t;

typedef enum {
	SOCK_CLOSED			= 0x00,
	SOCK_INIT			= 0x13,
	SOCK_LISTEN			= 0x14,
	SOCK_ESTABLISHED	= 0x17,
	SOCK_CLOSE_WAIT		= 0x1C,
	SOCK_UDP			= 0x22,
	SOCK_MACRAW			= 0x42
} Sn_Status_t;

#endif /* W5500_REGISTER_H_ */