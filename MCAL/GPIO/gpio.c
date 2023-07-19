/*
 * @file gpio.c
 * @author Ali Shabana
 * @date June 30, 2023
 *
 * @brief GPIO module source file.
 * This file contains functions definitions, private symbols and maybe some ISRs.
 *
 */


/******************** Includes and Macros ********************/
#include "gpio.h"
#include "bit_math.h"

/******************** Functions Implementation ********************/



/**
 * @func GPIO_SetPinPull
 * @brief Setting pin's pull functionality | .	GPIO_NO_PULL,  GPIO_PULL_UP, GPIO_PULL_DOWN,
 *
 *
 * @param GPIO_t* port[in]			Pointer to the Specified the targeted port
 * @param GPIO_Pin_en pin[in]		Specifies the targeted pin
 * @param GPIO_Pull_en pull[in]			Specifies the pull functionality of the pin
 *
 * @return void
 */
void GPIO_SetPinPull(GPIO_t* port, GPIO_Pin_en pin, GPIO_Pull_en pull){

	port->PUPDR |= (pull << (pin*2));

}


/**
 * @func GPIO_SetPinOutputSpeed
 * @brief Setting pin's output speed | .	GPIO_LOW_SPEED ,GPIO_MEDIUM_SPEED,	GPIO_HIGH_SPEED,	GPIO_VERY_HIGH_SPEED,
 *
 *
 * @param GPIO_t* port[in]			Pointer to the Specified the targeted port
 * @param GPIO_Pin_en pin[in]		Specifies the targeted pin
 * @param GPIO_Output_Speed_en ospeed[in]			Specifies the desired Output speed
 *
 * @return void
 */
void GPIO_SetPinOutputSpeed(GPIO_t* port, GPIO_Pin_en pin, GPIO_Output_Speed_en ospeed){

	port->OSPEEDR |= (ospeed << (pin*2));

}

/**
 * @func GPIO_SetPinAF
 * @brief Setting the Mode: 00 Input - 01 Output - 10 Alternate function - 11 Analog Mode.
 *
 * @param GPIO_t* port[in]						Pointer to the Specified the targeted port
 * @param GPIO_Pin_en pin[in]					Specifies the targeted pin
 * @param GPIO_Output_Type_en ot[in]			Specifies the desired Output type
 *
 * @return void
 */
void GPIO_SetPinOutputType(GPIO_t* port, GPIO_Pin_en pin, GPIO_Output_Type_en ot){

	CHANGE_BIT_VAL(port->OTYPER,pin,ot);
}


/**
 * @func GPIO_SetPinAF
 * @brief Setting the Mode: 00 Input - 01 Output - 10 Alternate function - 11 Analog Mode.
 *
 * @param GPIO_t* port[in]			Pointer to the Specified the targeted port
 * @param GPIO_Pin_en pin[in]		Specifies the targeted pin
 * @param GPIO_AF_en[in]			Specifies the desired AF
 *
 * @return void
 */
void GPIO_SetPinAF(GPIO_t* port, GPIO_Pin_en pin, GPIO_AF_en af){
	if(pin >= GPIO_PIN0 && pin <= GPIO_PIN7){
		//Will be using GPIOx->AFRL
		port->AFRL |= (af<<(pin*4)); //each pin[0-7]  correspondent 4 bits

	}else if(pin >= GPIO_PIN8 && pin <= GPIO_PIN15){
		//Will be using GPIOx->AFRH
		port->AFRH |= (af<<((pin-8)*4)); //each pin[8-15]  correspondent 4 bits

	}else{
		//OUT OF RANGE
	}
}
/**
 * @func GPIO_SetPinMode
 * @brief Setting the Mode: 00 Input - 01 Output - 10 Alternate function - 11 Analog Mode.
 *
 * @param GPIO_t* port[in]			Pointer to the Specified the targeted port
 * @param GPIO_Pin_en pin[in]		Specifies the targeted pin
 * @param GPIO_Mode_en mode[in]		Specifies the desired mode
 *
 * @return void
 */
void GPIO_SetPinMode(GPIO_t* port, GPIO_Pin_en pin, GPIO_Mode_en mode){

	/*Setting the mode bit by bit - As each pin has 2 correspondent bits*/
	CHANGE_BIT_VAL(port->MODER,pin*2,GET_BIT(mode,0));
	CHANGE_BIT_VAL(port->MODER,(pin*2)+1,GET_BIT(mode,1));

}


/**
 * @func GPIO_SetPinState
 * @brief Setting the state of the pin: 0 LOW - 1 HIGH.
 *
 * @param GPIO_t* port[in]				Pointer to the Specified the targeted port
 * @param GPIO_Pin_en pin[in]			Specifies the targeted pin
 * @param GPIO_Pin_State_en state[in]	Specifies the desired state
 *
 * @return void
 */
void GPIO_SetPinState(GPIO_t* port, GPIO_Pin_en pin, GPIO_Pin_State_en state){
/*
 * - Using BSRR to make it Atomic Access
 * */
	switch(state){
	case GPIO_LOW:
		SET_BIT(port->BSRR,pin<<16); // <<16 to set the correspondent bit of reset part of the register
		break;
	case GPIO_HIGH:
		SET_BIT(port->BSRR,pin);
		break;
	default:
		//Nothing
		break;
	}

}

/**
 * @func GPIO_GetPinState
 * @brief Getting the state of the specified pin.
 *
 * @param GPIO_t* port[in]				Pointer to the Specified the targeted port
 * @param GPIO_Pin_en pin[in]			Specifies the targeted pin
 *
 * @return GPIO_Pin_State_en
 */
GPIO_Pin_State_en GPIO_GetPinState(GPIO_t* port, GPIO_Pin_en pin){

	return GET_BIT(port->IDR,pin);

}


