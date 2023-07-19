/*
 * @file rcc.c
 *
 * @data Jul 1, 2023
 * @author Ali Shabana
 */


/******************************* Includes, Macros, globals *******************************/
#include "rcc.h"
#include "bit_math.h"

/*******************************Functions Implementation*******************************/

/**
 * @func RCC_EnableAHB1Clock
 * @brief Enabling AHB1 peripherals clock.
 *
 * @param RCC_AHB1PERIPH_en periph[in]		Enum to specify the desired periph
 *
 * @return void
 */
void RCC_EnableAHB1Clock(RCC_AHB1PERIPH_en periph){
		SET_BIT(RCC->AHB1ENR,periph);
}

void RCC_EnableAHB2Clock(RCC_AHB2PERIPH_en periph){
	SET_BIT(RCC->AHB2ENR,periph);
}


/**
 * @func RCC_EnableAHB3Clock
 * @brief Enabling AHB3 peripherals clock.
 *
 * @param RCC_AHB3PERIPH_en periph[in]		Enum to specify the desired periph
 *
 * @return void
 */
void RCC_EnableAHB3Clock(RCC_AHB3PERIPH_en periph){
	SET_BIT(RCC->AHB3ENR, periph);
}

/**
 * @func RCC_EnableAPB1Clock
 * @brief Enabling APB1 peripherals clock.
 *
 * @param RCC_APB1PERIPH_en periph[in]		Enum to specify the desired periph
 *
 * @return void
 */
void RCC_EnableAPB1Clock(RCC_APB1PERIPH_en periph){
	SET_BIT(RCC->APB1ENR, periph);
}


/**
 * @func RCC_EnableAPB2Clock
 * @brief Enabling APB1 peripherals clock.
 *
 * @param RCC_APB2PERIPH_en periph[in]		Enum to specify the desired periph
 *
 * @return void
 */
void RCC_EnableAPB2Clock(RCC_APB2PERIPH_en periph){
	SET_BIT(RCC->APB2ENR, periph);
}


/**
 * @func RCC_EnableHSI
 * @brief This function Enables/Turns On the HSI clock -> Turning On HSI Osc [16Mhz].
 * @param void
 * @return void
 *
 * - Important Registers:
 * 		# RCC->CR:
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
void RCC_EnableHSI(){

	/*Select HSI as the System's Clock Source    SW0: 0    SW1: 0*/
	CLEAR_BIT(RCC->CFGR, RCC_CFGR_SW0);
	CLEAR_BIT(RCC->CFGR, RCC_CFGR_SW1);

	/*Turning On HSI Osc [16Mhz]*/
	SET_BIT(RCC->CR, RCC_CR_HSION);

	/*Configuring other buses prescalers
	 *[they are configured based on pre-build configurations provided at rcc.h]*/
	RCC_SetAHBPrescaler();
	RCC_SetAPB1Prescaler();
	RCC_SetAPB2Prescaler();

	/*Polling and waiting for HSI Clock to be ready*/
	while(GET_BIT(RCC->CR, RCC_CR_HSIRDY) != 1);
}



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
void RCC_SetAHBPrescaler(){

	/*Clearing AHB prescaler bits*/
	RCC->CFGR &= 0xFFFFFF0F;

#if RCC_AHB_DIV == RCC_NO_DIV
	RCC->CFGR |= ( 0b000 << RCC_CFGR_HPRE);
#elif RCC_AHB_DIV == RCC_DIV2
	RCC->CFGR |= (0b1000 << RCC_CFGR_HPRE);
#elif RCC_AHB_DIV == RCC_DIV4
	RCC->CFGR |= (0b1001 << RCC_CFGR_HPRE);
#elif RCC_AHB_DIV == RCC_DIV8
	RCC->CFGR |= (0b1010 << RCC_CFGR_HPRE);
#elif RCC_AHB_DIV == RCC_DIV16
	RCC->CFGR |= (0b1011 << RCC_CFGR_HPRE);
#elif RCC_AHB_DIV == RCC_DIV64
	RCC->CFGR |= (0b1100 << RCC_CFGR_HPRE);
#elif RCC_AHB_DIV == RCC_DIV128
	RCC->CFGR |= (0b1101 << RCC_CFGR_HPRE);
#elif RCC_AHB_DIV == RCC_DIV256
	RCC->CFGR |= (0b1110 << RCC_CFGR_HPRE);
#elif RCC_AHB_DIV == RCC_DIV512
	RCC->CFGR |= (0b1111 << RCC_CFGR_HPRE);
#endif


}

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
void RCC_SetAPB1Prescaler(){

	/*Clearing APB1 prescaler bits*/
	RCC->CFGR &= 0xFFFFE3FF;

#if RCC_APB1_DIV == RCC_NO_DIV
	RCC->CFGR |= ( 0b000 << RCC_CFGR_HPRE);
#elif RCC_AHB_DIV == RCC_DIV2
	RCC->CFGR |= (0b100 << RCC_CFGR_HPRE);
#elif RCC_AHB_DIV == RCC_DIV4
	RCC->CFGR |= (0b101 << RCC_CFGR_HPRE);
#elif RCC_AHB_DIV == RCC_DIV8
	RCC->CFGR |= (0b110 << RCC_CFGR_HPRE);
#elif RCC_AHB_DIV == RCC_DIV16
	RCC->CFGR |= (0b111 << RCC_CFGR_HPRE);

#endif

}

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
void RCC_SetAPB2Prescaler(){
	/*Clearing APB2 prescaler bits*/
	RCC->CFGR &= 0xFFFF1FFF;

#if RCC_APB2_DIV == RCC_NO_DIV
	RCC->CFGR |= ( 0b000 << RCC_CFGR_HPRE);
#elif RCC_AHB_DIV == RCC_DIV2
	RCC->CFGR |= (0b100 << RCC_CFGR_HPRE);
#elif RCC_AHB_DIV == RCC_DIV4
	RCC->CFGR |= (0b101 << RCC_CFGR_HPRE);
#elif RCC_AHB_DIV == RCC_DIV8
	RCC->CFGR |= (0b110 << RCC_CFGR_HPRE);
#elif RCC_AHB_DIV == RCC_DIV16
	RCC->CFGR |= (0b111 << RCC_CFGR_HPRE);

#endif

}

