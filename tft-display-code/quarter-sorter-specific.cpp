//File Name: quarter-sorter-specific.c
//Description: This contains any misc. quarter-sorter implementations

//Include Files
#include "quarter-sorter-specific.h"

//Private Constants

//Private Variables

//Public Constants

//Public Variables

//Private Function Prototypes

//Public Function Prototypes

//Private Function Definitions

//Public Function Definitions
namespace GUI_API
{
void drawSelectionBackground(TFT_GFX& tftDisplay, uint16_t backgroundColor, uint16_t fontColor, uint16_t lineColor, uint16_t lineThickness,
		uint8_t chosenStatesFontSize, uint8_t stateSelectorFontSize)
{
	//Set background to correct color and add outline
	tftDisplay.writeFillRect(0, 0, tftDisplay.width(), tftDisplay.height(), lineColor);
	tftDisplay.writeFillRect(lineThickness, lineThickness, tftDisplay.width() - lineThickness * 2, tftDisplay.height() - lineThickness * 2, backgroundColor);
	//Draw the GUI lines
	tftDisplay.writeFillRect(0,(tftDisplay.height()-lineThickness)/2, tftDisplay.width(), lineThickness, lineColor);
	for(uint16_t i = 1; i < NUM_BOXES; i++)
	{
	  tftDisplay.writeFillRect(0, tftDisplay.height()/2 + i*(tftDisplay.height()/(2 *NUM_BOXES)) - lineThickness/2, tftDisplay.width(), lineThickness, lineColor);
	}
}

}//namespace GUI_API

CHOSEN_STATE_TEXT_BOX::CHOSEN_STATE_TEXT_BOX(uint8_t text_box_number, uint16_t font_color,
		uint8_t font_size, const TFT_TEXT_BOX& general_text_box):
TFT_TEXT_BOX(general_text_box),currentText{nullptr}, textBoxNumber{text_box_number}, fontColor{font_color}, fontSize{font_size}
{}

CHOSEN_STATE_TEXT_BOX::CHOSEN_STATE_TEXT_BOX(void):
TFT_TEXT_BOX(),currentText{nullptr}, textBoxNumber{0}, fontColor{0}, fontSize{0}
{}

void CHOSEN_STATE_TEXT_BOX::printState(const char* state_name)
{
	this->currentText = state_name;
	char outputString[STATE_MAX_CHARS + 3 + 1];
	sprintf(outputString, "%d: %s",this->textBoxNumber,state_name);
	this->write(outputString, this->fontColor, this->fontSize);
}

const char* CHOSEN_STATE_TEXT_BOX::getCurrentText(void)
{
	return this->currentText;
}
