/**
 * @file common_lib.h
 * @author Ali Shabana
 * @date Jul 4, 2023
 *
 * @brief .
 */
#ifndef COMMON_LIB_H_
#define COMMON_LIB_H_




/******************************* Includes *******************************/
#include "systick.h"
#include <stdint.h>
#include <stdio.h>
#include "usart.h"

/*******************************  Macros *******************************/


/******************************* globals *******************************/


/******************************* Configurations *******************************/
#define USART_DEBUGGING_CHANNEL	USART_USART2


/******************************* Types *******************************/


/******************************* Functions prototypes *******************************/
/**
 * @func LIB_SysTickDelay_us
 * @brief Causes a delay of the provided number of micro seconds.
 *
 * @attention Maximum allowed delay = 1000 usec
 *
 * @param uint16_t usec [in]	number of microseconds to be delayed
 * @return void .
 */
void LIB_SysTickDelay_us(uint16_t usec);

/**
 * @func LIB_SysTickDelay_ms
 * @brief Causes a delay of the provided number of millie seconds using the LIB_SysTickDelay_us function.
 *
 * @attention Maximum allowed delay = 4000 msec
 *
 * @param uint32_t msec [in]	number of microseconds to be delayed
 * @return void .
 */
void LIB_SysTickDelay_ms(uint32_t msec);


#endif /* COMMON_LIB_H_ */
