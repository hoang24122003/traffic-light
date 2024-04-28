/* This is belonged to Bui Manh Huy - 20213707
Main Use: Creating GPIO Header
All Rights Reserved */

#ifndef _STM32F103XX_GPIO_DRIVER
#define _STM32F103XX_GPIO_DRIVER
#include "stm32f103xx.h"
/* GPIO Configuration */
typedef struct{
	uint32_t GPIO_PinNumber;
	uint32_t GPIO_PinMode;
	uint8_t GPIO_PinSpeed;
	uint8_t GPIO_PinPull;
}GPIO_Config;
/* GPIO Status */
typedef struct{
	GPIO_RegDef *pGPIOx;
	GPIO_Config GPIO_PinConfig;
}GPIO_Handle;

/* General for GPIO */
#define GPIO_PIN_SET 	1
#define GPIO_PIN_RESET 	0
/* GPIO PIN (sometimes it might conflict with other drivers, so be careful)*/
#define GPIO_PIN_0		(0u)
#define GPIO_PIN_1		(1u)
#define GPIO_PIN_2		(2u)
#define GPIO_PIN_3		(3u)
#define GPIO_PIN_4		(4u)
#define GPIO_PIN_5		(5u)
#define GPIO_PIN_6		(6u)
#define GPIO_PIN_7		(7u)
#define GPIO_PIN_8		(8u)
#define GPIO_PIN_9		(9u)
#define GPIO_PIN_10		(10u)
#define GPIO_PIN_11		(11u)
#define GPIO_PIN_12		(12u)
#define GPIO_PIN_13		(13u)
#define GPIO_PIN_14		(14u)
#define GPIO_PIN_15		(15u)

/*  GPIO pin modes */

#define  GPIO_MODE_INPUT         1    /*!< Input Floating Mode                   */
#define  GPIO_MODE_OUTPUT_PP     2  /*!< Output Push Pull Mode                 */
#define  GPIO_MODE_OUTPUT_OD     3  /*!< Output Open Drain Mode                */
#define  GPIO_MODE_AF_PP         4 /*!< Alternate Function Push Pull Mode     */
#define  GPIO_MODE_AF_OD         5  /*!< Alternate Function Open Drain Mode    */
#define  GPIO_MODE_AF_INPUT   		GPIO_MODE_INPUT          /*!< Alternate Function Input Mode         */

#define  GPIO_MODE_ANALOG        6   /*!< Analog Mode  */

#define  GPIO_MODE_IT_RT         7  /*!< External Interrupt Mode with Rising edge trigger detection          */
#define  GPIO_MODE_IT_FT         8   /*!< External Interrupt Mode with Falling edge trigger detection         */
#define  GPIO_MODE_IT_RFT        9  /*!< External Interrupt Mode with Rising/Falling edge trigger detection  */

/* GPIO Pin Speed */

#define GPIO_SPEED_LOW 					0x02
#define GPIO_SPEED_MEDIUM 			0x01
#define GPIO_SPEED_FAST 				0x03

/* GPIO Push Pull*/

#define GPIO_NOPULL 0
#define GPIO_PULLUP 1
#define GPIO_PULLDOWN 2
/* GPIO Clock Register Low and High */

#define GPIO_CR_ANALOG 				0x00
#define GPIO_CR_FLOAT_INPUT 	0x04	
#define GPIO_CR_INPUT_PUPD 		0x08
#define GPIO_CR_RESERVED 			0x0C
#define GPIO_CR_GP_OUTPUT_PP	0x00
#define GPIO_CR_GP_OUTPUT_OD  0x04
#define GPIO_CR_AF_OUTPUT_PP  0x08
#define GPIO_CR_AF_OUTPUT_OD  0x0C

void GPIO_PeripClockControl(GPIO_RegDef *pGPIOx , uint8_t EnorDi) ;
/* gpio init and deinit apis */
void GPIO_Initialize(GPIO_Handle* tempGPIOHandle) ;
void GPIO_DeInitialize(GPIO_RegDef *tempGPIOx ) ;

/* gpio read and write to port or pin (or you can config register right into main if you want :D)*/
uint32_t GPIO_ReadFromInputPin(GPIO_RegDef *tempGPIOx , uint8_t PinNumber) ;
uint32_t GPIO_ReadFromInputPort(GPIO_RegDef *tempGPIOx ) ;
void GPIO_WriteToOutputPin(GPIO_RegDef *tempGPIOx , uint8_t PinNumber , uint32_t Value) ;
void GPIO_WriteToOutputPort(GPIO_RegDef *tempGPIOx ,uint32_t Value ) ;
void GPIO_ToggleOutputPin(GPIO_RegDef *tempGPIOx , uint8_t PinNumber ) ;

/* gpio IRQ config and handling */
void GPIO_IRQConfig(uint8_t IRQ_Number  , uint8_t EnorDi) ;
void GPIO_ExternalHandling(uint8_t PinNumber);
void GPIO_IRQ_PriorityConfig(uint8_t IRQ_Number , uint32_t Interrupt_Prority);

#endif /* STM32F103XX_GPIO_DRIVER_ */
