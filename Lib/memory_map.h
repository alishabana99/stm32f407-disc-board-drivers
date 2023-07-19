/*
 * @file memory_map.h
 * @author Ali Shabana
 * @date June 30, 2023
 *
 * @brief General Header file.
 * 		- This file contains Peripherals' typedefs, register mapping, and bit mapping of each register.
 * 		- The file is divided according the levels inside the memory map:
 * 			- Main Memory blocks in the memory map, each one has
 * 				- Buses, each bus has
 * 					- Peripherals, each peripheral has
 * 						- Registers, each register has
 * 							- Bits
 *
 */

#ifndef MEMORY_MAP_H_
#define MEMORY_MAP_H_

#include <stdint.h>


/*********Cortex-M4's internal peripherals Block*****************/
/**
 * @def CORTEX_M4_PERIPH_BASE
 * @brief The base address of Cortex-M4's internal peripherals Block in ARM's memory map.
 * 512-Mbyte block 7 Cortex-M4's internal peripherals
 * (0xE000 0000UL - 0xE00F FFFF)
 */
#define CORTEX_M4_PERIPH_BASE		(0xE0000000UL)

/**
 * @defgroup Peripherals_offsets_and_bases_from_CORTEX_M4_PERIPH_Bus_Base
 * @brief It's driven by the SystemClock or other(configurable).
 *
 */

#define	SysTick_OFFSET				(0x0000E000UL)
#define SysTick_BASE	(CORTEX_M4_PERIPH_BASE + SysTick_OFFSET)




/*********Peripheral Block*****************/
/**
 * @def PERIPH_BASE
 * @brief The base address of the peripherals in ARM's memory map.
 * 512-Mbyte block 2 Peripherals
 * (0x4000 0000 - 5FFF FFFF)
 */
#define PERIPH_BASE 				(0x40000000UL)

#define APB1_OFFSET (0x00000000UL)
#define APB2_OFFSET (0x00010000UL)
#define AHB1_OFFSET (0x00020000UL)



/**
 * @defgroup Base addresses
 * 	- Now we are standing on the {x} Bus, We have access to all peripherals that connected to it.
 * 	- And once we have reach the peripheral, we can reach each register inside it using systematic offsets.
 * 	- And inside each register we can access any bit as desired.
 */

#define APB1_BASE	(PERIPH_BASE + APB1_OFFSET)
#define APB2_BASE	(PERIPH_BASE + APB2_OFFSET)
#define AHB1_BASE	(PERIPH_BASE + AHB1_OFFSET)

/**
 * @defgroup Peripherals_offsets_and_bases_from_APB1_Bus_Base
 * @brief once we have reach the peripheral, we can reach each register inside it using systematic offsets.
 */
#define USART2_OFFSET	(0x00004400UL)
#define USART2_BASE		(APB1_BASE + USART2_OFFSET)

#define USART3_OFFSET	(0x00004800UL)
#define USART3_BASE		(APB1_BASE + USART3_OFFSET)

#define USART4_OFFSET	(0x00004C00UL)
#define USART4_BASE		(APB1_BASE + USART4_OFFSET)

#define USART5_OFFSET	(0x00005000UL)
#define USART5_BASE		(APB1_BASE + USART5_OFFSET)


/**
 * @defgroup Peripherals_offsets_and_bases_from_APB2_Bus_Base
 * @brief once we have reach the peripheral, we can reach each register inside it using systematic offsets.
 */
#define USART1_OFFSET	(0x00001000UL)
#define USART1_BASE		(APB2_BASE + USART1_OFFSET)

#define USART6_OFFSET	(0x00001400UL)
#define USART6_BASE		(APB2_BASE + USART6_OFFSET)


#define ADC_OFFSET		(0x00002000UL)
#define ADC_BASE		(APB2_BASE + ADC_OFFSET)

#define ADC1_OFFSET		(0x00000000UL)
#define ADC1_BASE		(ADC_BASE + ADC1_OFFSET)

#define ADC2_OFFSET		(0x00000100UL)
#define ADC2_BASE		(ADC_BASE + ADC2_OFFSET)

#define ADC3_OFFSET		(0x00000200UL)
#define ADC3_BASE		(ADC_BASE + ADC3_OFFSET)

#define ADC_COMMON_OFFSET		(0x00000300UL)
#define ADC_COMMON_BASE			(ADC1_BASE + ADC_COMMON_OFFSET)  /*RM:  relative to ADC1 base address + 0x300*/

/**
 * @defgroup Peripherals_offsets_and_bases_from_AHB1_Bus_Base
 * @brief once we have reach the peripheral, we can reach each register inside it using systematic offsets.
 */
#define GPIOA_OFFSET	(0x00000000UL)
#define GPIOA_BASE		(AHB1_BASE + GPIOA_OFFSET)

#define GPIOB_OFFSET	(0x00000400UL)
#define GPIOB_BASE		(AHB1_BASE + GPIOB_OFFSET)

#define GPIOC_OFFSET	(0x00000800UL)
#define GPIOC_BASE		(AHB1_BASE + GPIOC_OFFSET)

#define GPIOD_OFFSET	(0x00000C00UL)
#define GPIOD_BASE		(AHB1_BASE + GPIOD_OFFSET)

#define GPIOE_OFFSET	(0x00001000UL)
#define GPIOE_BASE		(AHB1_BASE + GPIOE_OFFSET)

#define GPIOH_OFFSET	(0x00001C00UL)
#define GPIOH_BASE		(AHB1_BASE + GPIOH_OFFSET)

#define RCC_OFFSET	(0x00003800UL)
#define RCC_BASE		(AHB1_BASE + RCC_OFFSET)




/*_________________________________________________________________________________________*/
/**
 * @defgroup Peripherals registers mapping using structs.
 * Details:
 *
 *
 *  */
typedef struct{
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFRL;
	volatile uint32_t AFRH;
}GPIO_t;

typedef struct
{
	  volatile uint32_t CR;            /*!< RCC clock control register,                                  Address offset: 0x00 */
	  volatile uint32_t PLLCFGR;       /*!< RCC PLL configuration register,                              Address offset: 0x04 */
	  volatile uint32_t CFGR;          /*!< RCC clock configuration register,                            Address offset: 0x08 */
	  volatile uint32_t CIR;           /*!< RCC clock interrupt register,                                Address offset: 0x0C */
	  volatile uint32_t AHB1RSTR;      /*!< RCC AHB1 peripheral reset register,                          Address offset: 0x10 */
	  volatile uint32_t AHB2RSTR;      /*!< RCC AHB2 peripheral reset register,                          Address offset: 0x14 */
	  volatile uint32_t AHB3RSTR;      /*!< RCC AHB3 peripheral reset register,                          Address offset: 0x18 */
	  uint32_t      RESERVED0;     /*!< Reserved, 0x1C                                                                    */
	  volatile uint32_t APB1RSTR;      /*!< RCC APB1 peripheral reset register,                          Address offset: 0x20 */
	  volatile uint32_t APB2RSTR;      /*!< RCC APB2 peripheral reset register,                          Address offset: 0x24 */
	  uint32_t      RESERVED1[2];  /*!< Reserved, 0x28-0x2C                                                               */
	  volatile uint32_t AHB1ENR;       /*!< RCC AHB1 peripheral clock register,                          Address offset: 0x30 */
	  volatile uint32_t AHB2ENR;       /*!< RCC AHB2 peripheral clock register,                          Address offset: 0x34 */
	  volatile uint32_t AHB3ENR;       /*!< RCC AHB3 peripheral clock register,                          Address offset: 0x38 */
	  uint32_t      RESERVED2;     /*!< Reserved, 0x3C                                                                    */
	  volatile uint32_t APB1ENR;       /*!< RCC APB1 peripheral clock enable register,                   Address offset: 0x40 */
	  volatile uint32_t APB2ENR;       /*!< RCC APB2 peripheral clock enable register,                   Address offset: 0x44 */
	  uint32_t      RESERVED3[2];  /*!< Reserved, 0x48-0x4C                                                               */
	  volatile uint32_t AHB1LPENR;     /*!< RCC AHB1 peripheral clock enable in low power mode register, Address offset: 0x50 */
	  volatile uint32_t AHB2LPENR;     /*!< RCC AHB2 peripheral clock enable in low power mode register, Address offset: 0x54 */
	  volatile uint32_t AHB3LPENR;     /*!< RCC AHB3 peripheral clock enable in low power mode register, Address offset: 0x58 */
	  uint32_t      RESERVED4;     /*!< Reserved, 0x5C                                                                    */
	  volatile uint32_t APB1LPENR;     /*!< RCC APB1 peripheral clock enable in low power mode register, Address offset: 0x60 */
	  volatile uint32_t APB2LPENR;     /*!< RCC APB2 peripheral clock enable in low power mode register, Address offset: 0x64 */
	  uint32_t      RESERVED5[2];  /*!< Reserved, 0x68-0x6C                                                               */
	  volatile uint32_t BDCR;          /*!< RCC Backup domain control register,                          Address offset: 0x70 */
	  volatile uint32_t CSR;           /*!< RCC clock control & status register,                         Address offset: 0x74 */
	  uint32_t      RESERVED6[2];  /*!< Reserved, 0x78-0x7C                                                               */
	  volatile uint32_t SSCGR;         /*!< RCC spread spectrum clock generation register,               Address offset: 0x80 */
	  volatile uint32_t PLLI2SCFGR;    /*!< RCC PLLI2S configuration register,                           Address offset: 0x84 */

} RCC_t;


typedef struct{

	volatile uint32_t RESERVED0[4];		/*Reserved, 0xE000-0xE010*/
	volatile uint32_t CSR;			/*SysTick Control And Status Register		OFFSET: 0x10*/
	volatile uint32_t RVR;			/*SysTick Reload Value Register				OFFSET:	0x14*/
	volatile uint32_t CVR;			/*SysTick Current Value Register			OFFSET:	0x18*/
	volatile uint32_t CALIB;		/*SysTick Calibration Value Register		OFFSET:	0x1C*/
}SysTick_t;


typedef struct{

	volatile uint32_t SR;	/*USART Status Register*/
	volatile uint32_t DR;	/*USART Data Register*/
	volatile uint32_t BRR;	/*USART Baud Rate Register*/
	volatile uint32_t CR1;	/*USART Control Register1*/
	volatile uint32_t CR2;	/*USART Control Register2*/
	volatile uint32_t CR3;	/*USART Control Register3*/
	volatile uint32_t GTPR;	/*USART Guard time and prescaler register*/
}USART_t;



typedef struct
{
  volatile uint32_t SR;     /*!< ADC status register,                         Address offset: 0x00 */
  volatile uint32_t CR1;    /*!< ADC control register 1,                      Address offset: 0x04 */
  volatile uint32_t CR2;    /*!< ADC control register 2,                      Address offset: 0x08 */
  volatile uint32_t SMPR1;  /*!< ADC sample time register 1,                  Address offset: 0x0C */
  volatile uint32_t SMPR2;  /*!< ADC sample time register 2,                  Address offset: 0x10 */
  volatile uint32_t JOFR1;  /*!< ADC injected channel data offset register 1, Address offset: 0x14 */
  volatile uint32_t JOFR2;  /*!< ADC injected channel data offset register 2, Address offset: 0x18 */
  volatile uint32_t JOFR3;  /*!< ADC injected channel data offset register 3, Address offset: 0x1C */
  volatile uint32_t JOFR4;  /*!< ADC injected channel data offset register 4, Address offset: 0x20 */
  volatile uint32_t HTR;    /*!< ADC watchdog higher threshold register,      Address offset: 0x24 */
  volatile uint32_t LTR;    /*!< ADC watchdog lower threshold register,       Address offset: 0x28 */
  volatile uint32_t SQR1;   /*!< ADC regular sequence register 1,             Address offset: 0x2C */
  volatile uint32_t SQR2;   /*!< ADC regular sequence register 2,             Address offset: 0x30 */
  volatile uint32_t SQR3;   /*!< ADC regular sequence register 3,             Address offset: 0x34 */
  volatile uint32_t JSQR;   /*!< ADC injected sequence register,              Address offset: 0x38*/
  volatile uint32_t JDR1;   /*!< ADC injected data register 1,                Address offset: 0x3C */
  volatile uint32_t JDR2;   /*!< ADC injected data register 2,                Address offset: 0x40 */
  volatile uint32_t JDR3;   /*!< ADC injected data register 3,                Address offset: 0x44 */
  volatile uint32_t JDR4;   /*!< ADC injected data register 4,                Address offset: 0x48 */
  volatile uint32_t DR;     /*!< ADC regular data register,                   Address offset: 0x4C */
}ADC_t;



typedef struct
{
  volatile uint32_t CSR;    /*!< ADC Common status register,                  Address offset: ADC1 base address + 0x300 */
  volatile uint32_t CCR;    /*!< ADC common control register,                 Address offset: ADC1 base address + 0x304 */
  volatile uint32_t CDR;    /*!< ADC common regular data register for dual
                             AND triple modes,                            Address offset: ADC1 base address + 0x308 */
}ADC_Common_t;


/*_________________________________________________________________________________________*/
/**
 * @defgroup Peripherals Bases casted to their structs types.
 * Details:
 *  */

#define RCC		((RCC_t*)RCC_BASE)

#define GPIOA	((GPIO_t*)GPIOA_BASE)
#define GPIOB	((GPIO_t*)GPIOB_BASE)
#define GPIOC	((GPIO_t*)GPIOC_BASE)
#define GPIOD	((GPIO_t*)GPIOD_BASE)
#define GPIOE	((GPIO_t*)GPIOE_BASE)
#define GPIOH	((GPIO_t*)GPIOH_BASE)

#define SysTick	((SysTick_t*)SysTick_BASE)

#define USART1	((USART_t*)USART1_BASE)
#define USART2	((USART_t*)USART2_BASE)
#define USART3	((USART_t*)USART3_BASE)
#define USART4	((USART_t*)USART4_BASE)
#define USART5	((USART_t*)USART5_BASE)
#define USART6	((USART_t*)USART6_BASE)

#define ADC1	((ADC_t*)ADC1_BASE)
#define ADC2	((ADC_t*)ADC2_BASE)
#define ADC3	((ADC_t*)ADC3_BASE)
#define ADC_COMMON	((ADC_Common_t*)ADC_COMMON_BASE)

/*____________________________________________________________________________________________*/
/*____________________________________RCC Registers Bits_____________________________________*/
/*____________________________________________________________________________________________*/

/* #RCC_CR ############################ */
#define RCC_CR_HSION				0
#define RCC_CR_HSIRDY				1
//________________RES				2
#define RCC_CR_HSITRIM				3	//[3-7]
#define RCC_CR_HSICAL				8	//[8-15]
#define RCC_CR_HSEON				16
#define RCC_CR_HSERDY				17
#define RCC_CR_BYB					18
#define RCC_CR_CSSON				19
//____________RES					[20-23]
#define RCC_CR_PLLON				24
#define RCC_CR_PLLRDY				25
#define RCC_CR_PLLI2SON				26
#define RCC_CR_PLLI2SRDY			27
//____________RES					[28-31]

/* #RCC_PLLCFGR ############################ */
#define RCC_PLLCFGR_PLLM0			0
#define RCC_PLLCFGR_PLLM1			1
#define RCC_PLLCFGR_PLLM2			2
#define RCC_PLLCFGR_PLLM3			3
#define RCC_PLLCFGR_PLLM4			4
#define RCC_PLLCFGR_PLLM5			5
#define RCC_PLLCFGR_PLLN			6	//[6-14]
//____________RES					15
#define RCC_PLLCFGR_PLLP0			16
#define RCC_PLLCFGR_PLLP1			17
//____________RES					[18-21]
#define RCC_PLLCFGR_PLLSRC			22
//____________RES					23
#define RCC_PLLCFGR_PLLQ0			24
#define RCC_PLLCFGR_PLLQ1			25
#define RCC_PLLCFGR_PLLQ2			26
#define RCC_PLLCFGR_PLLQ3			27
//____________RES					[28-31]

/* #RCC_CFGR ############################ */
#define RCC_CFGR_SW0				0
#define RCC_CFGR_SW1				1
#define RCC_CFGR_SWS0				2
#define RCC_CFGR_SWS1				3
#define RCC_CFGR_HPRE				4	//[4-7]
//____________RES					[8-9]
#define RCC_CFGR_PPRE1				10	//[10-12]
#define RCC_CFGR_PPRE2				13	//[13-15]
#define RCC_CFGR_RTCPRE				16	//[16-20]
#define RCC_CFGR_MCO1				21	//[21-22]
#define RCC_CFGR_I2SSCR				23
#define RCC_CFGR_MCO1PRE			24	//[24-26]
#define RCC_CFGR_MCO2PRE			27	//[27-29]
#define RCC_CFGR_MCO2				30	//[30-31]

/* #RCC_CIR ############################ */
#define RCC_CIR_LSIRDYF				0
#define RCC_CIR_LSERDYF				1
#define RCC_CIR_HSIRDYF				2
#define RCC_CIR_HSERDYF				3
#define RCC_CIR_PLLRDYF				4
#define RCC_CIR_PLLI2SRDYF			5
//____________RES					6
#define RCC_CIR_CSSF				7
#define RCC_CIR_LSIRDYIE			8
#define RCC_CIR_LSERDYIE			9
#define RCC_CIR_HSIRDYIE			10
#define RCC_CIR_HSERDYIE			11
#define RCC_CIR_PLLRDYIE			12
#define RCC_CIR_PLLI2SRDYIE			13
//____________RES					[14-15]
#define RCC_CIR_LSIRDYC				16
#define RCC_CIR_LSERDYC				17
#define RCC_CIR_HSIRDYC				18
#define RCC_CIR_HSERDYC				19
#define RCC_CIR_PLLRDYC				20
#define RCC_CIR_PLLI2SRDYC			21
//____________RES					22
#define RCC_CIR_CSSC				23
//____________RES					[24-31]

/* #RCC_AHB1RSTR ############################ */
#define RCC_AHB1RSTR_GPIOARST		0
#define RCC_AHB1RSTR_GPIOBRST		1
#define RCC_AHB1RSTR_GPIOCRST		2
#define RCC_AHB1RSTR_GPIODRST		3
#define RCC_AHB1RSTR_GPIOERST		4
#define RCC_AHB1RSTR_GPIOFRST		5
#define RCC_AHB1RSTR_GPIOGRST		6
#define RCC_AHB1RSTR_GPIOHRST		7
#define RCC_AHB1RSTR_GPIOIRST		8
//____________RES					[9-11]
#define RCC_AHB1RSTR_CRCRST			12
//____________RES					[13-20]
#define RCC_AHB1RSTR_DMA1RST		21
#define RCC_AHB1RSTR_DMA2RST		22
//____________RES					[23-24]
#define RCC_AHB1RSTR_ETHMACRST		25
//____________RES					[26-28]
#define RCC_AHB1RSTR_OTGHSRST		29
//____________RES					[30-31]

/* #RCC_AHB2RSTR ############################ */
#define RCC_AHB2RSTR_DCMIRST		0
//____________RES					[1-3]
#define RCC_AHB2RSTR_CRYPRST		4
#define RCC_AHB2RSTR_HASHRST		5
#define RCC_AHB2RSTR_RNGRST			6
#define RCC_AHB2RSTR_OTGFSRST		7
//____________RES					[8-31]

/* #RCC_AHB3RSTR ############################ */
#define RCC_AHB2RSTR_FSMCRST		0
//____________RES					[2-31]

/* #RCC_APB1ENR ############################ */
#define RCC_APB1ENR_TIM2RST		0
#define RCC_APB1ENR_TIM3RST		1
#define RCC_APB1ENR_TIM4RST		2
#define RCC_APB1ENR_TIM5RST		3
#define RCC_APB1ENR_TIM6RST		4
#define RCC_APB1ENR_TIM7RST		5
#define RCC_APB1ENR_TIM12RST		6
#define RCC_APB1ENR_TIM13RST		7
#define RCC_APB1ENR_TIM14RST		8
//____________RES					[9-10]
#define RCC_APB1ENR_WWDGRST		11
//____________RES					[12-13]
#define RCC_APB1ENR_SPI2RST		14
#define RCC_APB1ENR_SPI3RST		15
//____________RES					16
#define RCC_APB1ENR_UART2RST		17
#define RCC_APB1ENR_UART3RST		18
#define RCC_APB1ENR_UART4RST		19
#define RCC_APB1ENR_UART5RST		20
#define RCC_APB1ENR_I2C1RST		21
#define RCC_APB1ENR_I2C2RST		22
#define RCC_APB1ENR_I2C3RST		23
//____________RES					24
#define RCC_APB1ENR_CAN1RST		25
#define RCC_APB1ENR_CAN2RST		26
//____________RES					27
#define RCC_APB1ENR_PWRRST			28
#define RCC_APB1ENR_DACRST			29
//____________RES					[30-31]

/* #RCC_APB2RSTR ############################ */
#define RCC_APB2RSTR_TIM1RST		0
#define RCC_APB2RSTR_TIM8RST		1
//____________RES					[2-3]
#define RCC_APB2RSTR_UART1RST		4
#define RCC_APB2RSTR_UART6RST		5
//____________RES					[6-7]
#define RCC_APB2RSTR_ADCRST			8
//____________RES					[9-10]
#define RCC_APB2RSTR_SDIORST		11
#define RCC_APB2RSTR_SPI1RST		12
//____________RES					13
#define RCC_APB2RSTR_SYSCFGRST		14
//____________RES					15
#define RCC_APB2RSTR_TIM9RST		16
#define RCC_APB2RSTR_TIM10RST		17
#define RCC_APB2RSTR_TIM11RST		18
//____________RES					[19-31]

/* #RCC_AHB1ENR ############################ */
#define RCC_AHB1ENR_GPIOAEN			0
#define RCC_AHB1ENR_GPIOBEN			1
#define RCC_AHB1ENR_GPIOCEN			2
#define RCC_AHB1ENR_GPIODEN			3
#define RCC_AHB1ENR_GPIOEEN			4
#define RCC_AHB1ENR_GPIOFEN			5
#define RCC_AHB1ENR_GPIOGEN			6
#define RCC_AHB1ENR_GPIOHEN			7
#define RCC_AHB1ENR_GPIOIEN			8
//____________RES					[9-11]
#define RCC_AHB1ENR_CRCEN			12
//____________RES					[13-17]
#define RCC_AHB1ENR_BKPSRAMEN		18
//____________RES					19
#define RCC_AHB1ENR_CCMDATARAMEN	20
#define RCC_AHB1ENR_DMA1EN			21
#define RCC_AHB1ENR_DMA2EN			22
//____________RES					[23-24]
#define RCC_AHB1ENR_ETHMACEN		25
#define RCC_AHB1ENR_ETHMACTXEN		26
#define RCC_AHB1ENR_ETHMACRXEN		27
#define RCC_AHB1ENR_ETHMACPTPEN		28
#define RCC_AHB1ENR_OTGHSEN			29
#define RCC_AHB1ENR_OTGHSULPIEN		30
//____________RES					31

/* #RCC_AHB2ENR ############################ */
#define RCC_AHB2ENR_DCMIEN			0
//____________RES					[1-3]
#define RCC_AHB2ENR_CRYPEN			4
#define RCC_AHB2ENR_HASHEN			5
#define RCC_AHB2ENR_RNGEN			6
#define RCC_AHB2ENR_OTGFSEN			7
//____________RES					[8-31]

/* #RCC_AHB3ENR ############################ */
#define RCC_AHB3ENR_FSMCEN			0
//____________RES					[1-31]

/* #RCC_APB1ENR ############################ */
#define RCC_APB1ENR_TIM2EN		0
#define RCC_APB1ENR_TIM3EN		1
#define RCC_APB1ENR_TIM4EN		2
#define RCC_APB1ENR_TIM5EN		3
#define RCC_APB1ENR_TIM6EN		4
#define RCC_APB1ENR_TIM7EN		5
#define RCC_APB1ENR_TIM12EN		6
#define RCC_APB1ENR_TIM13EN		7
#define RCC_APB1ENR_TIM14EN		8
//____________RES				[9-10]
#define RCC_APB1ENR_WWDGEN		11
//____________RES				[12-13]
#define RCC_APB1ENR_SPI2EN		14
#define RCC_APB1ENR_SPI3EN		15
//____________RES				16
#define RCC_APB1ENR_UART2EN		17
#define RCC_APB1ENR_UART3EN		18
#define RCC_APB1ENR_UART4EN		19
#define RCC_APB1ENR_UART5EN		20
#define RCC_APB1ENR_I2C1EN		21
#define RCC_APB1ENR_I2C2EN		22
#define RCC_APB1ENR_I2C3EN		23
//____________RES				24
#define RCC_APB1ENR_CAN1EN		25
#define RCC_APB1ENR_CAN2EN		26
//____________RES				27
#define RCC_APB1ENR_PWREN		28
#define RCC_APB1ENR_DACEN		29
//____________RES				[30-31]

/* #RCC_APB2ENR ############################ */
#define RCC_APB2ENR_TIM1EN		0
#define RCC_APB2ENR_TIM8EN		1
//____________RES				[2-3]
#define RCC_APB2ENR_UART1EN		4
#define RCC_APB2ENR_UART6EN		5
//____________RES				[6-7]
#define RCC_APB2ENR_ADC1EN		8
#define RCC_APB2ENR_ADC2EN		9
#define RCC_APB2ENR_ADC3EN		10

#define RCC_APB2ENR_SDIOEN		11
#define RCC_APB2ENR_SPI1EN		12
//____________RES				13
#define RCC_APB2ENR_SYSCFGEN	14
//____________RES				15
#define RCC_APB2ENR_TIM9EN		16
#define RCC_APB2ENR_TIM10EN		17
#define RCC_APB2ENR_TIM11EN		18
//____________RES				[19-31]


///////////LOW POWER REGs////////////

/* #RCC_AHB1LPENR ############################ */
#define RCC_AHB1LPENR_GPIOALPEN			0
#define RCC_AHB1LPENR_GPIOBLPEN			1
#define RCC_AHB1LPENR_GPIOCLPEN			2
#define RCC_AHB1LPENR_GPIODLPEN			3
#define RCC_AHB1LPENR_GPIOELPEN			4
#define RCC_AHB1LPENR_GPIOFLPEN			5
#define RCC_AHB1LPENR_GPIOGLPEN			6
#define RCC_AHB1LPENR_GPIOHLPEN			7
#define RCC_AHB1LPENR_GPIOILPEN			8
//____________RES					[9-11]
#define RCC_AHB1LPENR_CRCLPEN			12
//____________RES					[13-14]
#define RCC_AHB1LPENR_FLITFLPEN			15
#define RCC_AHB1LPENR_SRAM1LPEN			16
#define RCC_AHB1LPENR_SRAM2LPEN			17
#define RCC_AHB1LPENR_BKPSRAMLPEN		18
//____________RES						[19-20]
#define RCC_AHB1LPENR_DMA1LPEN			21
#define RCC_AHB1LPENR_DMA2LPEN			22
//____________RES					[23-24]
#define RCC_AHB1LPENR_ETHMACLPEN		25
#define RCC_AHB1LPENR_ETHMACTXLPEN		26
#define RCC_AHB1LPENR_ETHMACRXLPEN		27
#define RCC_AHB1LPENR_ETHMACPTPLPEN		28
#define RCC_AHB1LPENR_OTGHSLPEN			29
#define RCC_AHB1LPENR_OTGHSULPILPEN		30
//____________RES					31

/* #RCC_AHB2LPENR ############################ */
#define RCC_AHB2LPENR_DCMILPEN			0
//____________RES					[1-3]
#define RCC_AHB2LPENR_CRYPLPEN			4
#define RCC_AHB2LPENR_HASHLPEN			5
#define RCC_AHB2LPENR_RNGLPEN			6
#define RCC_AHB2LPENR_OTGFSLPEN			7
//____________RES					[8-31]

/* #RCC_AHB3LPENR ############################ */
#define RCC_AHB3LPENR_FSMCLPEN			0
//____________RES					[1-31]

/* #RCC_APB1LPENR ############################ */
#define RCC_APB1LPENR_TIM2LPEN		0
#define RCC_APB1LPENR_TIM3LPEN		1
#define RCC_APB1LPENR_TIM4LPEN		2
#define RCC_APB1LPENR_TIM5LPEN		3
#define RCC_APB1LPENR_TIM6LPEN		4
#define RCC_APB1LPENR_TIM7LPEN		5
#define RCC_APB1LPENR_TIM12LPEN		6
#define RCC_APB1LPENR_TIM13LPEN		7
#define RCC_APB1LPENR_TIM14LPEN		8
//____________RES				[9-10]
#define RCC_APB1LPENR_WWDGLPEN		11
//____________RES				[12-13]
#define RCC_APB1LPENR_SPI2LPEN		14
#define RCC_APB1LPENR_SPI3LPEN		15
//____________RES					16
#define RCC_APB1LPENR_UART2LPEN		17
#define RCC_APB1LPENR_UART3LPEN		18
#define RCC_APB1LPENR_UART4LPEN		19
#define RCC_APB1LPENR_UART5LPEN		20
#define RCC_APB1LPENR_I2C1LPEN		21
#define RCC_APB1LPENR_I2C2LPEN		22
#define RCC_APB1LPENR_I2C3LPEN		23
//____________RES					24
#define RCC_APB1LPENR_CAN1LPEN		25
#define RCC_APB1LPENR_CAN2LPEN		26
//____________RES					27
#define RCC_APB1LPENR_PWRLPEN		28
#define RCC_APB1LPENR_DACLPEN		29
//____________RES				[30-31]

/* #RCC_APB2LPENR ############################ */
#define RCC_APB2LPENR_TIM1LPEN		0
#define RCC_APB2LPENR_TIM8LPEN		1
//____________RES					[2-3]
#define RCC_APB2LPENR_UART1LPEN		4
#define RCC_APB2LPENR_UART6LPEN		5
//____________RES					[6-7]
#define RCC_APB2LPENR_ADC1LPEN		8
#define RCC_APB2LPENR_ADC2LPEN		9
#define RCC_APB2LPENR_ADC3LPEN		10
#define RCC_APB2LPENR_SDIOLPEN		11
#define RCC_APB2LPENR_SPI1LPEN		12
//____________RES					13
#define RCC_APB2LPENR_SYSCFGLPEN	14
//____________RES					15
#define RCC_APB2LPENR_TIM9LPEN		16
#define RCC_APB2LPENR_TIM10LPEN		17
#define RCC_APB2LPENR_TIM11LPEN		18
//____________RES					[19-31]


/* #RCC_BDCR ############################ */
#define RCC_BDCR_LSEON				0
#define RCC_BDCR_LSERDY				1
#define RCC_BDCR_LSEBYP				2
//____________RES					[3-7]
#define RCC_BDCR_RTCSEL				8	//[8-9]
//____________RES					[10-14]
#define RCC_BDCR_RTCEN				15
#define RCC_BDCR_BDRST				16
//____________RES					[17-31]

/* #RCC_CSR ############################ */
#define RCC_CSR_LSION				0
#define	RCC_CSR_LSIRDY				1
//____________RES					[2-23]
#define	RCC_CSR_RMVF				24
#define	RCC_CSR_BORRSTF				25
#define	RCC_CSR_PINRSTF				26
#define	RCC_CSR_PORRSTF				27
#define	RCC_CSR_SFTRSTF				28
#define	RCC_CSR_IWDGRSTF			29
#define	RCC_CSR_WWDGRSTF			30
#define	RCC_CSR_LPWRRSTF			31

/* #RCC_SSCGR ############################ */
#define RCC_RCC_SSCGR_MODPER		0	//[0-12]
#define RCC_RCC_SSCGR_INCSTEP		13	//[13-27]
//____________RES					[28-29]
#define RCC_RCC_SSCGR_SPREADSEL		30
#define RCC_RCC_SSCGR_SSCGEN		31

/* #RCC_PLLI2SCFGR ############################ */
//____________RES						[0-5]
#define RCC_RCC_PLLI2SCFGR_PLLI2SN0		6
#define RCC_RCC_PLLI2SCFGR_PLLI2SN1		7
#define RCC_RCC_PLLI2SCFGR_PLLI2SN2		8
#define RCC_RCC_PLLI2SCFGR_PLLI2SN3		9
#define RCC_RCC_PLLI2SCFGR_PLLI2SN4		10
#define RCC_RCC_PLLI2SCFGR_PLLI2SN5		11
#define RCC_RCC_PLLI2SCFGR_PLLI2SN6		12
#define RCC_RCC_PLLI2SCFGR_PLLI2SN7		13
#define RCC_RCC_PLLI2SCFGR_PLLI2SN8		14
//____________RES						[15-27]
#define RCC_RCC_PLLI2SCFGR_PLLI2SR0		28
#define RCC_RCC_PLLI2SCFGR_PLLI2SR1		29
#define RCC_RCC_PLLI2SCFGR_PLLI2SR2		30
//____________RES						31





/*____________________________________________________________________________________________*/
/*___________________________________ SysTick Registers Bits _________________________________*/
/*____________________________________________________________________________________________*/

/* #SysTick_CSR Register ############################ */

#define SysTick_CSR_ENABLE				0
#define SysTick_CSR_TICKINT				1
#define SysTick_CSR_CLKSOURCE			2
//____________RES						[3-15]
#define SysTick_CSR_COUNTFLAG			16
//____________RES						[17-31]

/* #SysTick_RVR Register ############################ */
#define SysTick_RVR_LOAD //RELOAD		0	//[0-23]
//____________RES						[24-31]

/* #SysTick_CVR Register ############################ */
#define SysTick_CVR_CURRENT				0	//[0-23]
//____________RES						[24-31]

/* #SysTick_CALIB Register ############################ */
#define SysTick_CALIB_TENMS				0	//[0-23]
//____________RES						[24-29]
#define SysTick_CALIB_SKEW				30
#define SysTick_CALIB_NOREF				31


/*____________________________________________________________________________________________*/
/*___________________________________ SysTick Registers Bits _________________________________*/
/*____________________________________________________________________________________________*/
/* #USART_SR Register ############################ */
#define USART_SR_PE				0
#define USART_SR_FE				1
#define USART_SR_NF				2
#define USART_SR_ORE			3
#define USART_SR_IDLE			4
#define USART_SR_RXNE			5
#define USART_SR_TC				6
#define USART_SR_TXE			7
#define USART_SR_LBD			8
#define USART_SR_CTS			9
//____________RES				[10-31]

/* #USART_DR Register ############################ */
#define USART_DR_DATA			0	//[0-8]
//____________RES				[9-31]

/* #USART_BRR Register ############################ */
#define USART_BRR_DIV_FRAC		0	//[0-3]
#define USART_BRR_DIV_MANTISSA	4	//[4-15]
//____________RES				[16-31]

/* #USART_CR1 Register ############################ */
#define USART_CR1_SBK			0
#define USART_CR1_RWU			1
#define USART_CR1_RE			2
#define USART_CR1_TE			3
#define USART_CR1_IDLEIE		4
#define USART_CR1_RXNEIE		5
#define USART_CR1_TCIE			6
#define USART_CR1_TXEIE			7
#define USART_CR1_PEIE			8
#define USART_CR1_PS			9
#define USART_CR1_PCE			10
#define USART_CR1_WAKE			11
#define USART_CR1_M				12
#define USART_CR1_UE			13
//____________RES				14
#define USART_CR1_OVER8			15
//____________RES				[16-31]

/* #USART_CR2 Register ############################ */
#define USART_CR2_ADD			0	//[0-3]
//____________RES				4
#define USART_CR2_LBDIE			6
//____________RES				7
#define USART_CR2_LBCL			8
#define USART_CR2_CPHA			9
#define USART_CR2_CPOL			10
#define USART_CR2_CLKEN			11
#define USART_CR2_STOP			12	//[12-13]
//____________RES				[15-31]

/* #USART_CR3 Register ############################ */
#define USART_CR3_EIE			0
#define USART_CR3_IREN			1
#define USART_CR3_IRLP			2
#define USART_CR3_HDSEL			3
#define USART_CR3_NACK			4
#define USART_CR3_SCEN			5
#define USART_CR3_DMAR			6
#define USART_CR3_DMAT			7
#define USART_CR3_RTSE			8
#define USART_CR3_CTSE			9
#define USART_CR3_CTSIE			10
#define USART_CR3_ONEBIT		11
//____________RES				[12-31]

/* #USART_GTPR Register ############################ */
#define USART_GTPR_PSC			0	//[0-7]
#define USART_GTPR_GT			8	//[8-15]
//____________RES				[16-31]



/*____________________________________________________________________________________________*/
/*____________________________________ ADC Registers Bits _____________________________________*/
/*____________________________________________________________________________________________*/

/* #ADC_SR ############################ */
#define ADC_SR_AWD				0
#define ADC_SR_EOC				1
#define ADC_SR_JEOC				2
#define ADC_SR_JSTRT			3
#define ADC_SR_STRT				4
#define ADC_SR_OVR				5
//____________RES				[6-31]

/* #ADC_CR1 ############################ */
#define ADC_CR1_AWDCH			0 //[0-4]
#define ADC_CR1_EOCIE			5
#define ADC_CR1_AWDIE			6
#define ADC_CR1_JEOCIE			7
#define ADC_CR1_SCAN			8
#define ADC_CR1_AWDSGL			9
#define ADC_CR1_JAUTO			10
#define ADC_CR1_DISCEN			11
#define ADC_CR1_JDISCEN			12
#define ADC_CR1_DISCNUM			13	//[13-15]
//____________RES				[16-21]
#define ADC_CR1_JAWDEN			22
#define ADC_CR1_AWDEN			23
#define ADC_CR1_RES				24	//[24-25]
#define ADC_CR1_OVRIE			26
//____________RES				[27-31]


/* #ADC_CR2 ############################ */
#define ADC_CR2_ADON			0
#define ADC_CR2_CONT			1
//____________RES				[2-7]
#define ADC_CR2_DMA				8
#define ADC_CR2_DDS				9
#define ADC_CR2_EOCS			10
#define ADC_CR2_ALIGN			11
//____________RES				[12-15]
#define ADC_CR2_JEXTSEL			16	//[16-19]
#define ADC_CR2_JEXTEN			20	//[20-21]
#define ADC_CR2_JSWSTART		22
//____________RES				23
#define ADC_CR2_EXTSEL			24	//[24-27]
#define ADC_CR2_EXTEN			28	//[28-29]
#define ADC_CR2_SWSTART			30
//____________RES				31


/* #ADC_SMPR1 ############################ */
#define ADC_SMPR1_SMP10			0 //[0-2]
#define ADC_SMPR1_SMP11			3 //[3-5]
#define ADC_SMPR1_SMP12			6 //[6-8]
#define ADC_SMPR1_SMP13			9 //[9-11]
#define ADC_SMPR1_SMP14			12 //[12-14]
#define ADC_SMPR1_SMP15			15 //[15-17]
#define ADC_SMPR1_SMP16			18 //[18-20]
#define ADC_SMPR1_SMP17			21 //[21-23]
#define ADC_SMPR1_SMP18			24 //[24-26]
//____________RES				[27-31]

/* #ADC_SMPR2 ############################ */
#define ADC_SMPR2_SMP0			0 //[0-2]
#define ADC_SMPR2_SMP1			3 //[3-5]
#define ADC_SMPR2_SMP2			6 //[6-8]
#define ADC_SMPR2_SMP3			9 //[9-11]
#define ADC_SMPR2_SMP4			12 //[12-14]
#define ADC_SMPR2_SMP5			15 //[15-17]
#define ADC_SMPR2_SMP6			18 //[18-20]
#define ADC_SMPR2_SMP7			21 //[21-23]
#define ADC_SMPR2_SMP8			24 //[24-26]
#define ADC_SMPR2_SMP9			27 //[27-29]
//____________RES				[30-31]

/* #ADC_SQR1 ############################ */
#define ADC_SQR1_SQ13			0 //[0-4]
#define ADC_SQR1_SQ14			5 //[5-9]
#define ADC_SQR1_SQ15			10 //[10-14]
#define ADC_SQR1_SQ116			15 //[15-19]
#define ADC_SQR1_L				20 //[20-23]
//____________RES				[24-31]


/* #ADC_SQR2 ############################ */
#define ADC_SQR2_SQ7			0 //[0-4]
#define ADC_SQR2_SQ8			5 //[5-9]
#define ADC_SQR2_SQ9			10 //[10-14]
#define ADC_SQR2_SQ10			15 //[15-19]
#define ADC_SQR2_SQ11			20 //[20-24]
#define ADC_SQR2_SQ12			25 //[25-29]
//____________RES				[30-31]


/* #ADC_SQR3 ############################ */
#define ADC_SQR3_SQ1			0 //[0-4]
#define ADC_SQR3_SQ2			5 //[5-9]
#define ADC_SQR3_SQ3			10 //[10-14]
#define ADC_SQR3_SQ4			15 //[15-19]
#define ADC_SQR3_SQ5			20 //[20-24]
#define ADC_SQR3_SQ6			25 //[25-29]
//____________RES				[30-31]


/* #ADC_JSQR ############################ */
#define ADC_JSQR_JSQ1			0 //[0-4]
#define ADC_JSQR_JSQ2			5 //[5-9]
#define ADC_JSQR_JSQ3			10 //[10-14]
#define ADC_JSQR_JSQ4			15 //[15-19]
#define ADC_JSQR_JL				20 //[20-21]
//____________RES				[22-31]


/*____________________________________________________________________________________________*/
/*____________________________________ ADC Common Registers Bits _____________________________________*/
/*____________________________________________________________________________________________*/
/* #ADC_CSR ############################ */
#define ADC_CSR_AWD1			0
#define ADC_CSR_EOC1			1
#define ADC_CSR_JEOC1			2
#define ADC_CSR_JSTRT1			3
#define ADC_CSR_STRT1			4
#define ADC_CSR_OVR1			5
//____________RES				[6-7]
#define ADC_CSR_AWD2			8
#define ADC_CSR_EOC2			9
#define ADC_CSR_JEOC2			10
#define ADC_CSR_JSTRT2			11
#define ADC_CSR_STRT2			12
#define ADC_CSR_OVR2			13
//____________RES				[14-15]
#define ADC_CSR_AWD3			16
#define ADC_CSR_EOC3			17
#define ADC_CSR_JEOC3			18
#define ADC_CSR_JSTRT3			19
#define ADC_CSR_STRT3			20
#define ADC_CSR_OVR3			21
//____________RES				[22-31]

/* #ADC_CCR ############################ */
#define ADC_CCR_MULTI			0	//[0-4]
//____________RES				[5-7]
#define ADC_CCR_DELAY			8	//[8-11]
//____________RES				12
#define ADC_CCR_DDS				13
#define ADC_CCR_DMA				14	//[14-15]
#define ADC_CCR_ADCPRE			16	//[16-17]
//____________RES				[18-21]
#define ADC_CCR_VBATE			22
#define ADC_CCR_TSVREF			23
//____________RES				[24-31]









#endif /* MEMORY_MAP_H_ */
