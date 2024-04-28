/* This is belonged to Bui Manh Huy - 20213707
Main Use: Creating Function For GPIO Port
All Rights Reserved */

#include "stm32f103xx_gpio_driver.h"
/* Setting Clocks For GPIO Port */
void GPIO_PeripClockControl(GPIO_RegDef *tempGPIOx , uint8_t EnorDi) {

	if(EnorDi == ENABLES){

		if (tempGPIOx == GPIOA_Macro) {
			GPIOA_CLOCK_ENABLE();
		}else if (tempGPIOx == GPIOB_Macro) {
			GPIOB_CLOCK_ENABLE();
		}else if (tempGPIOx == GPIOC_Macro){
			GPIOC_CLOCK_ENABLE();
		}else if (tempGPIOx == GPIOD_Macro){
			GPIOD_CLOCK_ENABLE();
		}
	}else{
		if (tempGPIOx == GPIOA_Macro) {
			GPIOA_CLOCK_DISABLE();
		}else if (tempGPIOx == GPIOB_Macro) {
			GPIOB_CLOCK_DISABLE();
		}else if (tempGPIOx == GPIOC_Macro){
			GPIOC_CLOCK_DISABLE();
		}else if (tempGPIOx == GPIOD_Macro){
			GPIOD_CLOCK_DISABLE();
		}
	}
}
/* Starting & Configuring GPIO Pin (I'm Lazy To Explain Everything in this :D)*/
void GPIO_Initialize(GPIO_Handle* tempGPIOHandle){
	uint32_t temp;
	uint32_t tmp1;
	uint32_t tmp2;
	tmp1 = (tempGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber)/8;
	tmp2 = (tempGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber)%8;
	if((tempGPIOHandle->GPIO_PinConfig.GPIO_PinMode)==GPIO_MODE_OUTPUT_PP){
		temp = ((tempGPIOHandle -> GPIO_PinConfig.GPIO_PinSpeed) + (GPIO_CR_GP_OUTPUT_PP)) << (4 * tmp2) ;
		if(tmp1 == 0){
			tempGPIOHandle -> pGPIOx -> CRL &= (~((0xF) << (4 * tmp2)));
			tempGPIOHandle -> pGPIOx -> CRL |= temp;
		}else{
			tempGPIOHandle -> pGPIOx -> CRH &= (~((0xF) << (4 * tmp2)));
			tempGPIOHandle -> pGPIOx -> CRH |= temp;
		}
	}else if((tempGPIOHandle->GPIO_PinConfig.GPIO_PinMode)==GPIO_MODE_OUTPUT_OD){
		temp = ((tempGPIOHandle -> GPIO_PinConfig.GPIO_PinSpeed) + (GPIO_CR_GP_OUTPUT_OD)) << (4 * tmp2) ;
		if(tmp1 == 0){
			tempGPIOHandle -> pGPIOx -> CRL &= (~((0xF) << (4 * tmp2)));
			tempGPIOHandle -> pGPIOx -> CRL |= temp;
		}else{
			tempGPIOHandle -> pGPIOx -> CRH &= (~((0xF) << (4 * tmp2)));
			tempGPIOHandle -> pGPIOx -> CRH |= temp;
		}
	}else if((tempGPIOHandle->GPIO_PinConfig.GPIO_PinMode)==GPIO_MODE_AF_PP){
		temp = ((tempGPIOHandle -> GPIO_PinConfig.GPIO_PinSpeed) + (GPIO_CR_AF_OUTPUT_PP)) << (4 * tmp2) ;
		if(tmp1 == 0){
			tempGPIOHandle -> pGPIOx -> CRL &= (~((0xF) << (4 * tmp2)));
			tempGPIOHandle -> pGPIOx -> CRL |= temp;
		}else{
			tempGPIOHandle -> pGPIOx -> CRH &= (~((0xF) << (4 * tmp2)));
			tempGPIOHandle -> pGPIOx -> CRH |= temp;
		}
	}else if((tempGPIOHandle->GPIO_PinConfig.GPIO_PinMode)==GPIO_MODE_AF_OD){
		temp = ((tempGPIOHandle -> GPIO_PinConfig.GPIO_PinSpeed) + (GPIO_CR_AF_OUTPUT_OD)) << (4 * tmp2) ;
		if(tmp1 == 0){
			tempGPIOHandle -> pGPIOx -> CRL &= (~((0xF) << (4 * tmp2)));
			tempGPIOHandle -> pGPIOx -> CRL |= temp;
		}else{
			tempGPIOHandle -> pGPIOx -> CRH &= (~((0xF) << (4 * tmp2)));
			tempGPIOHandle -> pGPIOx -> CRH |= temp;
		}
	}else if((tempGPIOHandle->GPIO_PinConfig.GPIO_PinMode)==GPIO_MODE_INPUT ||(tempGPIOHandle->GPIO_PinConfig.GPIO_PinMode)==GPIO_MODE_AF_INPUT){
		if((tempGPIOHandle->GPIO_PinConfig.GPIO_PinPull)==GPIO_NOPULL){
			temp = (GPIO_CR_FLOAT_INPUT << (4*tmp2));
		if(tmp1 == 0){
			tempGPIOHandle -> pGPIOx -> CRL &= (~((0xF) << (4 * tmp2)));
			tempGPIOHandle -> pGPIOx -> CRL |= temp;
		}else{
			tempGPIOHandle -> pGPIOx -> CRH &= (~((0xF) << (4 * tmp2)));
			tempGPIOHandle -> pGPIOx -> CRH |= temp;
		}
	}else if((tempGPIOHandle->GPIO_PinConfig.GPIO_PinPull)==GPIO_PULLUP){
		temp = (GPIO_CR_INPUT_PUPD << (4*tmp2));
		if(tmp1 == 0){
			tempGPIOHandle -> pGPIOx -> CRL &= (~((0xF) << (4 * tmp2)));
			tempGPIOHandle -> pGPIOx -> CRL |= temp;
		}else{
			tempGPIOHandle -> pGPIOx -> CRH &= (~((0xF) << (4 * tmp2)));
			tempGPIOHandle -> pGPIOx -> CRH |= temp;
		}
		tempGPIOHandle->pGPIOx->BSRR |= (SETS << tempGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	}else if((tempGPIOHandle->GPIO_PinConfig.GPIO_PinPull)==GPIO_PULLDOWN){
		temp = (GPIO_CR_INPUT_PUPD << (4*tmp2));
		if(tmp1 == 0){
			tempGPIOHandle -> pGPIOx -> CRL &= (~((0xF) << (4 * tmp2)));
			tempGPIOHandle -> pGPIOx -> CRL |= temp;
		}else{
			tempGPIOHandle -> pGPIOx -> CRH &= (~((0xF) << (4 * tmp2)));
			tempGPIOHandle -> pGPIOx -> CRH |= temp;
		}
		tempGPIOHandle->pGPIOx->BSRR |= (SETS << (16+tempGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	}
	}else if(((tempGPIOHandle->GPIO_PinConfig.GPIO_PinMode)==GPIO_MODE_IT_FT )||((tempGPIOHandle->GPIO_PinConfig.GPIO_PinMode)==GPIO_MODE_IT_RFT)||((tempGPIOHandle->GPIO_PinConfig.GPIO_PinMode)==GPIO_MODE_IT_RT)){
		if((tempGPIOHandle->GPIO_PinConfig.GPIO_PinMode) ==GPIO_MODE_IT_FT){
			EXTI->FTSR |= (1 << tempGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->RTSR &= ~(1 << tempGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}else if((tempGPIOHandle->GPIO_PinConfig.GPIO_PinMode) ==GPIO_MODE_IT_RT){
			EXTI->FTSR &= ~(1 << tempGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->RTSR |= (1 << tempGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}else if((tempGPIOHandle->GPIO_PinConfig.GPIO_PinMode) ==GPIO_MODE_IT_RFT){
			EXTI->FTSR |= (1 << tempGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->RTSR |= (1 << tempGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		uint8_t temp1 = tempGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4  ;
		uint8_t temp2 = tempGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4  ;
		uint8_t code = (GPIO_BASEADDR_TO_CODE(tempGPIOHandle->pGPIOx)) ;
		/* Clock enable for external interrupts */
		AFIO_PCLK_EN();
		if(temp1 == 0)
			AFIO->EXTICR1 |= (code << ( temp2 * 4) );
		else if(temp1 == 1)
			AFIO->EXTICR2 |= (code << ( temp2 * 4) );
		else if(temp1 == 2)
			AFIO->EXTICR3 |= (code << ( temp2 * 4) );
		else if(temp1 == 3)
			AFIO->EXTICR4 |= (code << ( temp2 * 4) );
			/* enable the interrupt delivery in exti */
			EXTI->IMR |= (1 << tempGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		if((tempGPIOHandle->GPIO_PinConfig.GPIO_PinPull)==GPIO_NOPULL){
			temp= (GPIO_CR_FLOAT_INPUT << (4*tmp2));
		if(tmp1 == 0){
			tempGPIOHandle -> pGPIOx -> CRL &= (~((0xF) << (4 * tmp2)));
			tempGPIOHandle -> pGPIOx -> CRL |= temp;
		}else{
			tempGPIOHandle -> pGPIOx -> CRH &= (~((0xF) << (4 * tmp2)));
			tempGPIOHandle -> pGPIOx -> CRH |= temp;
		}
	}else if((tempGPIOHandle->GPIO_PinConfig.GPIO_PinPull)==GPIO_PULLUP){
		temp = (GPIO_CR_INPUT_PUPD << (4*tmp2));
		if(tmp1 == 0){
			tempGPIOHandle -> pGPIOx -> CRL &= (~((0xF) << (4 * tmp2)));
			tempGPIOHandle -> pGPIOx -> CRL |= temp;
		}else{
			tempGPIOHandle -> pGPIOx -> CRH &= (~((0xF) << (4 * tmp2)));
			tempGPIOHandle -> pGPIOx -> CRH |= temp;
		}
		tempGPIOHandle->pGPIOx->BSRR |= (SETS << tempGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	}else if((tempGPIOHandle->GPIO_PinConfig.GPIO_PinPull)==GPIO_PULLDOWN){
		temp = (GPIO_CR_INPUT_PUPD << (4*tmp2));
		if(tmp1 == 0){
			tempGPIOHandle -> pGPIOx -> CRL &= (~((0xF) << (4 * tmp2)));
			tempGPIOHandle -> pGPIOx -> CRL |= temp;
		}else{
			tempGPIOHandle -> pGPIOx -> CRH &= (~((0xF) << (4 * tmp2)));
			tempGPIOHandle -> pGPIOx -> CRH |= temp;
		}
		tempGPIOHandle->pGPIOx->BSRR |= (SETS << (16+tempGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		}
	}else if (tempGPIOHandle -> GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ANALOG)
	{
		temp = GPIO_CR_ANALOG + GPIO_CR_ANALOG;
	}
}
/* Disable GPIO Port*/
void GPIO_DeInitialize(GPIO_RegDef *tempGPIOx ) {
	if (tempGPIOx == GPIOA_Macro) {
		GPIOA_REG_RESET();
	} else if (tempGPIOx == GPIOB_Macro){
		GPIOB_REG_RESET();
	}else if (tempGPIOx == GPIOC_Macro){
		GPIOC_REG_RESET();
	}else if (tempGPIOx == GPIOD_Macro){
		GPIOD_REG_RESET();
	}
}
/* gpio read and write to port or pin */
uint32_t GPIO_ReadFromInputPin(GPIO_RegDef *tempGPIOx , uint8_t PinNumber){
	uint32_t value;
	value = ( ((tempGPIOx -> IDR) >> PinNumber) & 0x00000001 );
	return value;
}

uint32_t GPIO_ReadFromInputPort(GPIO_RegDef *tempGPIOx ){
	uint32_t value;
	value = (tempGPIOx->IDR);
	return value;
}
void GPIO_WriteToOutputPin(GPIO_RegDef *tempGPIOx , uint8_t PinNumber , uint32_t Value){
	if (Value == GPIO_PIN_SET) 
	{
		tempGPIOx -> ODR |= ( 1 << PinNumber );
	}else 
	{
		tempGPIOx -> ODR &= ~( 1 << PinNumber );
	}
}
void GPIO_WriteToOutputPort(GPIO_RegDef *tempGPIOx ,uint32_t Value ) {
	tempGPIOx->ODR = Value;
}
void GPIO_ToggleOutputPin(GPIO_RegDef *tempGPIOx , uint8_t PinNumber ) {
	tempGPIOx->ODR  ^= ( 1 << PinNumber);
}

/* gpio IRQ config and handling */
void GPIO_IRQConfig(uint8_t IRQ_Number  , uint8_t EnorD) {
	if (EnorD == ENABLES)
	{
		if (IRQ_Number <= 31)
		{
			*NVIC_ISER0 |= ( 1 << IRQ_Number);
		}
		else if (IRQ_Number >= 32 && IRQ_Number < 64)
		{
			*NVIC_ISER1 |= ( 1 << (IRQ_Number % 32));
		}
		else if (IRQ_Number >= 64 && IRQ_Number <=80){
			*NVIC_ISER2 |= ( 1 << (IRQ_Number % 64));
		}
	}
	else
	{
		if (IRQ_Number <= 31)
		{
			*NVIC_ICER0 |= ( 1 << IRQ_Number);
		}
		else if (IRQ_Number >= 32 && IRQ_Number <= 64)
		{
			*NVIC_ICER1 |= ( 1 << (IRQ_Number % 32));
		}
		else if (IRQ_Number >= 64 && IRQ_Number <=80){
			*NVIC_ICER2 |= ( 1 << (IRQ_Number % 64));
		}
	}
}
/* GPIO External Interrupt Processing*/
void GPIO_ExternalHandling(uint8_t PinNumber){
	if (EXTI->PR & (1 << PinNumber)) {
		/* clear the pr register and clear the interrupt */
		EXTI->PR |= (1 << PinNumber) ;
	}
}
/* Setting Priority Config */
void GPIO_IRQ_PriorityConfig(uint8_t IRQ_Number , uint32_t Interrupt_Prority){
	uint8_t iprx = IRQ_Number/4;
	uint8_t iprx_sector = IRQ_Number % 4;
	uint8_t shift_amount = ( 8 * iprx_sector) + NO_PR_BITS_IMPLEMENTED;
	*(NVIC_IPR_BASE + iprx ) |= (Interrupt_Prority << shift_amount);
}
