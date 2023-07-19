/**
 * @file main.c
 * @author Ali Shabana
 * @date June 30, 2023
 *
 */

#include "rcc.h"
#include "gpio.h"
#include "systick.h"
#include "common_lib.h"
#include "lcd.h"
#include "usart.h"
#include "adc.h"



/*******************************  Macros *******************************/
/*Green LED*/
#define GREEN_LED_PIN						GPIO_PIN12
#define GREEN_LED_RCC_PORT					RCC_AHB1_GPIOD
#define GREEN_LED_GPIO						GPIOD

/*Orange LED*/
#define ORANGE_LED_PIN						GPIO_PIN13
#define ORANGE_LED_RCC_PORT					RCC_AHB1_GPIOD
#define ORANGE_LED_GPIO						GPIOD

/*User Button*/
#define USER_BTN_PIN	GPIO_PIN0
#define USER_BTN_RCC_PORT					RCC_AHB1_GPIOA
#define USER_BTN_GPIO						GPIOA

	uint32_t adc_output = 0;

#include "memory_map.h"

int main(){

	/************** Initialization Zone ******************/
	//RCC CLOCK Init
	RCC_EnableHSI();

//	LCD_Init();
	USART_Init(USART_USART2);

	/*ADC initialization*/
	//ADC
	ADC_Handle_t adc1_handle = {0};
	adc1_handle.instace = ADC1;
	adc1_handle.configs.prescaler = ADC_PCLK_DIV2;
	adc1_handle.configs.resolution = ADC_RES_12_bit;
	adc1_handle.configs.num_of_conversions = 1;
	adc1_handle.configs.scan_mode = ADC_SCAN_MODE_DISABLED;
	adc1_handle.configs.cont = ADC_CONT_MODE_ENABLED;
	adc1_handle.configs.data_alignment = ADC_ALIGN_RIGHT;

	//Channel
	ADC_ChannelConfig_t channel0 = {0};
	channel0.channel_num = ADC_IN0_123;
	channel0.rank = ADC_RANK1;
	channel0.sampling_time = ADC_SAMPT_480CYCLES;

	ADC_ConfigureChannel(&adc1_handle, &channel0);
	ADC_Init(&adc1_handle);



	/************ 1-shot instructions ***********/



	ADC_Start(&adc1_handle);

	while(1){

		adc_output = ADC_Read(&adc1_handle);
		//printf("%d\n\r",adc_output);
	}




}


