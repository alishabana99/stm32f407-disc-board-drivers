/**
 * @file systick.c
 * @author Ali Shabana
 * @date Jul 3, 2023
 *
 * @brief .
 */
/******************************* Includes *******************************/
#include "systick.h"
#include "bit_math.h"

/*******************************  Macros *******************************/


/******************************* privates *******************************/


/******************************* Functions Implementation *******************************/
/**
 * @func SysTick_Init
 * @brief Initializing SysTick Peripheral based on Provided Configuration in the configuration Section.
 * And Enabling the SysTick.
 *
 * @param u32_load_val [in]		uint32_t value to specify the PreLoad and ReLoad values of the Counter.
 * @return void
 */
void SysTick_Init(uint32_t u32_load_val){

	/*Programming Load Value*/
	SysTick->RVR = u32_load_val;

	/*Clear Current SysTick Counter Value*/
	SysTick->CVR = 0;

	/****** Doing Configurations stuff ********/
	/*Select SysTick Clock Source */
#if SysTick_CLOCK_SOURCE == SysTick_AHB
	SET_BIT(SysTick->CSR,SysTick_CSR_CLKSOURCE);
#elif SysTick_CLOCK_SOURCE == SysTick_AHB_Div8
	CLEAR_BIT(SysTick->CSR,SysTick_CSR_CLKSOURCE);
#else
	/*eeeh*/
#endif
	/*Enable/Disable SysTick Interrupt*/
#if SysTick_Interrupt == SysTick_Enbale_INT
	SET_BIT(SysTick->CSR,SysTick_CSR_TICKINT);
#elif SysTick_Interrupt == SysTick_Disable_INT
	CLEAR_BIT(SysTick->CSR,SysTick_CSR_TICKINT);
#else
	/*eeeh*/
#endif

	/*Enable The SysTick*/
	SET_BIT(SysTick->CSR,SysTick_CSR_ENABLE);
}


/**
 * @func SysTick_UpdateReloadValue
 * @brief Updating reload value at runtime.
 *
 * @param u32_load_val [in]		uint32_t value to specify ReLoad value of the Counter.
 * @return void
 */
void SysTick_UpdateReloadValue(uint32_t u32_load_val){

	/*Programming Load Value*/
	SysTick->RVR = u32_load_val;

}


/**
 * @func SysTick_GetCurrentTickValue
 * @brief Return the current SysTick Counter value.
 *	# A write of any value clears the field to 0, and also clears the SYST_CSR_COUNTFLAG bit to 0.
 * @return uint32_t		returns the current value of the SysTick Counter Value.
 */
uint32_t SysTick_GetCurrentTickValue(void){

	uint32_t current_tick = (uint32_t)SysTick->CVR;
	return current_tick;

}


/**
 * @func SysTick_ReachedZero
 * @brief Returns if timer counted to 0 since last time this was read.
 *	# Bit[16] : Returns 1 if timer counted to 0 since last time this was read.
 * @return SysTick_CountFlag_t	returns either SysTick_COUNTING = 0  , SysTick_REACHED_ZERO = 1 .
 */
SysTick_CountFlag_t SysTick_ReachedZero(void){

	SysTick_CountFlag_t	counter_flag_status = SysTick_COUNTING;
	/*Checking if the timer counted to 0, since the last read.*/
	if(GET_BIT(SysTick->CSR,SysTick_CSR_COUNTFLAG)){
		counter_flag_status = SysTick_REACHED_ZERO;
	}else{

	}
	return counter_flag_status;
}




/******************************* ISR *******************************/


