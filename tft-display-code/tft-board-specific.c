#include "tft-board-specific.h"
#include "pin-definitions.h"


void resetTftBoard(void)
{
	TFT_RST_PORT->ODR &= ~(1 << TFT_RST_PIN);
	HAL_Delay(150);
	TFT_RST_PORT->ODR |=  (1 << TFT_RST_PIN);
	HAL_Delay(150);
}

