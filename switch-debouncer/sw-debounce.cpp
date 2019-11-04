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
SW_DEBOUNCE::SW_DEBOUNCE(GPIO_TypeDef* gpio_port, uint16_t gpio_pin, uint16_t timer_period_ms):
gpioPort{gpio_port}, gpioPin{gpio_pin}, timerPeriodMS{timer_period_ms}, currentState{NO_PRESS}
{}

void SW_DEBOUNCE::process(void)
{

}

SWITCH_STATE SW_DEBOUNCE::getCurrentState(void)
{
	return this->currentState;
}
