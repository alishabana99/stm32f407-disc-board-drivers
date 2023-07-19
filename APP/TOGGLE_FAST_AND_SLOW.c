/**
 * @file TOGGLE_FAST_AND_SLOW.c
 * @author Ali Shabana
 * @date Jul 3, 2023
 *
 * @brief .
 */
/******************************* Includes *******************************/
#include "rcc.h"
#include "gpio.h"

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



/******************************* Configurations (if any) *******************************/
/*Choose Between {ORANGE, GREEN, BOTH}*/
#define ORANGE	1
#define GREEN	2
#define BOTH	3
#define LED BOTH

/******************************* privates *******************************/


/******************************* Functions Implementation *******************************/
void APP_ToggleFastAndSlow(){


	/*1. Enable Clock for Green/Orange LED and User Button's GPIO clocks*/
	RCC_EnableAHB1Clock(GREEN_LED_RCC_PORT);
	RCC_EnableAHB1Clock(ORANGE_LED_RCC_PORT);

	RCC_EnableAHB1Clock(USER_BTN_RCC_PORT);

	/*2. Configure Green/Orange LED as Output and User Button's Pin as input*/
	GPIO_SetPinMode(GREEN_LED_GPIO, GREEN_LED_PIN, GPIO_OUTPUT);
	GPIO_SetPinMode(ORANGE_LED_GPIO, ORANGE_LED_PIN, GPIO_OUTPUT);

	GPIO_SetPinMode(USER_BTN_GPIO, USER_BTN_PIN, GPIO_INPUT);


	/*3. Set Green Led as HIGH initially*/
	GPIO_SetPinState(GREEN_LED_GPIO, GREEN_LED_PIN, GPIO_HIGH);
	GPIO_SetPinState(ORANGE_LED_GPIO, ORANGE_LED_PIN, GPIO_HIGH);


	uint32_t Shortdelay =	100000;
	uint32_t Longdelay =	1000000;

	while(1){

		/*4.Change LED's Toggling Speed According to Button State*/
		if(GPIO_GetPinState(USER_BTN_GPIO, USER_BTN_PIN) == GPIO_HIGH){
#if LED == GREEN
			GPIO_SetPinState(GREEN_LED_GPIO, GREEN_LED_PIN, GPIO_HIGH);
#elif LED == ORANGE
			GPIO_SetPinState(ORANGE_LED_GPIO, ORANGE_LED_PIN, GPIO_HIGH);
#else
			GPIO_SetPinState(GREEN_LED_GPIO, GREEN_LED_PIN, GPIO_HIGH);
			GPIO_SetPinState(ORANGE_LED_GPIO, ORANGE_LED_PIN, GPIO_HIGH);
#endif
			for(volatile int i = 0; i<Shortdelay; i++); //Additional delay

#if LED == GREEN
			GPIO_SetPinState(GREEN_LED_GPIO, GREEN_LED_PIN, GPIO_LOW);
#elif LED == ORANGE
			GPIO_SetPinState(ORANGE_LED_GPIO, ORANGE_LED_PIN, GPIO_LOW);
#else
			GPIO_SetPinState(GREEN_LED_GPIO, GREEN_LED_PIN, GPIO_LOW);
			GPIO_SetPinState(ORANGE_LED_GPIO, ORANGE_LED_PIN, GPIO_LOW);
#endif
			for(volatile int i = 0; i<Shortdelay; i++); //Additional delay
		}else{

#if LED == GREEN
			GPIO_SetPinState(GREEN_LED_GPIO, GREEN_LED_PIN, GPIO_HIGH);
#elif LED == ORANGE
			GPIO_SetPinState(ORANGE_LED_GPIO, ORANGE_LED_PIN, GPIO_HIGH);
#else
			GPIO_SetPinState(GREEN_LED_GPIO, GREEN_LED_PIN, GPIO_HIGH);
			GPIO_SetPinState(ORANGE_LED_GPIO, ORANGE_LED_PIN, GPIO_HIGH);
#endif
			for(volatile int i = 0; i<Longdelay; i++); //Additional delay

#if LED == GREEN
			GPIO_SetPinState(GREEN_LED_GPIO, GREEN_LED_PIN, GPIO_LOW);
#elif LED == ORANGE
			GPIO_SetPinState(ORANGE_LED_GPIO, ORANGE_LED_PIN, GPIO_LOW);
#else
			GPIO_SetPinState(GREEN_LED_GPIO, GREEN_LED_PIN, GPIO_LOW);
			GPIO_SetPinState(ORANGE_LED_GPIO, ORANGE_LED_PIN, GPIO_LOW);
#endif
			for(volatile int i = 0; i<Longdelay; i++); //Additional delay

		}


	}

}

/******************************* ISR *******************************/


