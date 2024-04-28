/* This is belonged to Bui Manh Huy - 20213707
Main Use: Creating Periphals (Mostly Simplified For Only GPIO Functions)
All Rights Reserved */

#ifndef _STM32F103XX
#define _STM32F103XX

#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
/* General definitions */
#define ENABLES  1
#define DISABLES 0
#define SETS		ENABLES
#define RESETS	DISABLES
/*NVIC ADDRESS */
#define NVIC_ISER0 		((volatile uint32_t*)0xE000E100) /* Enable Set External interrupts from 0 to 31*/
#define NVIC_ISER1 		((volatile uint32_t*)0xE000E104) /* Enable Set External interrupts from 32 to 63*/
#define NVIC_ISER2		((volatile uint32_t*)0xE000E108) /* Enable Set External interrupts from 64 to 80*/
	
#define NVIC_ICER0		((volatile uint32_t*)0xE000E180) /* Enable Clear External interrupts from 0 to 31*/
#define NVIC_ICER1		((volatile uint32_t*)0xE000E184) /* Enable Clear External interrupts from 32 to 63*/
#define NVIC_ICER2		((volatile uint32_t*)0xE000E188) /* Enable Clear External interrupts from 64 to 80*/

#define NVIC_IABR0		((volatile uint32_t*)0xE000E300) /* Corresponding interrupt is active or active and pending => 1, Interrupt not active => 0 */
#define NVIC_IABR1		((volatile uint32_t*)0xE000E304) /* Corresponding interrupt is active or active and pending => 1, Interrupt not active => 0 */
#define NVIC_IABR3		((volatile uint32_t*)0xE000E308) /* Corresponding interrupt is active or active and pending => 1, Interrupt not active => 0 */
	
#define NVIC_IPR_BASE	((volatile uint32_t*)0xE000E400) /*Priority interrupts base address*/
	#define NO_PR_BITS_IMPLEMENTED 		4 		/* Passing [3:0] bits */

#define FLASH_BASE            0x08000000U /*!< FLASH base address in the alias region */
#define FLASH_BANK1_END       0x08007FFFU /*!< FLASH END address of bank1 */
#define SRAM_BASE             0x20000000U /*!< SRAM base address in the alias region */
#define PERIPH_BASE           0x40000000U /*!< Peripheral base address in the alias region */

#define SRAM_BB_BASE          0x22000000U /*!< SRAM base address in the bit-band region */
#define PERIPH_BB_BASE        0x42000000U /*!< Peripheral base address in the bit-band region */

/*!< Peripheral memory map */
#define APB1PERIPH_BASE				PERIPH_BASE
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x00010000U)
#define AHBPERIPH_BASE        (PERIPH_BASE + 0x00020000U)

/*!< GPIO PORT BASE ADDRESS OF APB2 */
#define GPIOA_BASEADDRESS			(APB2PERIPH_BASE + 0x0800)
#define GPIOB_BASEADDRESS			(APB2PERIPH_BASE + 0x0C00)
#define GPIOC_BASEADDRESS			(APB2PERIPH_BASE + 0x1000)
#define GPIOD_BASEADDRESS			(APB2PERIPH_BASE + 0x1400)

/* RCC BASE ADDRESS */
#define RCC_BASEADDRESS				(AHBPERIPH_BASE + 0x1000)
/* EXTI BASE ADDRESS */
#define EXTI_BASEADDRESS			(APB2PERIPH_BASE + 0x0400)
/* Alternative Function GPIO BASE ADDRESS*/
#define AFIO_BASEADDR					(APB2PERIPH_BASE + 0x0000)
/* GPIO Register Definition */
typedef struct{
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;	
}GPIO_RegDef;
/* RCC Register Definition */
typedef struct{
	volatile uint32_t CR;
	volatile uint32_t CFG;
	volatile uint32_t CIR;
	volatile uint32_t APB2STR;
	volatile uint32_t APB1STR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	volatile uint32_t AHBSTR;
	volatile uint32_t CFGR2;
}RCC_RegDef;
/* EXTI Register Definition */
typedef struct{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_RegDef;
/* Alternative function Register Definition */
typedef struct
{
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR1;
	volatile uint32_t EXTICR2;
	volatile uint32_t EXTICR3;
	volatile uint32_t EXTICR4;
	volatile uint32_t MAPR2;
}AFIO_RegDef;
/* GPIO Macro */
#define GPIOA_Macro ((GPIO_RegDef*)GPIOA_BASEADDRESS)
#define GPIOB_Macro ((GPIO_RegDef*)GPIOB_BASEADDRESS)
#define GPIOC_Macro ((GPIO_RegDef*)GPIOC_BASEADDRESS)
#define GPIOD_Macro ((GPIO_RegDef*)GPIOD_BASEADDRESS)
/* RCC Macro */
#define RCC	((RCC_RegDef*)RCC_BASEADDRESS)
/* EXTI Macro */
#define EXTI ((EXTI_RegDef*)EXTI_BASEADDRESS)
/* SYSCFG Macro */
#define AFIO ((AFIO_RegDef*)AFIO_BASEADDR)
/* Periphral clock enable macros */
/* Clock Enable GPIO */
#define GPIOA_CLOCK_ENABLE()	(RCC->APB2ENR  |= (1 << 2) )
#define GPIOB_CLOCK_ENABLE()	(RCC->APB2ENR  |= (1 << 3) )
#define GPIOC_CLOCK_ENABLE()	(RCC->APB2ENR  |= (1 << 4) )
#define GPIOD_CLOCK_ENABLE()	(RCC->APB2ENR  |= (1 << 5) )
/* Clock Disable GPIO */
#define GPIOA_CLOCK_DISABLE()	(RCC->APB2ENR  &= (~(1 << 2)))
#define GPIOB_CLOCK_DISABLE()	(RCC->APB2ENR  &= (~(1 << 3)))
#define GPIOC_CLOCK_DISABLE()	(RCC->APB2ENR  &= (~(1 << 4)))
#define GPIOD_CLOCK_DISABLE()	(RCC->APB2ENR  &= (~(1 << 5)))
/* Clock Reset GPIO */
#define GPIOA_REG_RESET()						do {(RCC->APB2STR |=(1 <<  2)); (RCC->APB2STR &= (~(1 <<  2)));}while(0)
#define GPIOB_REG_RESET()           do {(RCC->APB2STR |=(1 <<  3)); (RCC->APB2STR &= (~(1 <<  3)));}while(0)
#define GPIOC_REG_RESET()           do {(RCC->APB2STR |=(1 <<  4)); (RCC->APB2STR &= (~(1 <<  4)));}while(0)
#define GPIOD_REG_RESET()           do {(RCC->APB2STR |=(1 <<  5)); (RCC->APB2STR &= (~(1 <<  5)));}while(0)
#define GPIO_BASEADDR_TO_CODE(x)      ( (x == GPIOA_Macro)?0:\
																				(x == GPIOB_Macro)?1:\
																				(x == GPIOC_Macro)?2:\
																				(x == GPIOD_Macro)?3: 0)
/* IRQ Macro Definitions */
#define IRQ_NO_EXTI0				6
#define IRQ_NO_EXTI1				7
#define IRQ_NO_EXTI2				8
#define IRQ_NO_EXTI3				9
#define IRQ_NO_EXTI4				10
#define IRQ_NO_EXTI9_5				23
#define IRQ_NO_EXTI15_10			40
/* Priority Macro */
#define NVIC_IRQ_PRI0    	0
#define NVIC_IRQ_PRI1    	1
#define NVIC_IRQ_PRI2    	2
#define NVIC_IRQ_PRI3    	3
#define NVIC_IRQ_PRI4    	4
#define NVIC_IRQ_PRI5    	5
#define NVIC_IRQ_PRI6    	6
#define NVIC_IRQ_PRI7    	7
#define NVIC_IRQ_PRI8    	8
#define NVIC_IRQ_PRI9    	9
#define NVIC_IRQ_PRI10    	10
#define NVIC_IRQ_PRI11    	11
#define NVIC_IRQ_PRT12    	12
#define NVIC_IRQ_PRI13    	13
#define NVIC_IRQ_PRI14    	14
#define NVIC_IRQ_PRI15    	15
/* AFIO CLock */
#define AFIO_PCLK_EN()			( RCC->APB2ENR |= ( 1 << 0) )
#include "stm32f103xx_gpio_driver.h"
#endif /* _STM32F103XX_H_ */
