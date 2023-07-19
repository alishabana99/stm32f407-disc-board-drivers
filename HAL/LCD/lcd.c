/**
 * @file lcd.c
 * @author Ali Shabana
 * @date Jul 1, 2023
 *
 * @brief source file for LCD module .
 *
 *  *
 * # This LCD Driver is implemented only for 4-bit configuration.
 *
 *
 */
/******************************* Includes *******************************/
#include "lcd.h"
#include <stdlib.h>
#include <stdio.h>


/*******************************  Macros *******************************/

/*5.1 Clear Display*/
#define LCD_CLEAR_DISPLAY		0x01
/*5.2 Return Home*/
#define LCD_RETURN_HOME			0x02

/*5.3 Entry Mode Set*/
	#define LCD_CURSOR_INCREASE		0x06
	#define LCD_CURSOR_DECREASE		0x04
	#define LCD_SHIFT_DISPLAY_ON	0x05
	#define LCD_SHIFT_DISPLAY_OFF	0x04
#define LCD_SHIFT_DISLAY_LEFT	(LCD_CURSOR_INCREASE | LCD_SHIFT_DISPLAY_ON)
#define LCD_SHIFT_DISLAY_RIGHT	(LCD_CURSOR_DECREASE | LCD_SHIFT_DISPLAY_ON)

/*5.4 Display ON/OFF Control*/
#define LCD_DISPLAY_ON			0x08
#define LCD_DISPLAY_OFF			0x0C
#define LCD_CURSOR_DISPLAY_ON	0x0A
#define LCD_CURSOR_DISPLAY_OFF	0x08
#define LCD_CURSOR_BLINK_ON		0x09
#define LCD_CURSOR_BLINK_OFF	0x08

/*5.5 Cursor/Display Shift - Shifts cursor/display without writing*/
#define LCD_SHIFT_CURSOR_LEFT			0x10
#define LCD_SHIFT_CURSOR_RIGHT			0x14
#define LCD_SHIFT_ENTIRE_DISPLAY_LEFT	0x18
#define LCD_SHIFT_ENTIRE_DISPLAY_RIGHT	0x1C

/*5.6 Function Set*/
#define LCD_8_BIT_MODE					0x30
#define	LCD_4_BIT_MODE					0x20
#define LCD_1_LINE						0x20
#define LCD_2_LINES						0x28
#define LCD_5_7_FONT					0x20
#define LCD_5_10_FONT					0x24

/*5.7 Set CG RAM Address*/
/*5.8 Set DD RAM Address*/
/*5.9 Read Busy Flag & Address*/
/*5.10 Write Data to CG or DD RAM*/
/*5.11 Read Data to CG or DD RAM*/




/******************************* Configurations (if any) *******************************/


/******************************* privates *******************************/


/******************************* Functions Implementation *******************************/


/**
 * @func LCD_LatchBits
 * @brief Responsible to latch whatever it receives (commands/data) and writes it on the LCD Registers.
 *
 * @note Static [private function]
 * @param  uint8_t bits
 * @return void
 */
static void LCD_LatchBits(uint8_t bits){


	//RW = 0, when writing
	GPIO_SetPinState(LCD_CONTROL_GPIO, LCD_RW, GPIO_LOW);

	//RW and RS setup time
	LIB_SysTickDelay_us(10);

	/*1st Nibble*/

	//Set the E pulse
	GPIO_SetPinState(LCD_CONTROL_GPIO, LCD_E, GPIO_HIGH);

	//E rising time
	LIB_SysTickDelay_us(10);

	//DATA SETUP
	GPIO_SetPinState(LCD_DATA_GPIO, LCD_D4, GET_BIT(bits,4));
	GPIO_SetPinState(LCD_DATA_GPIO, LCD_D5, GET_BIT(bits,5));
	GPIO_SetPinState(LCD_DATA_GPIO, LCD_D6, GET_BIT(bits,6));
	GPIO_SetPinState(LCD_DATA_GPIO, LCD_D7, GET_BIT(bits,7));

	//Clear the E pulse
	GPIO_SetPinState(LCD_CONTROL_GPIO, LCD_E, GPIO_LOW);

	//Data Hold time and E falling time
	LIB_SysTickDelay_us(30);

	/*2nd Nibble*/
	//Set the E pulse
	GPIO_SetPinState(LCD_CONTROL_GPIO, LCD_E, GPIO_HIGH);

	//E rising time
	LIB_SysTickDelay_us(10);

	//DATA SETUP
	GPIO_SetPinState(LCD_DATA_GPIO, LCD_D4, GET_BIT(bits,0));
	GPIO_SetPinState(LCD_DATA_GPIO, LCD_D5, GET_BIT(bits,1));
	GPIO_SetPinState(LCD_DATA_GPIO, LCD_D6, GET_BIT(bits,2));
	GPIO_SetPinState(LCD_DATA_GPIO, LCD_D7, GET_BIT(bits,3));


	//Clear the E pulse
	GPIO_SetPinState(LCD_CONTROL_GPIO, LCD_E, GPIO_LOW);

	//Data Hold time and E falling time
	LIB_SysTickDelay_us(30);

}

/**
 * @func LCD_SendCommand
 * @brief Send a command to the LCD .
 * @note Static [private function]
 * @param  uint8_t cmd
 * @return void
 */
static void LCD_SendCommand(uint8_t cmd){
	//RS = 0, when working with instruction register
	GPIO_SetPinState(LCD_CONTROL_GPIO, LCD_RS, GPIO_LOW);

	LCD_LatchBits(cmd);

}


/**
 * @func LCD_SendData
 * @brief Send 1 Byte data through data lines .
 *
 * @note Static [private function]
 * @param  uint8_t data
 * @return void
 */
static void LCD_SendData(uint8_t data){

	//RS = 1, when working with data
	GPIO_SetPinState(LCD_CONTROL_GPIO, LCD_RS, GPIO_HIGH);

	LCD_LatchBits(data);
}

/**
 * @func LCD_Init
 * @brief Initializing the LCD ( GPIO data pins, GPIO control pins, mode, font, lines, cursor, display, blinking, ...etc).
 *
 * @param  void
 * @return void
 */
void LCD_Init(){

	/*Configuring related GPIO pins*/
	//DATA PINs
	RCC_EnableAHB1Clock(LCD_DATA_RCC_GPIO);
	GPIO_SetPinMode(LCD_DATA_GPIO, LCD_D4, GPIO_OUTPUT);
	GPIO_SetPinMode(LCD_DATA_GPIO, LCD_D5, GPIO_OUTPUT);
	GPIO_SetPinMode(LCD_DATA_GPIO, LCD_D6, GPIO_OUTPUT);
	GPIO_SetPinMode(LCD_DATA_GPIO, LCD_D7, GPIO_OUTPUT);
	//CONTROL PINs
	RCC_EnableAHB1Clock(LCD_CONTROL_RCC_GPIO);
	GPIO_SetPinMode(LCD_CONTROL_GPIO, LCD_RS, GPIO_OUTPUT);
	GPIO_SetPinMode(LCD_CONTROL_GPIO, LCD_RW, GPIO_OUTPUT);
	GPIO_SetPinMode(LCD_CONTROL_GPIO, LCD_E, GPIO_OUTPUT);

	/*Wait for more than 30ms after Power On*/
	LIB_SysTickDelay_ms(35);

	/***_________ Function Set _________***/
	LCD_SendCommand(0x20);
	LCD_SendCommand(0x20);
	//2 lines  - 5*10 font
	LCD_SendCommand(0x0C);

	/*Wait for more than 39 uS*/
	LIB_SysTickDelay_us(50);

	/***_________ Display ON/OFF Control _________***/
	//Blink Off  - Cursor On  - Display On
	LCD_SendCommand(0x00);
	LCD_SendCommand(0xE0);

	/*Wait for more than 39 uS*/
	LIB_SysTickDelay_us(50);


	/***_________ Display Clear _________***/
	LCD_SendCommand(0x00);
	LCD_SendCommand(0x01);

	/*Wait for more than 1.5 mSecond*/
	LIB_SysTickDelay_ms(5);

	/***_________ Entry Mode Set  _________***/
	LCD_SendCommand(0x00);
	LCD_SendCommand(0x06);

}


/**
 * @func LCD_PrintChar
 * @brief print a character on LCD.
 *
 * @param  uint8_t byte
 * @return void
 */
void LCD_PrintChar(uint8_t byte){


	LCD_SendData(byte);

}

/**
 * @func LCD_PrintString
 * @brief print a string.
 * # The functions invokes LCD_PrintChar() function until it encounters an null terminator '\0'.
 *
 * @param  uint8_t* str
 * @return void
 */
void LCD_PrintString(uint8_t* str){

	uint8_t i = 0;
	while(str[i] != '\0'){
		LCD_SendData(str[i]);
		i++;
	}

}


/**
 * @func LCD_PrintString
 * @brief prints any signed/unsigned number with the range of [-2^31 : 2^31 - 1].
 *
 * @param  int32_t num_32
 * @return void
 */
void LCD_PrintInt32(int32_t num_32){

	uint8_t buffer[20];


	if(num_32 < 0)
	{
		//negative
		num_32 = num_32 * -1 ;
		LCD_PrintString("-");
	}else if(num_32 == 0){
		//do nothing
	}else{
		//do nothing
	}

	itoa(num_32, buffer, 10);
	LCD_PrintString(buffer);

}



/******************************* ISR *******************************/


