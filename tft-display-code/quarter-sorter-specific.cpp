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
