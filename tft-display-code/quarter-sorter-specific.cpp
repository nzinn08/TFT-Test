//File Name: quarter-sorter-specific.c
//Description: This contains any misc. quarter-sorter implementations

//Include Files
#include "quarter-sorter-specific.h"
#include "selection-encoder.h"

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
void resetSelectionGUI(TFT_GFX& tftDisplay, TFT_TEXT_BOX& instructionBox, TFT_TEXT_BOX& mainTitle, TFT_TEXT_BOX& stateSelector,
		const uint16_t backgroundColor,const uint16_t fontColor,const uint16_t lineColor,const uint16_t lineThickness,const uint8_t stateSelectorFontSize,
		uint8_t& statesSelected)
{
	statesSelected = 0;
	drawSelectionLines(tftDisplay, backgroundColor, fontColor, lineColor, lineThickness);
	writeSelectionWords(instructionBox, mainTitle, stateSelector, fontColor, stateSelectorFontSize);
}

void drawSelectionLines(TFT_GFX& tftDisplay,const uint16_t backgroundColor,const uint16_t fontColor,const uint16_t lineColor,const uint16_t lineThickness)
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

void writeSelectionWords(TFT_TEXT_BOX& instructionBox, TFT_TEXT_BOX& mainTitle, TFT_TEXT_BOX& stateSelector,const uint16_t fontColor,
		const uint8_t stateSelectorFontSize)
{
	instructionBox.write("*Hold OK button for 3 seconds to confirm selection.", fontColor, 1);
	mainTitle.write("State Selection: ", fontColor, 2);
	stateSelector.write(stateNames[0], fontColor, stateSelectorFontSize);
}

void printCurrentState(CHOSEN_STATE_TEXT_BOX chosenStates[NUM_BOXES], uint8_t& statesSelected,SELECTION_ENCODER* encoderPtr)
{
	chosenStates[statesSelected++].printState(stateNames[encoderPtr->getCurrentNameIndex()]);
	encoderPtr->printNextAvailableState();
	//Stay at the last state box
	if(statesSelected == NUM_BOXES)
	{
	  statesSelected--;
	}
}

void displayInProgress(TFT_GFX& tftDisplay, TFT_TEXT_BOX& instructionBox, const uint16_t lineThickness, const uint16_t lineColor, const uint16_t backgroundColor, const uint16_t fontColor)
{
	tftDisplay.writeFillRect(0, 0, tftDisplay.width(), tftDisplay.height(), lineColor);
	tftDisplay.writeFillRect(lineThickness, lineThickness, tftDisplay.width() - lineThickness * 2, tftDisplay.height() - lineThickness * 2, backgroundColor);
	TFT_TEXT_BOX statusBox{&tftDisplay,backgroundColor, lineThickness, (uint16_t)(tftDisplay.height()/3.0f),(int16_t)(tftDisplay.width() - lineThickness),true};
	statusBox.write("Scan in Progress!", fontColor, 4);
	instructionBox.write("*Press cancel to quit the current operation and go back to selecting states.", fontColor, 1);
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
