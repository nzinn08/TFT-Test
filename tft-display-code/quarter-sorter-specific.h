//File Name: quarter-sorter-specific.h
//Description: This contains any misc. quarter-sorter info

//Header Guards
#ifndef QUARTER_SORTER_SPECIFIC_H_
#define QUARTER_SORTER_SPECIFIC_H_

//Include Files
#include "text-box.h"

//C Interface
#ifdef __cplusplus
extern "C" {
#endif
//C Public Constants
constexpr uint8_t STATE_MAX_CHARS = 14;
//C Public Variables
const char* const stateNames[50] = {"Alabama", "Alaska", "Arizona", "Arkansas", "California", "Colorado",
		"Connecticut", "Delaware", "Florida", "Georgia", "Hawaii", "Idaho", "Illinois", "Indiana",
		"Iowa", "Kansas", "Kentucky", "Louisiana", "Maine", "Maryland", "Massachusetts", "Michigan",
		"Minnesota", "Mississippi", "Missouri", "Montana", "Nebraska", "Nevada", "New Hampshire",
		"New Jersey", "New Mexico", "New York", "North Carolina", "North Dakota", "Ohio", "Oklahoma",
		"Oregon", "Pennsylvania", "Rhode Island", "South Carolina", "South Dakota", "Tennessee", "Texas",
		"Utah", "Vermont", "Virginia", "Washington", "West Virginia", "Wisconsin", "Wyoming"};
//C Public Function Prototypes
void chosenStatePrinter(TFT_TEXT_BOX* chosen_state, uint8_t text_box_num, const char* state_name, uint16_t font_color, uint8_t font_size);

#ifdef __cplusplus
}
#endif //End C Interface

#endif //End Header Guard
