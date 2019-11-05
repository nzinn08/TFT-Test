//File Name: quarter-sorter-specific.h
//Description: This contains any misc. quarter-sorter info

//Header Guards
#ifndef QUARTER_SORTER_SPECIFIC_H_
#define QUARTER_SORTER_SPECIFIC_H_

//Include Files
#include "text-box.h"
#include "gfx.h"

//C Interface
#ifdef __cplusplus
extern "C" {
#endif
//C Structs
//C Public Constants
static constexpr uint8_t NUM_NAMES = 50;
static constexpr uint8_t STATE_MAX_CHARS = 14;
static constexpr uint16_t NUM_BOXES = 5;
//C Public Variables
const char* const stateNames[NUM_NAMES] = {"Alabama", "Alaska", "Arizona", "Arkansas", "California", "Colorado",
		"Connecticut", "Delaware", "Florida", "Georgia", "Hawaii", "Idaho", "Illinois", "Indiana",
		"Iowa", "Kansas", "Kentucky", "Louisiana", "Maine", "Maryland", "Massachusetts", "Michigan",
		"Minnesota", "Mississippi", "Missouri", "Montana", "Nebraska", "Nevada", "New Hampshire",
		"New Jersey", "New Mexico", "New York", "North Carolina", "North Dakota", "Ohio", "Oklahoma",
		"Oregon", "Pennsylvania", "Rhode Island", "South Carolina", "South Dakota", "Tennessee", "Texas",
		"Utah", "Vermont", "Virginia", "Washington", "West Virginia", "Wisconsin", "Wyoming"};
//C Public Function Prototypes
#ifdef __cplusplus
}
#endif //End C Interface

//C++ Interface
//Public Functions
namespace GUI_API
{
void drawSelectionBackground(TFT_GFX& tft_display, uint16_t background_color, uint16_t font_color, uint16_t line_color, uint16_t line_thickness,
		uint8_t chosen_states_font_size, uint8_t state_selector_font_size);
}
//Class Definitions
class CHOSEN_STATE_TEXT_BOX: public TFT_TEXT_BOX
{
public:
//Constructors
CHOSEN_STATE_TEXT_BOX(uint8_t text_box_number, uint16_t font_color, uint8_t font_size, const TFT_TEXT_BOX& general_text_box);
//Default constructor for mass initialization
CHOSEN_STATE_TEXT_BOX(void);
//Public Function Prototypes
void printState(const char* state_name);
const char* getCurrentText(void);
//Public Constants

//Public Variable
private:
//Private Variables
const char* currentText;
uint8_t textBoxNumber;
uint16_t fontColor;
uint8_t fontSize;
//Private Function Prototypes
};


#endif //End Header Guard
