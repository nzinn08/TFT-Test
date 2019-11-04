//File Name: sw-debounce.cpp
//Description: This implements the functions for the state-text-box selection encoder

//Include Files
#include "sw-debounce.h"

//Private Constants

//Private Variables

//Public Constants

//Public Variables

//Private Function Prototypes

//Public Function Prototypes

//Private Function Definitions

//Public Function Definitions
SW_DEBOUNCE::SW_DEBOUNCE(GPIO_TypeDef* gpio_port, uint16_t gpio_pin, uint32_t timer_period_ms):
gpioPort{gpio_port}, gpioPin{gpio_pin}, debouncedState{SWITCH_STATE::NO_PRESS},
switchBitSequence{0xFF},stateMachineState{SW_STATE_MACHINE::SWITCH_OPEN}, validPressBitSequence{1 << static_cast<uint8_t>(SW_DEBOUNCE::MS_FOR_VALID_PRESS/timer_period_ms)},
msHeldCounter{0}, timerPeriodMs{timer_period_ms}
{}

void SW_DEBOUNCE::process(void)
{
	this->switchBitSequence = (this->switchBitSequence << 1) | ((this->gpioPort->IDR & this->gpioPin) != 0);
	if(this->stateMachineState == SW_STATE_MACHINE::SWITCH_OPEN)
	{
		if(this->switchBitSequence == this->validPressBitSequence)
		{
			this->stateMachineState = SW_STATE_MACHINE::VALID_PRESS_DETECTED;
			this->msHeldCounter = SW_DEBOUNCE::MS_FOR_VALID_PRESS;
			//Reset the bit sequence to only count held time now
			this->switchBitSequence = 0;
		}
	}else if(this->stateMachineState == SW_STATE_MACHINE::VALID_PRESS_DETECTED)
	{
		//If the bit sequence is all 0's then the switch is being held closed
		if(!this->switchBitSequence)
		{
			this->msHeldCounter+= this->timerPeriodMs;
			//Add if statements to check how long held is here, doesn't even need to be else if
			if(this->msHeldCounter == static_cast<uint32_t>(SWITCH_STATE::THREE_SECOND_PRESS))
			{
				this->debouncedState = SWITCH_STATE::THREE_SECOND_PRESS;
			}
		}else{
			//If there is a 1 in the bit sequence than the switch was released
			this->stateMachineState = SW_STATE_MACHINE::SWITCH_RELEASED;
			this->msHeldCounter = 0;
			if(this->debouncedState < SWITCH_STATE::SHORT_PRESS)
			{
				this->debouncedState = SWITCH_STATE::SHORT_PRESS;
			}
		}
	}else if(this->stateMachineState == SW_STATE_MACHINE::SWITCH_RELEASED)
	{
		if(this->switchBitSequence == SW_DEBOUNCE::SWITCH_OPEN_BIT_SEQUENCE)
		{
			this->stateMachineState = SW_STATE_MACHINE::SWITCH_OPEN;
		}
	}
}

SWITCH_STATE SW_DEBOUNCE::getCurrentState(void)
{
	SWITCH_STATE temp = this->debouncedState;
	this->debouncedState = SWITCH_STATE::NO_PRESS;
	return temp;
}
