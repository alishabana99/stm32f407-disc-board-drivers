/**
 * @file lcd.h
 * @author Ali Shabana
 * @date Jul 1, 2023
 *
 * @brief header file for LCD module.
 *
 * This module implements LCD module in 4-bit mode
 */
#ifndef LCD_LCD_H_
#define LCD_LCD_H_



/******************************* Includes, Macros, globals *******************************/
#include "gpio.h"
#include "rcc.h"
#include "common_lib.h"
#include "bit_math.h"

/******************************* Configurations *******************************/
/**
 * @defgroup LCD connection configurations (GPIO pins used for data/control & GPIO port used).
 *
 * # This LCD Driver is implemented only for 4-bit configuration.
 *
 */
#define LCD_D4	GPIO_PIN4
#define LCD_D5	GPIO_PIN5
#define LCD_D6	GPIO_PIN6
#define LCD_D7	GPIO_PIN7
#define LCD_DATA_GPIO		GPIOA
#define LCD_DATA_RCC_GPIO		RCC_AHB1_GPIOA

#define LCD_RS	GPIO_PIN8
#define LCD_RW	GPIO_PIN9
#define LCD_E	GPIO_PIN10
#define LCD_CONTROL_GPIO	GPIOA
#define LCD_CONTROL_RCC_GPIO	RCC_AHB1_GPIOA


/******************************* Types *******************************/


/******************************* Functions prototypes *******************************/

/**
 * @func LCD_Init
 * @brief Initializing the LCD ( GPIO data pins, GPIO control pins, mode, font, lines, cursor, display, blinking, ...etc).
 *
 * @param  void
 * @return void
 */
void LCD_Init();

/**
 * @func LCD_PrintChar
 * @brief print a character on LCD.
 *
 * @param  uint8_t byte
 * @return void
 */
void LCD_PrintChar(uint8_t byte);


/**
 * @func LCD_PrintString
 * @brief print a string.
 * # The functions invokes LCD_PrintChar() function until it encounters an null terminator '\0'.
 *
 * @param  uint8_t* str
 * @return void
 */
void LCD_PrintString(uint8_t* str);


/**
 * @func LCD_PrintString
 * @brief prints any signed/unsigned number with the range of [-2^31 : 2^31 - 1].
 *
 * @param  int32_t num_32
 * @return void
 */
void LCD_PrintInt32(int32_t num_32);

#endif /* LCD_LCD_H_ */
