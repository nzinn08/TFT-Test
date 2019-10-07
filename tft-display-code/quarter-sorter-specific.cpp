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
void chosenStatePrinter(TFT_TEXT_BOX* chosen_state, uint8_t text_box_num, const char* state_name, uint16_t font_color, uint8_t font_size)
{
    if(chosen_state != nullptr)
    {
        char outputString[STATE_MAX_CHARS + 3 + 1];
        sprintf(outputString, "%d: %s",text_box_num,state_name);
        chosen_state->write(outputString, font_color, font_size);
    }
}
