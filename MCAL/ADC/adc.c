/**
 * @file adc.c
 * @author Ali Shabana
 * @date Jul 14, 2023
 *
 * @brief ADC peripherals' drivers source file .
 *
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

/******************************* Includes *******************************/
#include "adc.h"

/*******************************  Macros *******************************/


/******************************* Configurations (if any) *******************************/


/******************************* privates *******************************/
//maintains the reserved adc channels so the correspondent GPIO pins configuration can be done.
static uint8_t g_ADC_TAKEN_CHANNELS[ADC_TOTAL_CHANNELS]= {0};
static uint8_t g_ADC_TAKEN_CHANNELS_INDEX = 0;

/******************************* Functions Implementation *******************************/

/**
 * @func ADC_ConfigureGPIOPins
 * @brief Initializes the needed gpio pins needed for the adc channels.
 *
 * @return void
 *
 */

static void ADC_ConfigureGPIOPins(){
	GPIO_t* gpio = 0;
	RCC_AHB1PERIPH_en rcc_gpio = 0;
	uint8_t index_pinno_map =0;
	for(int8_t i = 0; i< g_ADC_TAKEN_CHANNELS_INDEX; i++){
		if(g_ADC_TAKEN_CHANNELS[i] <= 7){
			/*PORTA Configurations*/
			gpio = GPIOA;
			index_pinno_map = 0;
			rcc_gpio = RCC_AHB1_GPIOA;
		}else if(g_ADC_TAKEN_CHANNELS[i] <= 9){
			/*PORTB Configurations*/
			gpio = GPIOB;
			index_pinno_map = 8;
			rcc_gpio = RCC_AHB1_GPIOB;

		}else{
			/*PORTC Configurations*/
			gpio = GPIOC;
			index_pinno_map = 10;
			rcc_gpio = RCC_AHB1_GPIOC;
		}

		RCC_EnableAHB1Clock(rcc_gpio);
		GPIO_SetPinMode(gpio, g_ADC_TAKEN_CHANNELS[i]-index_pinno_map, GPIO_ANALOG);
		GPIO_SetPinPull(gpio, g_ADC_TAKEN_CHANNELS[i]-index_pinno_map, GPIO_NO_PULL);

	}


}
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
void ADC_Init(ADC_Handle_t* adc){

	/*Configure used channels' related gpio pins*/
	ADC_ConfigureGPIOPins();

	/*Configure the dedicated ADC Peripheral*/

	//SCAN mode: single channel || multiple channels
	adc->instace->CR1 |= ((adc->configs.scan_mode)<< ADC_CR1_SCAN);

	//Number of ADC Resolution bit
	adc->instace->CR1 |= ((adc->configs.resolution)<< ADC_CR1_RES);

	//CONT mode: single conversion || multiple channels
	CHANGE_BIT_VAL(adc->instace->CR2, ADC_CR2_CONT, adc->configs.cont);

	//ALIGN: data register alignment { Right, Left }
	adc->instace->CR2 |= ((adc->configs.data_alignment)<< ADC_CR2_ALIGN);

	//ADC prescaler
	ADC_COMMON->CCR |= ((adc->configs.prescaler) <<ADC_CCR_ADCPRE);

	//number of conversion channels
	adc->instace->SQR1 |= ((adc->configs.num_of_conversions-1)<< ADC_SQR1_L);



	//Enable the ADC module
	SET_BIT(adc->instace->CR2, ADC_CR2_ADON);
}

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
void ADC_ConfigureChannel(ADC_Handle_t* adc, ADC_ChannelConfig_t* channel){
	/*This is needed for the GPIO configuration step as the ADC_ConfigureGPIOPins() function
	 *configures all the used gpio pins by checking the taken channels.*/
	g_ADC_TAKEN_CHANNELS[g_ADC_TAKEN_CHANNELS_INDEX++] = channel->channel_num;


	/*Configure used channels' related gpio pins*/
	ADC_ConfigureGPIOPins();



	//Enable ADC clock
	uint32_t adc_address_int = (uint32_t)adc->instace;
	switch (adc_address_int) {
		case (uint32_t)ADC1:
			RCC_EnableAPB2Clock(RCC_APB2_ADC1);
			break;
		case (uint32_t)ADC2:
			RCC_EnableAPB2Clock(RCC_APB2_ADC2);
			break;
		case (uint32_t)ADC3:
			RCC_EnableAPB2Clock(RCC_APB2_ADC3);
			break;
		default:
			break;
	}


	/*configuring the channel rank in the correspondent register
	 *based on its value*/
	uint8_t ch_rank = channel->rank;

	if(ch_rank <= 6){
		adc->instace->SQR3 |= ((channel->channel_num)<< ((ch_rank-1)*5));

	}else if(ch_rank <= 12 ){
		adc->instace->SQR2 |= ((channel->channel_num)<< ((ch_rank-7)*5));
	}else{
		//from 13 to 16
		adc->instace->SQR1 |= ((channel->channel_num)<< ((ch_rank-13)*5));
	}

	/*configuring channel's sampling time in the correspondent register
	 * based on its value*/
	uint8_t ch_samp_time = channel->sampling_time;

	if(ch_samp_time > 9){
		adc->instace->SMPR1 |= (channel->sampling_time << (((channel->channel_num)-10)*3));
	}else{
		//from 0 to 9
		adc->instace->SMPR2 |= (channel->sampling_time << (((channel->channel_num))*3));
	}


}
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
void ADC_Start(ADC_Handle_t* adc){
	SET_BIT(adc->instace->CR2, ADC_CR2_SWSTART);
}


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
uint16_t ADC_Read(ADC_Handle_t* adc){

	/*wait till we make sure that conversion is done*/
	while(GET_BIT(adc->instace->SR, ADC_SR_EOC) == 0); //while conversion not complete
	/*Read*/
	return adc->instace->DR;

}


/******************************* ISR *******************************/


