#ifndef HSPI_H
#define HSPI_H

#include "main.h"

void pullCSLow(void);
void pullCSHigh(void);
void hspi_w8(SPI_TypeDef *SPIx, uint8_t dat);
void hspi_w16(SPI_TypeDef *SPIx, uint16_t dat);
void hspi_cmd(SPI_TypeDef *SPIx, uint8_t cmd);
void ili9341_hspi_init(SPI_TypeDef *SPIx);

#endif 
