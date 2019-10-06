//File Name: text-box.h
//Description: This contains the declarations of the class used for a text box

//Header Guards
#ifndef TEXT_BOX_H_
#define TEXT_BOX_H_

//Include Files
#include "gfx.h"

//C Interface
#ifdef __cplusplus
extern "C" {
#endif
//C Public Constants
/*This is an example description for constants and variables. Delete this if it is unused here and copy and paste it to where it is needed. */
/**
 * @brief This is a brief description
 */

//C Public Variables

//C Public Function Prototypes
/*This is an example description for function prototypes. Delete this if it is unused here and copy and paste it to where it is needed. */
/**
 * @brief This is a brief description
 * @param Input_Param_Name - Description of input parameter
 * @ret Description of return value
 */


#ifdef __cplusplus
}
#endif //End C Interface

//C++ Interface
//Class Definitions
class TFT_TEXT_BOX: private TFT_GFX
{
//Constructors
/**
 * @brief Constructor to initialize x and y position as well as pass spi instance
 * @param SPIx: Spi instance
 * @param bg_color: This is the background color this text box will be on top of
 * @param x_pos: x position of bottom left corner of text box
 * @param y_pos: y position of bottom left corner of text box
 */
TFT_TEXT_BOX(SPI_TypeDef *SPIx, uint16_t bg_color, uint16_t x_pos, uint16_t y_pos, bool wrap_allowed = false);
//Delete all other constructors
TFT_TEXT_BOX(void) = delete;
TFT_TEXT_BOX(const TFT_TEXT_BOX&) = delete;
TFT_TEXT_BOX(const TFT_TEXT_BOX&&) = delete;
TFT_TEXT_BOX& operator=(const TFT_TEXT_BOX&) = delete;
TFT_TEXT_BOX& operator=(const TFT_TEXT_BOX&&) = delete;
//Public Function Prototypes
/**
 * @brief Writes a null terminated string in the text box
 * @param string: Null terminated string to write
 * @param font_size: Size of the font
 */
void write(const char* string, uint16_t font_color, uint8_t font_size);
/**
 * @brief This clears the text box
 */
void clear(void);
//Public Constants

//Public Variable
private:
//Private Variables
uint16_t xPos;
uint16_t yPos;
/**
 * @brief This tracks the previous string length so we know how much to erase
 */
uint8_t prevStringLength;
/**
 * @brief This tracks the previous font size so we know how much to erase
 */
uint8_t prevFontSize;
/**
 * @brief This is the color of the background which the text box lies on top of. Used for clear
 */
uint16_t bgColor;
/**
 * @brief This tracks whether we allow text wrapping to a new line
 */
bool wrapAllowed;
//Private Function Prototypes
};

#endif //End Header Guard