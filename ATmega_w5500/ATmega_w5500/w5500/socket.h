/*
 * socket.h
 *
 * Created: 2025-11-04 오후 10:28:58
 *  Author: jweli
 */ 


#ifndef SOCKET_H_
#define SOCKET_H_

#include "../main.h"

void w5500_Init(W5500_Config_t *config);

Sn_Status_t Socket_Open(uint8_t socket, Sn_Mode_t mode, uint16_t port);
Sn_Status_t Socket_Connect(uint8_t socket, Dest_Config_t dest);
Sn_Status_t Socket_Listen(uint8_t socket);	// 미완성 함수
Sn_Status_t Socket_Close(uint8_t socket);

// getSnTX_FSR : 송신 버퍼에서 쓸 수 있는 빈 공간의 크기 (초기값 : 0x0800)
uint8_t getSnTX_FSR(uint8_t socket, uint8_t* data);
// getSnRX_RSR : 수신 버퍼에 존재하는 읽을 수 있는 데이터의 크기 (초기값 : 0x0000)
uint8_t getSnRX_RSR(uint8_t socket, uint8_t* data);

uint8_t getSnTX_RD(uint8_t socket, uint8_t* data);	// 
uint8_t getSnRX_RD(uint8_t socket, uint8_t* data);
uint8_t setSnRX_RD(uint8_t socket, uint8_t* data);	//

uint8_t getSnTX_WR(uint8_t socket, uint8_t* data);
uint8_t setSnTX_WR(uint8_t socket, uint8_t* data);
uint8_t getSnRX_WR(uint8_t socket, uint8_t* data);

uint8_t Socket_Transmit(uint8_t socket, uint8_t* data, uint8_t len);
uint8_t Socket_Receive(uint8_t socket, uint8_t* data);

#endif /* SOCKET_H_ */