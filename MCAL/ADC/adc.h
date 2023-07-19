/**
 * @file adc.h
 * @author Ali Shabana
 * @date Jul 14, 2023
 *
 * @brief ADC peripherals' drivers header file.
 *
 *  *
 * ♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣ HOW TO USE ♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣
 * # Which ADC Instance ?
 * 		[♥] -> We choose which ADC instance to work with during whatever API we're working with by passing
 * 				ADC_Handle_t* adc which has {Instance} member which is configured with the base address
 * 				of the dedicated instance.
 * 			-> using {Instance}, you can use all ADC's instance registers.
 *
 * # HOW to Configure ?
 *		[♥] Each ADC configuration parameter has either an enum or defgroup(@macros) that provide various configuration options.
 *		[♥] You make a variable of the type {ADC_Handle_t} through which you'll configure your desired ADC instance and other
 *			configuration parameters [implemented till now].
 *		[+♥] Then you make a variable of the type {ADC_ChannelConfig_t} for each channel you'll be using.
 *		[+♥] ⚠Make sure you are invoking ADC_ConfigureChannel() before ADC_Init()
 *			 *
 * # Usage Work Flow ?
 * 		1. Make a {ADC_Handle_t} variable and initialize its members with the desired configurations.
 * 		2. Make a {ADC_ChannelConfig_t} variable for each to-be-used channel ,and initialize them with the desired configurations.
 * 		3. Call ADC_ConfigureChannel() for each channel.
 * 		4. Then, call ADC_Init()
 * 		5. Use ADC_Start() to start conversion
 * 		6. Use ADC_Read() to read the output value
 *
 * # Adding more Features ?
 * 		[♥] Adding more features means that there're more configurations to be considered.
 * 		[♥] New configurations options need to be added for each new configuration parameter in adc.h @macros
 * 		[♥] Then, new configuration parameters will be added in {ADC_Config_t} if they're ADC-related,
 * 			and added in {ADC_ChannelConfig_t} if they're channel-related.
 * 		[♥] Then, Considering these new configuration parameters when applying step#1 and step#2 in usage work flow,
 * 			and when using any related API sequentially.
 *
 */
#ifndef ADC_ADC_H_
#define ADC_ADC_H_




/******************************* Includes *******************************/
#include "common_lib.h"
#include "bit_math.h"
#include "memory_map.h"
#include "stdint.h"

/******************************* Types *******************************/
typedef enum{
	ADC_PIN0 = 0,
	ADC_PIN1,
	ADC_PIN2,
	ADC_PIN3,
	ADC_PIN4,
	ADC_PIN5,
	ADC_PIN6,
	ADC_PIN7,
	ADC_PIN8,
	ADC_PIN9,
	ADC_PIN10,
	ADC_PIN11,
	ADC_PIN12,
	ADC_PIN13,
	ADC_PIN14,
	ADC_PIN15
}ADC_Pin_en;




/**
 * @enum ADC_Config_t
 * @brief Grouping different possible configuration for the ADC [implemented till now]
 * @note This structure includes only the implemented/considered configurations
 * any further considerations/configurations, will be added ISA.
 */
typedef struct{

	uint8_t prescaler;	/* Selects ADC prescaler out of the provided options @defgroup ADC_Clock_Prescaler_Options section  */
	uint8_t resolution;	/*Selects ADC # of resolution bits out of the provided options @defgroup ADC_Resolution_Options section */
	uint8_t data_alignment; /*Selects data alignment left or right out of the provided options @defgroup ADC_Data_Alignment_Options section */
	uint8_t scan_mode;	/*disables or enables SCAN conversion mode out of the provided options @defgroup ADC_SCAN_MODE_Options section*/
	uint8_t cont;	/*Choose between single or multiple conversion mode out of the provided options @defgroup ADC_CONT_MODE_Options section*/
	uint8_t num_of_conversions; /*number of chosen regular conversion channels, number between 0b0000(0) and 0b1111(15)*/

}ADC_Config_t;

/**
 * @enum ADC_ChannelConfig_t
 * @brief Grouping different possible configuration for an ADC's Channel [implemented till now]
 *
 * @note This structure includes only the implemented/considered configurations
 * 		 any further considerations/configurations, will be added ISA.
 *
 */
typedef struct{
	uint8_t channel_num; /*choose out of options @defgroup ADC_Channels_Options*/
	uint8_t rank; /*choose out of options @defgroup ADC_RANKS_Options */
	uint8_t sampling_time; /*choose out of options @defgroup ADC_SamplingTime_Options*/
}ADC_ChannelConfig_t;


/**
 * @enum ADC_ChannelConfig_t
 * @brief Grouping different possible configuration for an ADC's Channel [implemented till now]
 * @note This structure includes only the implemented/considered configurations
 * any further considerations/configurations, will be added ISA.
 */
typedef struct{
	ADC_t* instace;
	ADC_Config_t configs;
}ADC_Handle_t;

/*******************************  Macros *******************************/
/** @defgroup ADC_Clock_Prescaler_Options
  *
  */
#define ADC_PCLK_DIV2		(0)
#define ADC_PCLK_DIV4		(1)
#define ADC_PCLK_DIV6		(2)
#define ADC_PCLK_DIV8		(3)

/** @defgroup ADC_Resolution_Options
  *
  */
#define ADC_RES_12_bit		(0)
#define ADC_RES_10_bit		(1)
#define ADC_RES_8_bit		(2)
#define ADC_RES_6_bit		(3)

/** @defgroup ADC_Data_Alignment_Options
  *
  */
#define ADC_ALIGN_RIGHT		(0)
#define ADC_ALIGN_LEFT		(1)

/** @defgroup ADC_SCAN_MODE_Options
  *
  */
#define ADC_SCAN_MODE_DISABLED		(0)
#define ADC_SCAN_MODE_ENABLED		(1)

/** @defgroup ADC_CONT_MODE_Options
  *
  */
#define ADC_CONT_MODE_DISABLED		(0)
#define ADC_CONT_MODE_ENABLED		(1)

/** @defgroup ADC_Channels_Options
  *
  */
/*PORTA*/
#define ADC_IN0_123		(0)//ADC_PIN0
#define ADC_IN1_123			(1)//ADC_PIN1
#define ADC_IN2_123			(2)//ADC_PIN2
#define ADC_IN3_123			(3)//ADC_PIN3
#define ADC_IN4_12			(4)//ADC_PIN4
#define ADC_IN5_12			(5)//ADC_PIN5
#define ADC_IN6_12			(6)//ADC_PIN6
#define ADC_IN7_12			(7)//ADC_PIN7
/*PORTB*/
#define ADC_IN8_12			(8)//ADC_PIN0
#define ADC_IN9_12			(9)//ADC_PIN1
/*PORTC*/
#define ADC_IN10_123		(10)//ADC_PIN0
#define ADC_IN11_123		(11)//ADC_PIN1
#define ADC_IN12_123		(12)//ADC_PIN2
#define ADC_IN13_123		(13)//ADC_PIN3
#define ADC_IN14_12			(14)//ADC_PIN4
#define ADC_IN15_12			(15)//ADC_PIN5


/** @defgroup ADC_RANKS_Options
  *
  */
#define ADC_RANK1			(1)
#define ADC_RANK2			(2)
#define ADC_RANK3			(3)
#define ADC_RANK4			(4)
#define ADC_RANK5			(5)
#define ADC_RANK6			(6)
#define ADC_RANK7			(7)
#define ADC_RANK8			(8)
#define ADC_RANK9			(9)
#define ADC_RANK10			(10)
#define ADC_RANK11			(11)
#define ADC_RANK12			(12)
#define ADC_RANK13			(13)
#define ADC_RANK14			(14)
#define ADC_RANK15			(15)
#define ADC_RANK16			(16)


/** @defgroup ADC_SamplingTime_Options
  *
  */
#define ADC_SAMPT_3CYCLES		(0)
#define ADC_SAMPT_15CYCLES		(1)
#define ADC_SAMPT_28CYCLES		(2)
#define ADC_SAMPT_56CYCLES		(3)
#define ADC_SAMPT_84CYCLES		(4)
#define ADC_SAMPT_112CYCLES		(5)
#define ADC_SAMPT_144CYCLES		(6)
#define ADC_SAMPT_480CYCLES		(7)


/******************************* globals *******************************/


/******************************* Configurations *******************************/
#define ADC_TOTAL_CHANNELS	15


/******************************* Functions prototypes *******************************/
/**
 * @func ADC_Init
 * @brief Initializes the provided ADC peripheral.
 *
 * @param	ADC_Handle_t* adc[IN]	-> specifies which ADC peripheral user wants to initialize.
 *
 * Important Register:
 * 	 	#ADC_CR1:
 * 	 		♦ SCAN[8]		-> single or multichannel(sequence) 	| 0: disabled		  ,   1: scan mode enabled
 * 	 		♦ RES[1:0]		-> resolution 							| 00: 12-bit,		01: 10-bit,		10: 8-bit		11: 6-bit
 *
 * 		#ADC_CR2:
 *			♦ ADON[0] 		-> On/Off the ADC
 * 			♦ CONT[1] 		-> On/Off Continuous conversion			| 0: single conversion,   1: multiple conversion
 * 			♦ ALIGN[11]		-> Data alignment 					 	| 0: Right			  ,   1: Left
 *		#ACD_COMMON_CCR:
 *			♦ ADCPRE[16-17] -> ADCs clock prescaler 				| 00: PCLK2/2,	01: PCLK2/4,	10: PCLK2/6,	11: PCLK2/8
 *		#ADC_SQR1:
 *			♦ L[20:23]		-> specifies e the total number of conversions in the regular channel conversion sequence

 * @warning This function must be called only after channels' configurations not before
 * 			[implementation dependency]
 *
 * @return void
 *
 */
void ADC_Init(ADC_Handle_t* adc);


/**
 * @func ADC_ConfigureChannel
 * @brief Initializes the provided ADC channel.
 *
 * @param	ADC_ChannelConfig_t* channel[IN]	-> specifies which ADC channel user wants to init.
 *
 * Important Registers:
 * 			(#) ADC_SMPR1, ADC_SMPR2 -> based on the channel that user wants to configure its sample time
 * 					♦ SMP1:SMP18
 * 			(#) ADC_SQR1, ADC_SQR2, ADC_SQR3 -> based on the channel
 * 					♦ SQ1:SQ16
 * @warning Channels configurations must be done before ADC configuration
 * 			[implementation dependency]
 *
 * @return void
 *
 */
void ADC_ConfigureChannel(ADC_Handle_t* adc, ADC_ChannelConfig_t* channel);




/**
 * @func ADC_Start
 * @brief Initializes the provided ADC peripheral.
 *
 * @param	ADC_Handle_t* adc[IN]	-> specifies which ADC peripheral user wants to ON/OFF.
 * Important Register:
 * 		#ADC_SR:
 *			♦ EOC[1] 		-> End of conversion bit   |   0: not complete,    1: complete *
 * @return void
 *
 */
void ADC_Start(ADC_Handle_t* adc);


/**
 * @func ADC_Read
 * @brief Read the ADC's data register.
 *
 * @param	ADC_Handle_t* adc[IN]	-> specifies which ADC peripheral user wants to read data.
 * Important Register:
 * 		#ADC_DR:
 *			♦ [1:16] 		-> ADC output data
 * @return void
 *
 */
uint16_t ADC_Read(ADC_Handle_t* adc);


#endif /* ADC_ADC_H_ */
