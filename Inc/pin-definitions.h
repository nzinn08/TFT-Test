#ifndef PIN_DEFINITIONS_H_
#define PIN_DEFINITIONS_H_

#include "main.h"

#define TFT_DC_PORT (GPIOC)
#define TFT_DC_PIN (0)
#define TFT_RST_PORT (GPIOA)
#define TFT_RST_PIN (0)

#define SPI2_MOSI_PORT (GPIOC)
#define SPI2_MOSI_PIN (3)
#define SPI2_MISO_PORT (GPIOC)
#define SPI2_MISO_PIN (2)
#define SPI2_SCK_PORT (GPIOB)
#define SPI2_SCK_PIN (10)
#define SPI2_CS_PORT (GPIOC)
#define SPI2_CS_PIN (1)

#define PB_MOSI (5)
#define PB_SCK  (3)
#define PB_DC   (4)
#define PA_CS   (10)
#define PA_RST  (15)

#endif