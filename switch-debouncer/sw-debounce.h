//File Name: sw-debounce.h
//Description: This implements the generic debouncing for a switch

//Header Guards
#ifndef SW_DEBOUNCE_H_
#define SW_DEBOUNCE_H_

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
enum SWITCH_STATE
{
	NO_PRESS,
	SHORT_PRESS,
	THREE_SECOND_PRESS,
};
//Class Definitions
class SW_DEBOUNCE
{
public:
//Constructors
/**
 * @brief This takes in the initialized-as-input gpio pin
 * @param gpio_port: port of switch
 * @param gpio_pin: pin of switch
 * @param timer_period_ms: The amount of time between timer interrupts in ms at which @process should be called.
 */
SW_DEBOUNCE(GPIO_TypeDef* gpio_port, uint16_t gpio_pin, uint16_t timer_period_ms);
//Public Function Prototypes
/**
 * @brief This should be called once every @timer_period_ms milliseconds.
 */
void process(void);
/**
 * @brief This gets the current debounced state of the switch
 * @retval the debounced state of the switch
 */
SWITCH_STATE getCurrentState(void);
//Public Constants

//Public Variable
private:
//Private Variables
GPIO_TypeDef* gpioPort;
uint16_t gpioPin;
uint16_t timerPeriodMS;
SWITCH_STATE currentState;

//Private Function Prototypes
};

#endif //End Header Guard
