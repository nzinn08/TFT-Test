//File Name: selection-encoder.cpp
//Description: This implements the functions for the state-text-box selection encoder

//Include Files
#include "selection-encoder.h"

//Private Constants

//Private Variables

//Public Constants

//Public Variables

//Private Function Prototypes

//Public Function Prototypes

//Private Function Definitions

//Public Function Definitions
SELECTION_ENCODER::SELECTION_ENCODER(uint8_t ticks_per_step, TFT_TEXT_BOX* display_box,
		uint16_t font_color, uint8_t font_size, const char * const * output_text_array, uint16_t output_text_length):
ROTARY_ENCODER(ticks_per_step), displayBox{display_box}, fontColor{font_color},
fontSize{font_size}, outputTextArray{output_text_array}, outputTextLength{output_text_length}, nameIndex{0}
{}

void SELECTION_ENCODER::doStep(bool up_not_down)
{
	if(up_not_down)
	{
		if(this->nameIndex == (this->outputTextLength - 1))
		{
			this->nameIndex = 0;
		}else{
			this->nameIndex++;
		}
	}else{
		if(this->nameIndex == 0)
		{
			this->nameIndex = this->outputTextLength - 1;
		}else{
			this->nameIndex--;
		}
	}
	displayBox->write(this->outputTextArray[this->nameIndex], this->fontColor, this->fontSize);
}
