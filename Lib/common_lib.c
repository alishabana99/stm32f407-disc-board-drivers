/**
 * @file common_lib.c
 * @author Ali Shabana
 * @date Jul 4, 2023
 *
 * @brief .
 */
/******************************* Includes *******************************/
#include "common_lib.h"

/*******************************  Macros *******************************/


/******************************* Configurations (if any) *******************************/


/******************************* privates *******************************/


/******************************* Functions Implementation *******************************/
/*
 * @func __io_putchar
 *
 * @brief 	related to re-targeting printf() function
 *
 * */
int __io_putchar(int ch){
	USART_SendChar(USART_DEBUGGING_CHANNEL, ch);
	return ch;
}


#ifndef SysTickCLK
#warning You Have not provided SysTick CLK Freq SysTickCLK macro Which is needed for the delay function
#define SysTickCLK	(16000000UL)	//fallback
#endif


/**
 * @func LIB_SysTickDelay_us
 * @brief Causes a delay of the provided number of micro seconds.
 *
 * @attention Maximum allowed delay = 1000 usec
 *
 * @param uint16_t usec [in]	number of microseconds to be delayed
 * @return void .
 */

void LIB_SysTickDelay_us(uint16_t usec){

	uint32_t tick_time_nano = (1000000000UL) / SysTickCLK;

	uint32_t ticks = (usec*1000)/tick_time_nano;

	SysTick_Init(ticks-1);

	while(SysTick_ReachedZero() == SysTick_COUNTING);
}

/**
 * @func LIB_SysTickDelay_ms
 * @brief Causes a delay of the provided number of millie seconds using the LIB_SysTickDelay_us function.
 *
 * @attention Maximum allowed delay = 4000 msec
 *
 * @param uint32_t msec [in]	number of microseconds to be delayed
 * @return void .
 */
void LIB_SysTickDelay_ms(uint32_t msec){

	/*for each msec we delay 1000 micro seconds */
	for(;msec>0;msec--){
		LIB_SysTickDelay_us(1000);
	}
}

/******************************* ISR *******************************/


