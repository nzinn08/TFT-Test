//File Name: text-box.cpp
//Description: This implements functions necessary to use a text box

//Include Files
#include "text-box.h"

//Private Constants

//Private Variables

//Public Constants

//Public Variables

//Private Function Prototypes

//Public Function Prototypes

//Private Function Definitions

//Public Function Definitions
TFT_TEXT_BOX::TFT_TEXT_BOX(SPI_TypeDef *SPIx, uint16_t bg_color, uint16_t x_pos, uint16_t y_pos, bool wrap_allowed):
TFT_GFX{SPIx}, bgColor{bg_color}, xPos{x_pos}, yPos{y_pos}, prevStringLength{0}, prevFontSize{0}, wrapAllowed{wrap_allowed}
{}

void TFT_TEXT_BOX::write(const char* string, uint16_t font_color, uint8_t font_size)
{
    //First clear previous text
    this->clear();
    //Then draw new text
    this->prevStringLength = this->drawString(this->xPos, this->yPos, string, font_color, font_color, font_size, font_size, this->wrapAllowed);
    this->prevFontSize = font_size;
}

void TFT_TEXT_BOX::clear(void)
{
    this->writeFillRect(this->xPos, this->yPos, this->prevStringLength * (this->prevFontSize * 6), this->prevFontSize * 8, this->bgColor);
}