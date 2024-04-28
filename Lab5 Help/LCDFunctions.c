#include "LCDFunctions.h"

#include <stdio.h>
#include "stm32f103xx.h"
/* This is LCD Library Function. Thanks so much to srisurya97*/
///////////////////////////////////////////////////////////////////
//Pinnumber address in mode config port
uint16_t pinpos[16] = {
	(0x00),
	(0x04),
	(0x08),
	(0x0C),
	(0x10),
	(0x14),
	(0x18),
	(0x1C),
	(0x00),
	(0x04),
	(0x08),
	(0x0C),
	(0x10),
	(0x14),
	(0x18),
	(0x1C),
};

///////////////////////////////////////////////////////////////////
void NotExactDelay(int delay)
{
	volatile int i;
	for(i=0; i < delay; i++);
}

///////////////////////////////////////////////////////////////////
void SetPinandPortForOutputPushPull(GPIO_RegDef *port, int pinnumber)
	{
		//Enabling Port Clocks
		if(port == GPIOA_Macro)
			GPIOA_CLOCK_ENABLE();
		if(port == GPIOB_Macro)
			GPIOB_CLOCK_ENABLE();
		if(port == GPIOC_Macro)
			GPIOC_CLOCK_ENABLE();
		
		//output mode and pushpull
		if(pinnumber>8)
			{
				port->CRH |= (1<<pinpos[pinnumber] | 1<<(pinpos[pinnumber]+1));
				port->CRH &= ~(1<<(pinpos[pinnumber]+2) | 1<<(pinpos[pinnumber]+3));
			}
			else
				{
					port->CRL |= (1<<pinpos[pinnumber] | 1<<(pinpos[pinnumber]+1));
					port->CRL &= ~(1<<(pinpos[pinnumber]+2) | 1<<(pinpos[pinnumber]+3));
				}
	} 

///////////////////////////////////////////////////////////////////	
void InitializingPortsForLCD(void)
	{
		SetPinandPortForOutputPushPull(LCDD0PORT, LCDD0PIN);
		SetPinandPortForOutputPushPull(LCDD1PORT, LCDD1PIN);
		SetPinandPortForOutputPushPull(LCDD2PORT, LCDD2PIN);
		SetPinandPortForOutputPushPull(LCDD3PORT, LCDD3PIN);
		SetPinandPortForOutputPushPull(LCDD4PORT, LCDD4PIN);
		SetPinandPortForOutputPushPull(LCDD5PORT, LCDD5PIN);
		SetPinandPortForOutputPushPull(LCDD6PORT, LCDD6PIN);
		SetPinandPortForOutputPushPull(LCDD7PORT, LCDD7PIN);
		SetPinandPortForOutputPushPull(LCDRWPORT, LCDRWPIN);
		SetPinandPortForOutputPushPull(LCDRSPORT, LCDRSPIN);
		SetPinandPortForOutputPushPull(LCDEnablePORT, LCDEnablePIN);
		
	}	
	
///////////////////////////////////////////////////////////////////	
void SendBitToPortandPin(GPIO_RegDef *port, int pinnumber, uint8_t bitstate)
	{
		if(bitstate)
			{
				port->BSRR = 1<<pinnumber;
			}
			else
				{
					port->BRR = 1<<pinnumber;
				}
	}
	
///////////////////////////////////////////////////////////////////
void LCDEnable(void)
	{
		NotExactDelay(1);
		SendBitToPortandPin(LCDEnablePORT, LCDEnablePIN, 1);
	}	

///////////////////////////////////////////////////////////////////	
void LCDSetToWrite(void)
	{
		SendBitToPortandPin(LCDRWPORT, LCDRWPIN, 0);
	}

///////////////////////////////////////////////////////////////////	
void LCDSetToRead(void)
	{
		SendBitToPortandPin(LCDRWPORT, LCDRWPIN, 1);
	}

///////////////////////////////////////////////////////////////////	
void LCDCommandMode(void)
	{
		SendBitToPortandPin(LCDRSPORT ,LCDRSPIN, 0);
		//NotExactDelay(10);
	}

///////////////////////////////////////////////////////////////////	
void LCDCharacterMode(void)
	{
		SendBitToPortandPin(LCDRSPORT ,LCDRSPIN, 1);
	}

///////////////////////////////////////////////////////////////////	
void LCDByte(uint8_t character)
	{
		NotExactDelay(10);
		SendBitToPortandPin(LCDD0PORT, LCDD0PIN, (uint8_t)character & 0x01);
		SendBitToPortandPin(LCDD1PORT, LCDD1PIN, (uint8_t)character & 0x02);
		SendBitToPortandPin(LCDD2PORT, LCDD2PIN, (uint8_t)character & 0x04);
		SendBitToPortandPin(LCDD3PORT, LCDD3PIN, (uint8_t)character & 0x08);
		SendBitToPortandPin(LCDD4PORT, LCDD4PIN, (uint8_t)character & 0x10);
		SendBitToPortandPin(LCDD5PORT, LCDD5PIN, (uint8_t)character & 0x20);
		SendBitToPortandPin(LCDD6PORT, LCDD6PIN, (uint8_t)character & 0x40);
		SendBitToPortandPin(LCDD7PORT, LCDD7PIN, (uint8_t)character & 0x80);
		//NotExactDelay(DelayAfterEnable);
		NotExactDelay(60); //60ns
		SendBitToPortandPin(LCDEnablePORT, LCDEnablePIN,0);
		NotExactDelay(10);
	}	
	
///////////////////////////////////////////////////////////////////	
void LCDSendCharacter(char character)
	{
		LCDSetToWrite();
		LCDCharacterMode();
		LCDEnable();
		LCDByte((uint8_t)character);
		NotExactDelay(200); //200ns
	}

///////////////////////////////////////////////////////////////////
void LCDSendCommand(uint8_t command)
	{
		LCDSetToWrite();
		LCDCommandMode();
		LCDEnable();
		LCDByte(command);
		NotExactDelay(1); //200ns
	}
	
///////////////////////////////////////////////////////////////////	
void LCDClear(void)
	{
		LCDSendCommand(0x01); //Clear Display
		NotExactDelay(100);
	}

///////////////////////////////////////////////////////////////////	
void LCDBegin(void)
	{	
		InitializingPortsForLCD();
		LCDSendCommand(0x0C); //0b00111000 Display ON, Cursor OFF
		LCDSendCommand(0x38); //0b00001110 8-bit Active
		LCDSendCommand(0x06);  //Shift Cursor Right 
		LCDSendCommand(0x80);  //Cursor To 1St Line
		LCDClear();		// display on, cursor off, blinking off
	}	
	
///////////////////////////////////////////////////////////////////
void LCDSendString(char *stringofcharacters)
{
	while(*stringofcharacters)
	{
		LCDSendCharacter(*stringofcharacters++);
	}
}	
	
///////////////////////////////////////////////////////////////////
void LCDSendInteger(uint32_t Integer ,uint8_t MaxLengthOfString)
{
		char StringNumber[MaxLengthOfString];
	if(Integer >= 10)	
	sprintf(StringNumber, "%d", Integer);
	else
		sprintf(StringNumber, "0%d", Integer);
		LCDSendString(StringNumber);
}

///////////////////////////////////////////////////////////////////
void LCDSendFloat(float floatnumber ,uint8_t MaxLengthOfString)
{
		char StringNumber[MaxLengthOfString];
		sprintf(StringNumber, "%f", floatnumber);
		LCDSendString(StringNumber);
}

///////////////////////////////////////////////////////////////////
//    0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
//   64  65  66  67  68  69  70  71  72  73  74  75  76  77  78  79

void LCDCursorPositionBitCheck(void)
	{
		//int i=0;
		for(int Y=0;Y<=1;Y++)
		{
			for(int X=0;X<=16;X++)
			{
							LCDSendCommand(0x80 + X + (Y*64));
							LCDSendCharacter('X');	
							NotExactDelay(3000000);
							LCDClear();
			}
		}
	}

///////////////////////////////////////////////////////////////////	
void LCDSetCursorPosition(int X, int Y)
	{
		if(X <= 16 && Y <= 1)
		{
			LCDSendCommand(0x80 + X + (Y*64));
		}
	}
	
