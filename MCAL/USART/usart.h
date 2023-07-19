/**
 * @file usart.h
 * @author Ali Shabana
 * @date Jul 8, 2023
 *
 * @brief USART's module header file .
 *
 *
 * ♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣ HOW TO USE ♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣
 * # Which USART Instance ?
 * 		[♥] -> We choose which USART instance to work with during whatever API we're working with by passing
 * 				USART_Peripheral_en of the dedicated instance.
 * 			->USART_Peripheral_en is used as an index of the g_USART_INSTANCES that has the base addresses of
 * 				All USART instances.
 *
 * # HOW to Configure ?
 *		[♥] Each USART instance has a group of configuration parameters [the only implemented ones]
 *			@Configurations section in the header (usart.h) file.
 *		[♥] Each configuration parameter different options are defined @macros section in the header (usart.h) file.
 *
 * # Another Related Configuration ?
 * 		[♥] -> I'm using USART as a main debugging tool, so @common_lib.c uses the a USART instance [depending on the configured]
 * 				as a serial monitor.
 * 			-> You can configured what USART instance to use, from common_lib.h @configuration section
 * 				for USART_DEBUGGING_CHANNEL provided the desired USART_Peripheral_en.
 * 			-> For sure, the desired USART instance has to be initialized before being used as a debugging channel.
 *
 * # Usage Work Flow ?
 * 		1. Configure in usart.h @configuration section using different options in usart.h @macros section
 * 		2. Call USART_Init() providing the meant using USART_Peripheral_en.
 * 		3. Call whatever USART API you want to use.
 *
 * # Adding more Features ?
 * 		[♥] Adding more features means that there're more configurations to be considered
 * 		[♥] New configurations options need to be added for each new configuration parameter in usart.h @macros
 * 		[♥] Then, choose which option will be used for each new configuration parameter in usart.h @configurations
 * 		[♥] Then, each of these new configuration parameters is applied through the initialization function, mainly,
 * 			and other related USART APIs, sequentially.
 */
#ifndef USART_USART_H_
#define USART_USART_H_




/******************************* Includes *******************************/
#include "stdint.h"
#include "bit_math.h"
#include "memory_map.h"
#include "gpio.h"
#include "rcc.h"


/*******************************  Macros *******************************/
/*
 * F_USART Options -Available in the reference manual-
 * You can provide any value out of these options, it will still operate correctly.*/
#define F_UASRT_CLOCK_8MHz				(8000000UL)
#define F_UASRT_CLOCK_12MHz				(12000000UL)
#define F_UASRT_CLOCK_16MHz				(16000000UL)
#define F_UASRT_CLOCK_24MHz				(24000000UL)
#define F_UASRT_CLOCK_30MHz				(30000000UL)
#define F_UASRT_CLOCK_42MHz				(42000000UL)
#define F_UASRT_CLOCK_60MHz				(60000000UL)
#define F_UASRT_CLOCK_84MHz				(84000000UL)
/*Over sample Options*/
#define OVERSAMPLE16		0
#define OVERSAMPLE8			1
/*Baud Rate Options*/
#define BAUDRATE_1200		(1200UL)
#define BAUDRATE_2400		(2400UL)
#define BAUDRATE_9600		(9600UL)
#define BAUDRATE_19200		(19200UL)
#define BAUDRATE_38400		(38400UL)
#define BAUDRATE_57600		(57600UL)
#define BAUDRATE_115200		(115200UL)
#define BAUDRATE_230400		(230400UL)
#define BAUDRATE_460800		(460800UL)
#define BAUDRATE_896000		(896000UL)
#define BAUDRATE_921600		(921600UL)
#define BAUDRATE_1792000	(1792000UL)
#define BAUDRATE_1843200	(1843200UL)
#define BAUDRATE_3584000	(3584000UL)
#define BAUDRATE_3686400	(3686400UL)
#define BAUDRATE_7168000	(7168000UL)
#define BAUDRATE_7372800	(7372800UL)
#define BAUDRATE_2000000	(2000000UL)
#define BAUDRATE_3000000	(3000000UL)
#define BAUDRATE_9000000	(9000000UL)
#define BAUDRATE_10500000	(10500000UL)
/*Word Length Options*/
#define WORDLENGTH_8		0
#define WORDLENGTH_9		1
/*Parity Options*/
#define PARITY_DISABLED		99
#define	PARITY_ODD			1
#define	PARITY_EVEN			0
/*USART MODE options*/
#define TRANSMITTER_MODE	36
#define RECEIVER_MODE		37
#define TRANSCEIVER_MODE	38
/*Number of stop bits options*/
#define STOP_BITS_1			0b00
#define STOP_BITS_0_5		0b01
#define STOP_BITS_2			0b10
#define STOP_BITS_1_5		0b11

/*
  Bit Sampling method
 * (#) Three sample method
 * (#) 1Bit sample method (NF is disabled)*/
#define SAMPLING_METHOD_1BIT	0
#define SAMPLING_METHOD_3BITS	1


/******************************* globals *******************************/


/******************************* Configurations *******************************/

/*USART1*******************************************************************/



/*USART2*******************************************************************/
#define USART2_OVERSAMPLE				OVERSAMPLE16
#define USART2_F_USART					F_UASRT_CLOCK_16MHz
#define USART2_BAUDRATE					BAUDRATE_115200

#define	USART2_WORDLENGTH				WORDLENGTH_9	//including parity bit (if enabled)
#define USART2_PARITY					PARITY_ODD
#define USART2_MODE						TRANSCEIVER_MODE
#define USART2_STOP_BITS				STOP_BITS_1
#define USART2_SAMPLING_METHOD			SAMPLING_METHOD_1BIT

#define	USART2_TX_GPIO					GPIOA
#define	USART2_TX_RCC_GPIO_PORT			RCC_AHB1_GPIOA
#define USART2_TX_PIN					GPIO_PIN2

#define	USART2_RX_GPIO					GPIOA
#define	USART2_RX_RCC_GPIO_PORT			RCC_AHB1_GPIOA
#define USART2_RX_PIN					GPIO_PIN3

/*USART3*******************************************************************/


/*USART4*******************************************************************/


/*USART5*******************************************************************/


/*USART6*******************************************************************/


/******************************* Types *******************************/
typedef enum{
	USART_USART1 = 0,
	USART_USART2,
	USART_USART3,
	USART_USART4,
	USART_USART5,
	USART_USART6,
}USART_Peripheral_en;



/******************************* Functions prototypes *******************************/



/**
 * @func USART_Init
 * @brief Initializes the provided USART peripheral.
 *
 * @param	USART_Peripheral_en usart[IN]	-> specifies which USART peripheral user wants to init
 * @return void
 * *
 */
void USART_Init(USART_Peripheral_en usart);

/**
 * @func USART_SendChar
 * @brief Sends a character.
 *
 * @param	USART_Peripheral_en usart
 * @param	uint8_t msg[IN]	-> the to-be-sent 8-bit message
 *
 * @return void
 * *
 */
void USART_SendChar(USART_Peripheral_en usart, uint8_t msg);

/**
 * @func USART_ReceiveChar
 * @brief receives a character
 *
 * @param	USART_Peripheral_en usart
 * @param	uint8_t* msg [OUT]	-> received message by reference
 *
 * @return void
 *
 */
void USART_ReceiveChar(USART_Peripheral_en usart, uint8_t* msg);


#endif /* USART_USART_H_ */
