/**
 * @file systick.h
 * @author Ali Shabana
 * @date Jul 3, 2023
 *
 * @brief .
 */
#ifndef SYSTICK_SYSTICK_H_
#define SYSTICK_SYSTICK_H_




/******************************* Includes *******************************/
#include "memory_map.h"

/*******************************  Macros *******************************/


/******************************* globals *******************************/


/******************************* Configurations *******************************/
/**
 * @brief Configuring if SysTick's Interrupt is Enabled or Disabled.
 *
 * #Choose Between
 * 		- SysTick_Enbale_INT
 * 		- SysTick_Disable_INT
 */
#define SysTick_Enbale_INT	1
#define SysTick_Disable_INT	0
#define SysTick_Interrupt	SysTick_Disable_INT

/**
 * @brief Configuring if SysTick's Clock Source
 * 	0 -> External Clock Source	[Which is (HCLK/8)     AHB Clock / 8]
 * 	1 -> Processor Clock Source	[Which is (HCLK)       AHB Clock
 *
 * #Choose Between
 * 		- SysTick_AHB_Div8
 * 		- SysTick_AHB
 */
#define SysTick_AHB_Div8		0
#define SysTick_AHB				1
#define SysTick_CLOCK_SOURCE	SysTick_AHB



/******************************* Types *******************************/
typedef enum{
	SysTick_COUNTING = 0,
	SysTick_REACHED_ZERO = 1,
}SysTick_CountFlag_t;

/******************************* Functions prototypes *******************************/
/**
 * @func SysTick_Init
 * @brief Initializing SysTick Peripheral based on Provided Configuration in the configuration Section.
 *
 * @param u32_load_val [in]		uint32_t value to specify the PreLoad and ReLoad values of the Counter.
 * @return void
 */
void SysTick_Init(uint32_t u32_load_val);



/**
 * @func SysTick_UpdateReloadValue
 * @brief Updating reload value at runtime.
 *
 * @param u32_load_val [in]		uint32_t value to specify ReLoad value of the Counter.
 * @return void
 */
void SysTick_UpdateReloadValue(uint32_t u32_load_val);


/**
 * @func SysTick_GetCurrentTickValue
 * @brief Return the current SysTick Counter value.
 *	# A write of any value clears the field to 0, and also clears the SYST_CSR_COUNTFLAG bit to 0.
 * @return uint32_t		returns the current value of the SysTick Counter Value.
 */
uint32_t SysTick_GetCurrentTickValue(void);


/**
 * @func SysTick_ReachedZero
 * @brief Returns if timer counted to 0 since last time this was read.
 *	# Bit[16] : Returns 1 if timer counted to 0 since last time this was read.
 * @return SysTick_CountFlag_t	returns either SysTick_COUNTING = 0  , SysTick_REACHED_ZERO = 1 .
 */
SysTick_CountFlag_t SysTick_ReachedZero(void);






#endif /* SYSTICK_SYSTICK_H_ */
