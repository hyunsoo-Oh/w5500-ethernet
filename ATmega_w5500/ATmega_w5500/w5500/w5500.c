/*
 * w5500.c
 *
 * Created: 2025-10-29 오후 11:38:18
 *  Author: hyunsoo-Oh
 */ 

#include "w5500.h"
#include "../peripheral/spi.h"

#define BUFF_SIZE		256

static spi_pins_t spi_pins =
{
	.miso = PB4,
	.mosi = PB3,
	.sck = PB5,
	.cs = PB2
};

void w5500_Init(void)
{
	spi_MasterInit(&DDRB, spi_pins);
	_delay_ms(10);
}

uint8_t w5500_ReadVersion(void)
{
	SPI_CS_RESET(DDRB, PORTB, spi_pins.cs);
	_delay_us(2);
	
	spi_MasterWrite((uint8_t)(W5500_ADDR_VERSIONR >> 8));
	spi_MasterWrite((uint8_t)(W5500_ADDR_VERSIONR & 0xFF));
	
	spi_MasterWrite(W5500_CTRL(W5500_BSB_COMMON, RWB_READ, 0x00));
	
	uint8_t value = spi_MasterRead();
	
	_delay_us(2);
	SPI_CS_SET(DDRB, PORTB, spi_pins.cs);
	
	return (value == 0x04) ? 1 : 0;
}

uint8_t w5500_ReadByte(uint8_t bsb, uint16_t addr)
{
	SPI_CS_RESET(DDRB, PORTB, spi_pins.cs);
	_delay_us(2);
		
	spi_MasterWrite((uint8_t)(addr >> 8));
	spi_MasterWrite((uint8_t)(addr & 0xFF));
		
	spi_MasterWrite(W5500_CTRL(bsb, RWB_READ, 0x00));
		
	uint8_t value = spi_MasterRead();
		
	_delay_us(2);
	SPI_CS_SET(DDRB, PORTB, spi_pins.cs);
		
	return value;
}

void w5500_WriteByte(uint8_t bsb, uint16_t addr, uint8_t data)
{
	SPI_CS_RESET(DDRB, PORTB, spi_pins.cs);
	_delay_us(2);
		
	spi_MasterWrite((uint8_t)(addr >> 8));
	spi_MasterWrite((uint8_t)(addr & 0xFF));
		
	spi_MasterWrite(W5500_CTRL(bsb, RWB_WRITE, 0x00));
		
	spi_MasterWrite(data);
		
	_delay_us(2);
	SPI_CS_SET(DDRB, PORTB, spi_pins.cs);
}

uint8_t w5500_ReadBuff(uint8_t bsb, uint16_t addr, uint8_t* data, uint8_t len)
{
	SPI_CS_RESET(DDRB, PORTB, spi_pins.cs);
	_delay_us(2);
	
	spi_MasterWrite((uint8_t)(addr >> 8));
	spi_MasterWrite((uint8_t)(addr & 0xFF));
	
	spi_MasterWrite(W5500_CTRL(bsb, RWB_READ, 0x00));
	
    uint8_t i = 0;
    do {
	    data[i++] = spi_MasterRead();
   } while (i < len);

	_delay_us(2);
	SPI_CS_SET(DDRB, PORTB, spi_pins.cs);
	
	return (i == len) ? 1 : 0;
}

uint8_t w5500_WriteBuff(uint8_t bsb, uint16_t addr, uint8_t* data, uint8_t len)
{
	SPI_CS_RESET(DDRB, PORTB, spi_pins.cs);
	_delay_us(2);
	
	spi_MasterWrite((uint8_t)(addr >> 8));
	spi_MasterWrite((uint8_t)(addr & 0xFF));
	
	spi_MasterWrite(W5500_CTRL(bsb, RWB_WRITE, 0x00));
	
	uint8_t i = 0;
	do {
	    spi_MasterWrite(data[i++]);
	} while (i < len);
	
	_delay_us(2);
	SPI_CS_SET(DDRB, PORTB, spi_pins.cs);
	
	return (i == len) ? 1 : 0;
}