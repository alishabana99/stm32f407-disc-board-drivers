/*
 * @file gpio.h
 * @author Ali Shabana
 * @date June 30, 2023
 *
 * @brief GPIO module header file.
 * This file contains types, global symbols, macros, functions prototypes, and maybe some configurations.
 *
 */

#ifndef GPIO_GPIO_H_
#define GPIO_GPIO_H_

/******************************* Includes, globals *******************************/
#include "memory_map.h"

/******************************* Types *******************************/

/**
 * @enum GPIO_Pin_en
 * @brief Describing GPIO pin numbers
 * @note Validity has to be checked for each port, as not all ports have the same number of pins.
 */
typedef enum{
	GPIO_PIN0 = 0,
	GPIO_PIN1,
	GPIO_PIN2,
	GPIO_PIN3,
	GPIO_PIN4,
	GPIO_PIN5,
	GPIO_PIN6,
	GPIO_PIN7,
	GPIO_PIN8,
	GPIO_PIN9,
	GPIO_PIN10,
	GPIO_PIN11,
	GPIO_PIN12,
	GPIO_PIN13,
	GPIO_PIN14,
	GPIO_PIN15
}GPIO_Pin_en;

/**
 * @enum GPIO_Mode_en
 * @brief Describing GPIO pin numbers
 * @note Validity has to be checked for each port, as not all ports have the same number of pins.
 */
typedef enum{
	GPIO_INPUT		= 0,
	GPIO_OUTPUT 		= 1,
	GPIO_AF	= 2,
	GPIO_ANALOG		= 3,
}GPIO_Mode_en;

/**
 * @enum GPIO_Pin_State_en
 * @brief Describing GPIO pin states
 */
typedef enum{

	GPIO_LOW = 0,
	GPIO_HIGH

}GPIO_Pin_State_en;

/**
 * @enum GPIO_AF_en
 * @brief Specifying GPIO pin's possible alternate functions
 */

typedef enum{
	GPIO_AF0 = 0b0,
	GPIO_AF1 = 0b1,
	GPIO_AF2 = 0b10,
	GPIO_AF3 = 0b11,
	GPIO_AF4 = 0b100,
	GPIO_AF5 = 0b101,
	GPIO_AF6 = 0b110,
	GPIO_AF7 = 0b111,
	GPIO_AF8 = 0b1000,
	GPIO_AF9 = 0b1001,
	GPIO_AF10 = 0b1010,
	GPIO_AF11 = 0b1011,
	GPIO_AF12 = 0b1100,
	GPIO_AF13 = 0b1101,
	GPIO_AF14 = 0b1110,
	GPIO_AF15 = 0b1111,
}GPIO_AF_en;

typedef enum{

	GPIO_PUSH_PULL = 0,
	GPIO_OPEN_DRAIN,

}GPIO_Output_Type_en;

typedef enum{
	GPIO_LOW_SPEED = 0b00,
	GPIO_MEDIUM_SPEED = 0b01,
	GPIO_HIGH_SPEED = 0b10,
	GPIO_VERY_HIGH_SPEED = 0b11,
}GPIO_Output_Speed_en;

typedef enum{
	GPIO_NO_PULL = 0b00,
	GPIO_PULL_UP = 0b01,
	GPIO_PULL_DOWN = 0b10,
}GPIO_Pull_en;
/******************************* Macros *******************************/
#define GPIO_AF_SYS				GPIO_AF0
#define GPIO_AF_TIM1				GPIO_AF1
#define GPIO_AF_TIM2				GPIO_AF1

#define GPIO_AF_TIM3				GPIO_AF2
#define GPIO_AF_TIM4				GPIO_AF2
#define GPIO_AF_TIM5				GPIO_AF2

#define GPIO_AF_TIM8				GPIO_AF3
#define GPIO_AF_TIM9				GPIO_AF3
#define GPIO_AF_TIM10			GPIO_AF3
#define GPIO_AF_TIM11			GPIO_AF3

#define GPIO_AF_I2C1				GPIO_AF4
#define GPIO_AF_I2C2				GPIO_AF4
#define GPIO_AF_I2C3				GPIO_AF4

#define GPIO_AF_SPI1				GPIO_AF5
#define GPIO_AF_SPI2				GPIO_AF5
#define GPIO_AF_I2S2				GPIO_AF5
#define GPIO_AF_I2S2ext			GPIO_AF5

#define GPIO_AF_SPI3				GPIO_AF6
#define GPIO_AF_I2Sext			GPIO_AF6
#define GPIO_AF_I2S3				GPIO_AF6

#define GPIO_AF_USART1			GPIO_AF7
#define GPIO_AF_USART2			GPIO_AF7
#define GPIO_AF_USART3			GPIO_AF7
#define GPIO_AF_I2S3ext			GPIO_AF7

#define GPIO_AF_USART4			GPIO_AF8
#define GPIO_AF_USART5			GPIO_AF8
#define GPIO_AF_USART6			GPIO_AF8

#define GPIO_AF_CAN1				GPIO_AF9
#define GPIO_AF_CAN2				GPIO_AF9
#define GPIO_AF_TIM12			GPIO_AF9
#define GPIO_AF_TIM13			GPIO_AF9
#define GPIO_AF_TIM14			GPIO_AF9

#define GPIO_AF_OTG_FS10			GPIO_AF10
#define GPIO_AF_OTG_HS			GPIO_AF10

#define GPIO_AF_ETH				GPIO_AF11

#define GPIO_AF_FSMC				GPIO_AF12
#define GPIO_AF_SDIO				GPIO_AF12
#define GPIO_AF_OTG_FS12			GPIO_AF12

#define GPIO_AF_DCMI				GPIO_AF13



/*******************************Functions Prototypes*******************************/

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
void GPIO_SetPinPull(GPIO_t* port, GPIO_Pin_en pin, GPIO_Pull_en pull);


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
void GPIO_SetPinOutputSpeed(GPIO_t* port, GPIO_Pin_en pin, GPIO_Output_Speed_en ospeed);
/**
 * @func GPIO_SetPinOutputType
 * @brief Setting pin Output type | GPIO_PUSH_PULL ,   GPIO_OPEN_DRAIN.
 *
 * @param GPIO_t* port[in]			Pointer to the Specified the targeted port
 * @param GPIO_Pin_en pin[in]		Specifies the targeted pin
 * @param GPIO_Output_Type_en ot[in]			Specifies the desired Output type
 *
 * @return void
 */
void GPIO_SetPinOutputType(GPIO_t* port, GPIO_Pin_en pin, GPIO_Output_Type_en ot);

/**
 * @func GPIO_SetPinAF
 * @brief Setting pin alternate function | GPIO_AF0 : GPIO_AF1.
 *
 * @param GPIO_t* port[in]			Pointer to the Specified the targeted port
 * @param GPIO_Pin_en pin[in]		Specifies the targeted pin
 * @param GPIO_AF_en[in]			Specifies the desired AF
 *
 * @return void
 */
void GPIO_SetPinAF(GPIO_t* port, GPIO_Pin_en pin, GPIO_AF_en af);

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
void GPIO_SetPinMode(GPIO_t* port, GPIO_Pin_en pin, GPIO_Mode_en mode);


/**
 * @func GPIO_SetPinState
 * @brief Setting the state of the pin: 0 GPIO_LOW - 1 GPIO_HIGH.
 *
 * @param GPIO_t* port[in]				Pointer to the Specified the targeted port
 * @param GPIO_Pin_en pin[in]			Specifies the targeted pin
 * @param GPIO_Pin_State_en state[in]	Specifies the desired state
 *
 * @return void
 */
void GPIO_SetPinState(GPIO_t* port, GPIO_Pin_en pin, GPIO_Pin_State_en state);

/**
 * @func GPIO_GetPinState
 * @brief Getting the state of the specified pin.
 *
 * @param GPIO_t* port[in]				Pointer to the Specified the targeted port
 * @param GPIO_Pin_en pin[in]			Specifies the targeted pin
 *
 * @return GPIO_Pin_State_en
 */
GPIO_Pin_State_en GPIO_GetPinState(GPIO_t* port, GPIO_Pin_en pin);







#endif /* GPIO_GPIO_H_ */
