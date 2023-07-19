/*
 * @file rcc.h
 *
 * @data Jul 1, 2023
 * @author Ali Shabana
 */



#ifndef RCC_RCC_H_
#define RCC_RCC_H_

/******************************* Includes *******************************/
#include "memory_map.h"

/*******************************  globals *******************************/


/******************************* Macros *******************************************/

	#define RCC_NO_DIV		0
	#define RCC_DIV2		1
	#define RCC_DIV4		2
	#define RCC_DIV8		3
	#define RCC_DIV16		4
	#define RCC_DIV64		5
	#define RCC_DIV128		6
	#define RCC_DIV256		7
	#define RCC_DIV512		8

/******************************* Types *******************************/
typedef enum{
	RCC_AHB1_GPIOA = 0,	RCC_AHB1_GPIOB = 1,	RCC_AHB1_GPIOC = 2,	RCC_AHB1_GPIOD = 3,	RCC_AHB1_GPIOE = 8,	RCC_AHB1_GPIOH = 7,
	RCC_AHB1_CRC = 12,	RCC_AHB1_BKP_SRAM = 18,	RCC_AHB1_CCM_DATA_RAM = 20,	RCC_AHB1_DMA1 = 21,	RCC_AHB1_DMA2 = 22,
	RCC_AHB1_ETH_MAC = 25,	RCC_AHB1_ETH_MAC_TX = 26,	RCC_AHB1_ETH_MAC_RX = 27,	RCC_AHB1_ETH_MAC_PTP = 28,
	RCC_AHB1_OTGHS = 29,	RCC_AHB1_OTGHS_UPI = 30,
}RCC_AHB1PERIPH_en;

typedef enum{
	RCC_AHB2_DCMI = 0,	RCC_AHB2_CRYP = 4,	RCC_AHB2_HASH = 5,	RCC_AHB2_RNG = 6,	RCC_AHB2_OTGFS = 7
}RCC_AHB2PERIPH_en;

typedef enum{
	RCC_AHB3_FSMC = 0,
}RCC_AHB3PERIPH_en;

typedef enum{
	RCC_APB1_TIM2 = 0,	RCC_APB1_TIM3 = 1,	RCC_APB1_TIM4 = 2,	RCC_APB1_TIM5 = 3,	RCC_APB1_TIM6 = 4,	RCC_APB1_TIM7 = 5,
	RCC_APB1_TIM12 = 6,	RCC_APB1_TIM13 = 7,	RCC_APB1_TIM14 = 8,	RCC_APB1_WWDG = 11,	RCC_APB1_SPI2 = 14,	RCC_APB1_SPI3 = 15,
	RCC_APB1_USART2 = 17,	RCC_APB1_USART3 = 18,	RCC_APB1_USART4 = 19,	RCC_APB1_USART5 = 20,	RCC_APB1_I2C1 = 21,
	RCC_APB1_I2C2 = 22,	RCC_APB1_I2C3 = 23,	RCC_APB1_CAN1 = 25,	RCC_APB1_CAN2 = 26,	RCC_APB1_PWR = 28,	RCC_APB1_DAC = 29
}RCC_APB1PERIPH_en;

typedef enum{
	RCC_APB2_TIM1 = 0,	RCC_APB2_TIM8 = 1,	RCC_APB2_USART1 = 4,	RCC_APB2_USART6 = 5,	RCC_APB2_ADC1 = 8 ,	RCC_APB2_ADC2 = 9,
	RCC_APB2_ADC3 = 10,	RCC_APB2_SDIO = 11,	RCC_APB2_SPI1 = 12,	RCC_APB2_SYSCONFIG = 14,	RCC_APB2_TIM9 = 16,	RCC_APB2_TIM10 = 17
	,	RCC_APB2_TIM11 = 18,
}RCC_APB2PERIPH_en;

typedef enum{
	RCC_PIN0 = 0,
	RCC_PIN1 ,
	RCC_PIN2 ,
	RCC_PIN3 ,
	RCC_PIN4 ,
	RCC_PIN5 ,
	RCC_PIN6 ,
	RCC_PIN7 ,
	RCC_PIN8 ,
	RCC_PIN9 ,
	RCC_PIN10 ,
	RCC_PIN11 ,
	RCC_PIN12 ,
	RCC_PIN13 ,
	RCC_PIN14 ,
	RCC_PIN15 ,
}RCC_Pin_en;


/******************************* Configurations *******************************************/
/*Choose between
 *
 * 	RCC_NO_DIV
	RCC_DIV2
	RCC_DIV4
	RCC_DIV8
	RCC_DIV16
	RCC_DIV64
	RCC_DIV128
	RCC_DIV256
	RCC_DIV512
 *
 * */


#define RCC_AHB_DIV			RCC_NO_DIV
#define RCC_APB1_DIV		RCC_NO_DIV
#define RCC_APB2_DIV		RCC_NO_DIV

/*******************************Functions Prototypes*******************************/

/**
 * @func RCC_EnableAHB1Clock
 * @brief Enabling AHB1 peripherals clock.
 *
 * @param RCC_AHB1PERIPH_en periph[in]		Enum to specify the desired periph
 *
 * @return void
 */
void RCC_EnableAHB1Clock(RCC_AHB1PERIPH_en periph);
/**
 * @func RCC_EnableAHB2Clock
 * @brief Enabling AHB2 peripherals clock.
 *
 * @param RCC_AHB2PERIPH_en periph[in]		Enum to specify the desired periph
 *
 * @return void
 */
void RCC_EnableAHB2Clock(RCC_AHB2PERIPH_en periph);

/**
 * @func RCC_EnableAHB3Clock
 * @brief Enabling AHB3 peripherals clock.
 *
 * @param RCC_AHB3PERIPH_en periph[in]		Enum to specify the desired periph
 *
 * @return void
 */
void RCC_EnableAHB3Clock(RCC_AHB3PERIPH_en periph);

/**
 * @func RCC_EnableAPB1Clock
 * @brief Enabling APB1 peripherals clock.
 *
 * @param RCC_APB1PERIPH_en periph[in]		Enum to specify the desired periph
 *
 * @return void
 */
void RCC_EnableAPB1Clock(RCC_APB1PERIPH_en periph);


/**
 * @func RCC_EnableAPB2Clock
 * @brief Enabling APB1 peripherals clock.
 *
 * @param RCC_APB2PERIPH_en periph[in]		Enum to specify the desired periph
 *
 * @return void
 */
void RCC_EnableAPB2Clock(RCC_APB2PERIPH_en periph);

/**
 * @func RCC_EnableHSI
 * @brief This function Enables/Turns On the HSI clock -> Turning On HSI Osc [16Mhz].
 * @param void
 * @return void
 *
 * - Important Registers:
 * 		# RCC->CSR:
 * 			[♥]	HSION			->	Turn On/Off HSI OSC 				| 0: HSI OSC OFF, 1: HSI OSC ON
 * 			[♥]	HSIRDY			->	Check if the HSI OSC yet stable		| 0: Not Ready,   1: Ready
 * 			[♥]	HSITRIM[5bits]	->	provide an additional user-programmable trimming value that is added to the HSICAL[7:0] bits.
 * 								${I will not use neither it nor the HSICAL[0-7]}
* 			[♥]	HSICAL[8bits]	->	Initialized automatically with Calibration data		${I will not use it}
*
* 		# RCC->CFGR:
* 			[♥]	SW[2bits]		-> Select System's Clock Source	|	00:HSI, 01:HSE, 10:PLL, 11:not allowed
* 			[♥]	SWS[2bits]		-> Indicates which clock system source is selected	{SAME AS ABOVE}
*
* 		# RCC->CIR:
* 			[♥] HSIRDYF			-> 1: if HCLK is stable and HSIRDYDIE is set,  0: else
* 									This bit is cleared by setting HSIRDYC in that register
* 			[♥] HSIRDYIE		->	Enables interrupt if HSI is ready
* 			[♥] HSIRDYC			->	HSI ready interrupt clear
 */
void RCC_EnableHSI();


/**
 * @func RCC_SetAHBPrescaler
 * @brief This function control the division factor of the AHB Clock.
 * @note AHB clock frequency must be at least 25Mhz when Ethernet is used.
 *
 * @param	void
 * @return void
 *
 * - Important Registers:
 * 		# RCC->CFGR:
 * 			[♥]	HPRE			->	AHB prescaler 				| values range [RCC_NO_DIV - RCC_DIV512]

 *
 */
void RCC_SetAHBPrescaler();

/**
 * @func RCC_SetAPB1Prescaler
 * @brief This function control the division factor of the APB1 Clock.
 * @note The software has to set these bits correctly not to exceed 42 MHz on this domain..
 *
 * @param	void
 * @return void
 *
 * - Important Registers:
 * 		# RCC->CFGR:
 * 			[♥]	PPRE1	->	APB1 (Low Speed prescaler) 	| values range [RCC_NO_DIV - RCC_DIV16]
 *
 */
void RCC_SetAPB1Prescaler();


/**
 * @func RCC_SetAPB2Prescaler
 * @brief This function control the division factor of the APB2 Clock.
 * @note The software has to set these bits correctly not to exceed 84 MHz on this domain.
 *
 * @param	void
 * @return void
 *
 * - Important Registers:
 * 		# RCC->CFGR:
 * 			[♥]	PPRE2	->	APB2 (Low Speed prescaler) 	| values range [RCC_NO_DIV - RCC_DIV16]
 *
 */
void RCC_SetAPB2Prescaler();

#endif /* RCC_RCC_H_ */
