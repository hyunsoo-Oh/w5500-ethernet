/*
 * socket.h
 *
 * Created: 2025-11-04 오후 10:28:58
 *  Author: jweli
 */ 


#ifndef SOCKET_H_
#define SOCKET_H_

#include "../main.h"

// getSnTX_FSR : 송신 버퍼에서 쓸 수 있는 빈 공간의 크기 (초기값 : 0x0800)
uint8_t getSnTX_FSR(uint8_t socket, uint8_t* data);
// getSnRX_RSR : 수신 버퍼에 존재하는 읽을 수 있는 데이터의 크기 (초기값 : 0x0000)
uint8_t getSnRX_RSR(uint8_t socket, uint8_t* data);

uint8_t getSnTX_RD(uint8_t socket, uint8_t* data);	// 
uint8_t setSnRX_RD(uint8_t socket, uint8_t* data);	//

uint8_t setSnTX_WR(uint8_t socket, uint8_t* data);
uint8_t getSnRX_WR(uint8_t socket, uint8_t* data);


#endif /* SOCKET_H_ */