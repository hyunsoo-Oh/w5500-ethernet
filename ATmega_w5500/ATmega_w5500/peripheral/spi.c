/*
 * spi.c
 *
 * Created: 2025-10-30 오후 8:51:29
 *  Author: hyunsoo-Oh
 */ 

#include "spi.h"

void spi_MasterInit(volatile uint8_t* ddr, spi_pins_t spi)
{
	*ddr |= 1 << spi.mosi | 1 << spi.sck;
	// SPI enable, Master, F_CPU/16
	SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0);
	// MSB first + Mode 0 (CPOL=0, CPHA=0)
	SPCR &= ~((1 << DORD) | (1 << CPOL) | (1 << CPHA));
}

void spi_MasterWrite(uint8_t data)
{
	SPDR = data;
	while (!(SPSR & (1 << SPIF)));
}

uint8_t spi_MasterRead(void)
{
	SPDR = 0xFF;
	while (!(SPSR & (1 << SPIF)));
	return SPDR;
}

uint8_t spi_MasterWriteRead(uint8_t data)
{
		SPDR = data;
		while (!(SPSR & (1 << SPIF)));
		return SPDR;
}