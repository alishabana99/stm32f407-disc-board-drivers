/**
 * @file usart.c
 * @author Ali Shabana
 * @date Jul 8, 2023
 *
 * @brief USART's module source file .
 *
 * ♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣ HOW TO USE ♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣♣
 * # Which USART Instance ?
 * 		[♥] -> We choose which USART instance to work with during whatever API we're working with by passing
 * 				USART_Peripheral_en of the dedicated instance.
 * 			->USART_Peripheral_en is used as an index of the g_USART_INSTANCES that has the base addresses of
 * 				All USART instances.
 *
 * # HOW to Configure ?
 *		[♥] Each USART instance has a group of configuration parameters [the only implemented ones]
 *			@Configurations section in the header (usart.h) file.
 *		[♥] Each configuration parameter different options are defined @macros section in the header (usart.h) file.
 *
 * # Another Related Configuration ?
 * 		[♥] -> I'm using USART as a main debugging tool, so @common_lib.c uses the a USART instance [depending on the configured]
 * 				as a serial monitor.
 * 			-> You can configured what USART instance to use, from common_lib.h @configuration section
 * 				for USART_DEBUGGING_CHANNEL provided the desired USART_Peripheral_en.
 * 			-> For sure, the desired USART instance has to be initialized before being used as a debugging channel.
 *
 * # Usage Work Flow ?
 * 		1. Configure in usart.h @configuration section using different options in usart.h @macros section
 * 		2. Call USART_Init() providing the meant using USART_Peripheral_en.
 * 		3. Call whatever USART API you want to use.
 *
 * # Adding more Features ?
 * 		[♥] Adding more features means that there're more configurations to be considered
 * 		[♥] New configurations options need to be added for each new configuration parameter in usart.h @macros
 * 		[♥] Then, choose which option will be used for each new configuration parameter in usart.h @configurations
 * 		[♥] Then, each of these new configuration parameters is applied through the initialization function, mainly,
 * 			and other related USART APIs, sequentially.
 *
 */

/******************************* Includes *******************************/
#include "usart.h"

/*******************************  Macros *******************************/


/******************************* Configurations (if any) *******************************/


/******************************* privates *******************************/
volatile USART_t* g_USART_INSTANCES[6] = {USART1, USART2, USART3, USART4, USART5, USART6};

/******************************* Functions Implementation *******************************/

/**
 * @func USART_SetBRRValues
 * @brief This function responsible for returning the register values of mantissa and fraction bits
 * To be put into the bits directly.
 *
 * @param	USART_Peripheral_en usart [IN]		-> specifies which USART peripheral we're working with during the function call.
 *
 * @param 	uint8_t over [IN]					-> oversampling number of samples | 8 OR 16
 *
 * @param	uint32_t baud [IN]					-> baud rate of the specified USART peripheral
 *
 * @note STATIC FUNCTION
 * @return void
 * *
 */
static void USART_ConfigureGPIOPins(USART_Peripheral_en usart){

	RCC_AHB1PERIPH_en TxRCCgpioPort;
	RCC_AHB1PERIPH_en RxRCCgpioPort;
	GPIO_t* Txgpio;
	GPIO_t* Rxgpio;
	GPIO_Pin_en TxPin;
	GPIO_Pin_en RxPin;


	switch(usart){
	case USART_USART1:

		break;
	case USART_USART2:
		TxRCCgpioPort = USART2_TX_RCC_GPIO_PORT;
		RxRCCgpioPort = USART2_RX_RCC_GPIO_PORT;
		Txgpio = USART2_TX_GPIO;
		Rxgpio = USART2_RX_GPIO;
		TxPin = USART2_TX_PIN;
		RxPin = USART2_RX_PIN;

		break;
	case USART_USART3:

		break;
	case USART_USART4:

		break;
	case USART_USART5:

		break;
	case USART_USART6:

		break;
	}

	/*Configure related GPIO pins*/
		//Enable correspondent GPIO pins' clock for (Tx, Rx, ....)
		RCC_EnableAHB1Clock(TxRCCgpioPort);
		RCC_EnableAHB1Clock(RxRCCgpioPort);

		//set mode to AF
		GPIO_SetPinMode(Txgpio, TxPin, GPIO_AF);
		GPIO_SetPinMode(Rxgpio, RxPin, GPIO_AF);
		//set AF
		GPIO_SetPinAF(Txgpio, TxPin, GPIO_AF_USART2);
		GPIO_SetPinAF(Rxgpio, RxPin, GPIO_AF_USART2);


		//set push_pull functionality for Tx (the output pin)
		GPIO_SetPinOutputType(Txgpio, TxPin, GPIO_PUSH_PULL);

		//set Output speed
		GPIO_SetPinOutputSpeed(Txgpio, TxPin, GPIO_MEDIUM_SPEED);

		//set pullup functionality for Tx,Rx
		GPIO_SetPinPull(Txgpio, TxPin, GPIO_PULL_UP);	//Tx
		GPIO_SetPinPull(Rxgpio, RxPin, GPIO_PULL_UP);	//Rx



}

/**
 * @func USART_SetBRRValues
 * @brief This function responsible for returning the register values of mantissa and fraction bits
 * To be put into the bits directly.
 *
 * @param	USART_Peripheral_en usart [IN]		-> specifies which USART peripheral we're working with during the function call.
 *
 * @param 	uint8_t over [IN]					-> oversampling number of samples | 8 OR 16
 *
 * @param	uint32_t baud [IN]					-> baud rate of the specified USART peripheral
 *
 * @note STATIC FUNCTION
 * @return void
 * *
 */
static void	USART_SetBRRValues(USART_Peripheral_en usart, uint32_t usart_freq, uint8_t over, uint32_t baud){
/*Equation
 => Baud = Usart_freq / baud* 8(2-OVER) * USARTDIV

 => USARTDIV = Usart_freq / baud* 8(2-OVER)

 *  */
	uint32_t usart_div = 0;
	uint16_t mantissa = 0;
	uint16_t frac = 0;

	usart_div = (usart_freq*100 ) / (baud * (8*(2-over)));

	mantissa = (usart_div/100);
	frac = usart_div - (mantissa*100);
	frac *= (8* (2-over));
	frac += 50; //rounding the number

	frac /= 100;
	switch(over){
	case 0:
		if(frac >= 16){
			mantissa++;
			frac = 0;
		}else{
			//noting
		}
		break;
	case 1:
		if(frac >= 8){
			mantissa++;
			frac = 0;
		}else{
			//noting
		}
		break;
	}

	g_USART_INSTANCES[usart]->BRR = 0;
	g_USART_INSTANCES[usart]->BRR |= (frac << USART_BRR_DIV_FRAC);
	g_USART_INSTANCES[usart]->BRR |= (mantissa << USART_BRR_DIV_MANTISSA);
}


/**
 * @func USART_Init
 * @brief Initializes the provided USART peripheral.
 *
 * @param	USART_Periph_en usart[IN]	-> specifies which USART peripheral user wants to init
 *
 * #Important Registers [till now]:
 * 			=> USART->BRR
 * 				[♥] DIV_Fraction[0:3]
 * 				[♥] DIV_Mantissa[11:0]
 *
 * 			=> USART->CR1
 * 				[♥] OVER8[16]		oversampling mode | 0 : oversampling by 16, 1: oversampling by 8
 * 			=[♥] UE[13]			Enabling USART
 * 				[♥] M[12]			Word Length		  | 0: 8 data bits, 1: 9 data bits [including parity]
 * 				[♥] PCE[10]			Parity control enable
 * 				[♥] PS[9]			Parity Selection	| 0: Even parity, 1: Odd parity
 * 			=[♥] TE[3]			Transmitter Enable
 * 			=[♥] RE[2]			Receiver Enable
 *
 * 			=> USART->CR2
 * 				[♥] STOP[12:13]		Number of stop bits | 00: 1 Stop bit,
 * 														  01: 0.5 Stop bit,
 * 														  10: 2 Stop bits,
 * 														  11: 1.5 Stop bits
*
* 			=> USART->CR3
* 				[♥] ONEBIT[11]		1: Three sample method, 0: 1Bit sample method (NF is disabled)
*
 *
 * @return void
 * *
 */
void USART_Init(USART_Peripheral_en usart){

/*Choosing which usart peripheral to configure*/
	switch(usart){
	case USART_USART1:

		break;
	case USART_USART2:

		/*Enable related  bus Clock*/
		RCC_EnableAPB1Clock(RCC_APB1_USART2);

			USART_ConfigureGPIOPins(usart);

			/*Configure Baud rate*/
			USART_SetBRRValues(usart, USART2_F_USART, USART2_OVERSAMPLE, USART2_BAUDRATE);

			/*configure word length*/
			CHANGE_BIT_VAL(g_USART_INSTANCES[usart]->CR1,USART_CR1_M,USART2_WORDLENGTH);

			/*configure parity*/
#if USART2_PARITY == PARITY_DISABLED
			CLEAR_BIT(g_USART_INSTANCES[usart]->CR1, USART_CR1_PCE);
#else
			SET_BIT(g_USART_INSTANCES[usart]->CR1, USART_CR1_PCE);
			CHANGE_BIT_VAL(g_USART_INSTANCES[usart]->CR1,USART_CR1_PS,USART2_PARITY);
#endif

			/*configure stop bits*/
			g_USART_INSTANCES[usart]->CR2 |= ( USART2_STOP_BITS <<USART_CR2_STOP);

			/*configure oversampling 8|16*/
			CHANGE_BIT_VAL(g_USART_INSTANCES[usart]->CR1, USART_CR1_OVER8, USART2_OVERSAMPLE);

			/*configure sampling method*/
			CHANGE_BIT_VAL(USART2->CR3, USART_CR3_ONEBIT, USART2_SAMPLING_METHOD);

			/*configure/enable usart mode transmitter|receiver|transceiver*/
#if USART2_MODE == TRANSMITTER_MODE
			SET_BIT(USART2->CR1,USART_CR1_TE);
#elif USART2_MODE == RECEIVER_MODE
			SET_BIT(USART2->CR1,USART_CR1_RE);
#else
			SET_BIT(USART2->CR1,USART_CR1_TE);
			SET_BIT(USART2->CR1,USART_CR1_RE);
#endif

			SET_BIT(USART2->CR1, USART_CR1_UE);
		break;
	case USART_USART3:
		break;
	case USART_USART4:
		break;
	case USART_USART5:
		break;
	case USART_USART6:
		break;
	}



}


/**
 * @func USART_SendChar
 * @brief Sends a character.
 *
 * @param	USART_Peripheral_en usart
 * @param	uint8_t msg[IN]	-> the to-be-sent 8-bit message
 *
 * @return void
 * *
 */
void USART_SendChar(USART_Peripheral_en usart, uint8_t msg){

	while(!GET_BIT(g_USART_INSTANCES[usart]->SR,USART_SR_TXE));
	USART2->DR = msg;

}


/**
 * @func USART_ReceiveChar
 * @brief receives a character
 *
 * @param	USART_Peripheral_en usart
 * @param	uint8_t* msg [OUT]	-> received message by reference
 *
 * @return void
 *
 */
void USART_ReceiveChar(USART_Peripheral_en usart, uint8_t* msg){

	while(! GET_BIT(g_USART_INSTANCES[usart]->SR,USART_SR_RXNE));
	*msg = g_USART_INSTANCES[usart]->DR;

}


/******************************* ISR *******************************/


