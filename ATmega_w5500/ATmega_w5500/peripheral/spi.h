/*
 * spi.h
 *
 * Created: 2025-10-30 오후 8:51:39
 *  Author: hyunsoo-Oh
 */ 


#ifndef SPI_H_
#define SPI_H_

#include "../main.h"

typedef struct
{
	uint8_t miso;
	uint8_t mosi;
	uint8_t sck;
	uint8_t cs;
} spi_pins_t;

#define SPI_CS_SET(port, pin, num)		do { port |= 1U << num; pin |= 1U << num; } while (0)
#define SPI_CS_RESET(port, pin, num)	do { port |= 1U << num; pin &= ~(1U << num); } while (0)

void spi_MasterInit(volatile uint8_t* ddr, spi_pins_t spi);
void spi_MasterWrite(uint8_t data);
uint8_t spi_MasterRead(void);

#endif /* SPI_H_ */