//File Name: gfx.h
//Description: This defines the interface for the graphic fx library

//Header Guards
#ifndef GFX_H_
#define GFX_H_

//Include Files
#include "main.h"
//C Interface
#ifdef __cplusplus
extern "C" {
#endif
//C Public Constants

//C Public Variables

//C Public Function Prototypes

#ifdef __cplusplus
}
#endif //End C Interface

//C++ Interface
//Class Definitions
class TFT_GFX
{
//Constructors
TFT_GFX(SPI_TypeDef *SPIx);
//Delete all other constructors
TFT_GFX(void) = delete;
TFT_GFX(const TFT_GFX&) = delete;
//Public Function Prototypes

//Public Constants

//Public Variable

//Private Variables

//Private Function Prototypes
};

#endif //End Header Guard
