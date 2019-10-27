//File Name: generic-rotary-encoder.cpp
//Description: This defines the base functions for the generic rotary encoder ABC

//Include Files
#include "generic-rotary-encoder.h"

//Private Constants

//Private Variables

//Public Constants

//Public Variables

//Private Function Prototypes

//Public Function Prototypes

//Private Function Definitions

//Public Function Definitions
ROTARY_ENCODER::ROTARY_ENCODER(uint8_t ticks_per_step):
ticksPerStep{ticks_per_step}, tickCounter{0}
{}

void ROTARY_ENCODER::doTick(bool up_not_down)
{
    if(up_not_down)
    {
    	//Reset tick counter if we were in the middle of turning it one way and we start turning it the other way
    	if(this->tickCounter < 0)
    	{
    		this->tickCounter = 0;
    	}
        this->tickCounter++;
    }else{
    	//Reset tick counter if we were in the middle of turning it one way and we start turning it the other way
    	if(this->tickCounter > 0)
    	{
    		this->tickCounter = 0;
    	}
        this->tickCounter--;
    }

    uint16_t tempCounter = (this->tickCounter < 0) ? this->tickCounter * -1 : this->tickCounter;
    if(tempCounter >= this->ticksPerStep)
    {
    	this->doStep(up_not_down);
    	this->tickCounter = 0;
    }
}
