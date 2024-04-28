#include <stdio.h>
#include <stdint.h>
#include "stm32f103xx.h"
#include <string.h>
#include "LCDFunctions.h"
/* All States Definition */
#define GoS 0
#define WaitS 1
#define StopS 2
#define GoW 3
#define WaitW 4
#define StopW 5
#define	WalkG 6
#define On1 7
#define Off1 8
#define On2 9
#define Off2 10
#define WalkR 11
#define StopAll 12
/* State Definitions */
struct State{
	uint32_t OutTraffic;
	uint32_t timemili;
	uint8_t Next[8];
};
typedef const struct State TempState;
/* FSM All states */
const static TempState FSM[13]={
	/*goS*/
	{0xA01, 10000, {WaitS, WaitS, GoS, WaitS, WaitS, WaitS, WaitS, WaitS}},
	/*waitS*/
	{0xA02, 5000, {StopS, StopS, StopS, StopS, StopS, StopS, StopS, StopS}},
	/*stopS*/
	{0xA20, 100, {StopAll, GoW, GoS, GoW, WalkG, GoW, WalkG, GoW}},
	/*goW*/
	{0x860, 10000, {WaitW, GoW, WaitW, WaitW, WaitW, WaitW, WaitW, WaitW}},
	/*waitW*/
	{0x920, 5000, {StopW, StopW, StopW, StopW, StopW, StopW, StopW, StopW}},
	/*stopW*/
	{0xA20, 100, {StopAll, GoW, GoS, GoS, WalkG, WalkG, GoS, WalkG}},
	/*walkG*/
	{0x620, 10000, {On1, On1, On1, On1, WalkG, On1, On1, On1}},
	/*on1*/
	{0xA20, 1000, {Off1, Off1, Off1, Off1, Off1, Off1, Off1, Off1}},
	/*off1*/
	{0x220, 1000, {On2, On2, On2, On2, On2, On2, On2, On2}},
	/*on2*/
	{0xA20, 1000, {Off2, Off2, Off2, Off2, Off2, Off2, Off2, Off2}},
	/*off2*/
	{0x220, 1000, {WalkR, WalkR, WalkR, WalkR, WalkR, WalkR, WalkR, WalkR}},
	/*walkR*/
	{0xA20, 100, {StopAll, GoW, GoS, GoS, WalkG, GoW, GoS, GoS}},
	/*StopALL*/
	{0xA20, 100, {StopAll, GoW, GoS, GoS, WalkG, GoW, GoS, GoS}}
};
void GPIO_Configuration(void);
void DelayMilisec(uint32_t temptime);
void EXTI9_5_IRQHandler(void);
/* Variables For Flags */
static uint32_t Input = 0x00;
static uint32_t BeforeInput = 0x00;
/* Counter To Export To LCD */
static uint32_t Counter = 0;
/* Variables For Checking Led Status */
static uint32_t GreenSouth;
static uint32_t GreenWest;
static uint32_t GreenWalk;
static uint32_t AllRed;
/* main function */
int main(void){
	/* Intialize all Components */
	GPIO_Configuration();
	uint8_t n = StopAll;
	LCDBegin();
	LCDSetCursorPosition(0,0);
	/* loop */
	while(1){
		/* checking led status */
		AllRed = (FSM[n].OutTraffic);
		GreenSouth = (FSM[n].OutTraffic & 0x01);
		GreenWest = (FSM[n].OutTraffic & 0x40)>>6;
		GreenWalk = (FSM[n].OutTraffic & 0x400)>>10;
		/* Tracking Changes */
		BeforeInput = Input;
		/* Output */
		GPIOB_Macro->ODR = FSM[n].OutTraffic;
		/* Delay */
		DelayMilisec(FSM[n].timemili);
		/* Get next states */
		n = FSM[n].Next[Input];
	}
}

void GPIO_Configuration(void)
{
	/* Enables Clock */
	GPIO_PeripClockControl(GPIOB_Macro, ENABLES);
	GPIO_PeripClockControl(GPIOA_Macro, ENABLES);
  GPIO_Handle GPIO_LedTraffic;
	GPIO_LedTraffic.pGPIOx = GPIOB_Macro;
  /*Configure GPIO pins : PB0 PB1 PB5 PB6 PB8 PB9 PB10 PB11 */
  GPIO_LedTraffic.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_0;
  GPIO_LedTraffic.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
  GPIO_LedTraffic.GPIO_PinConfig.GPIO_PinPull = GPIO_PULLDOWN;
	GPIO_LedTraffic.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
  GPIO_Initialize(&GPIO_LedTraffic);
	
	GPIO_LedTraffic.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_1;
  GPIO_LedTraffic.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
  GPIO_LedTraffic.GPIO_PinConfig.GPIO_PinPull = GPIO_PULLDOWN;
	GPIO_LedTraffic.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
  GPIO_Initialize(&GPIO_LedTraffic);
	
	GPIO_LedTraffic.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_5;
  GPIO_LedTraffic.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
  GPIO_LedTraffic.GPIO_PinConfig.GPIO_PinPull = GPIO_PULLDOWN;
	GPIO_LedTraffic.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
  GPIO_Initialize(&GPIO_LedTraffic);
	
	GPIO_LedTraffic.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_6;
  GPIO_LedTraffic.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
  GPIO_LedTraffic.GPIO_PinConfig.GPIO_PinPull = GPIO_PULLDOWN;
	GPIO_LedTraffic.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
  GPIO_Initialize(&GPIO_LedTraffic);
	
	GPIO_LedTraffic.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_8;
  GPIO_LedTraffic.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
  GPIO_LedTraffic.GPIO_PinConfig.GPIO_PinPull = GPIO_PULLDOWN;
	GPIO_LedTraffic.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIO_Initialize(&GPIO_LedTraffic);
	
	GPIO_LedTraffic.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_9;
  GPIO_LedTraffic.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
  GPIO_LedTraffic.GPIO_PinConfig.GPIO_PinPull = GPIO_PULLDOWN;
	GPIO_LedTraffic.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIO_Initialize(&GPIO_LedTraffic);

	GPIO_LedTraffic.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_10;
  GPIO_LedTraffic.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
  GPIO_LedTraffic.GPIO_PinConfig.GPIO_PinPull = GPIO_PULLDOWN;
	GPIO_LedTraffic.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIO_Initialize(&GPIO_LedTraffic);
	
	GPIO_LedTraffic.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_11;
  GPIO_LedTraffic.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
  GPIO_LedTraffic.GPIO_PinConfig.GPIO_PinPull = GPIO_PULLDOWN;
	GPIO_LedTraffic.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIO_Initialize(&GPIO_LedTraffic);
	
	/*Configure GPIO pins : PA5 PA6 PA7 */
	GPIO_Handle GPIO_Button;
  GPIO_Button.pGPIOx = GPIOA_Macro;
  GPIO_Button.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_5;
  GPIO_Button.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_RFT;
  GPIO_Button.GPIO_PinConfig.GPIO_PinPull = GPIO_PULLDOWN;
	GPIO_Button.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
  GPIO_Initialize(&GPIO_Button);
	
	GPIO_Button.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_6;
  GPIO_Button.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_RFT;
  GPIO_Button.GPIO_PinConfig.GPIO_PinPull = GPIO_PULLDOWN;
	GPIO_Button.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
  GPIO_Initialize(&GPIO_Button);
	
	GPIO_Button.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_7;
  GPIO_Button.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_RFT;
  GPIO_Button.GPIO_PinConfig.GPIO_PinPull = GPIO_PULLDOWN;
	GPIO_Button.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
  GPIO_Initialize(&GPIO_Button);
	/* Enable Interrupt from PA5 to PA9*/
	GPIO_IRQConfig(IRQ_NO_EXTI9_5, ENABLES);
	GPIO_IRQ_PriorityConfig(IRQ_NO_EXTI9_5, NVIC_IRQ_PRI15);
}
/* Interupt Request Goes Here */
void EXTI9_5_IRQHandler(void){
	GPIO_ExternalHandling(GPIO_PIN_5);
	GPIO_ExternalHandling(GPIO_PIN_6);
	GPIO_ExternalHandling(GPIO_PIN_7);
	/* Get New Flag */
	Input = (GPIOA_Macro->IDR >> 5) & 0x07;
}
/* Delay and Counter */
void DelayMilisec(uint32_t temptime){
	/* Checking Led Status */
	if(!(GreenSouth||GreenWalk||GreenWest))
		Counter = 0;
	volatile uint32_t i;
	/* Delay */
	for(i = 1; i <= 5*temptime;i++){
		/* Set LCD Cursor and show up */
		LCDSetCursorPosition(0,0);
		LCDSendInteger(Counter, 1);
		/* Changes Was Made */
		if(Input != BeforeInput && ((GreenSouth)||GreenWalk||GreenWest) && (Counter > 10)){
			LCDSetCursorPosition(0,0);
			LCDSendString("00");
			break;
		}
		/* Set Counter stable when lights are red */
		if(AllRed == 0xA20)
				Counter = 0;
		/* Counting Every Seconds */
		if(i % 5000 == 0){
			Counter++;
		}
	}
}
