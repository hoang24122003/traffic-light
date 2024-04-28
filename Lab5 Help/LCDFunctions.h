#ifndef LCDFunctions_H
#define LCDFunctions_H
/* This is LCD Library Header. Thanks so much to srisurya97*/
#include "stm32f103xx.h"


#define LCDD0PIN 12					//LCD PIN D0
#define LCDD0PORT GPIOB_Macro
#define LCDD1PIN 13					//LCD PIN D1
#define LCDD1PORT GPIOB_Macro
#define LCDD2PIN 14					//LCD PIN D2
#define LCDD2PORT GPIOB_Macro
#define LCDD3PIN 15					//LCD PIN D3
#define LCDD3PORT GPIOB_Macro
#define LCDD4PIN 0 					//LCD PIN D4
#define LCDD4PORT GPIOA_Macro
#define LCDD5PIN 1					//LCD PIN D5
#define LCDD5PORT GPIOA_Macro
#define LCDD6PIN 2					//LCD PIN D6
#define LCDD6PORT GPIOA_Macro
#define LCDD7PIN 3					//LCD PIN D7
#define LCDD7PORT GPIOA_Macro
#define LCDRSPIN 4					//LCD PIN Command/Data Pin
#define LCDRSPORT GPIOA_Macro
#define LCDRWPIN 10					//LCD PIN Read/Write mode
#define LCDRWPORT GPIOA_Macro
#define LCDEnablePIN  11	//LCD PIN Enable pin
#define LCDEnablePORT GPIOA_Macro
#define DelayBeforeEnable 10 
#define DelayAfterEnable 30



void NotExactDelay(int delay);
void SetPinandPortForOutputPushPull(GPIO_RegDef *port, int pinnumber);
void InitializingPortsForLCD(void);
void SendBitToPortandPin(GPIO_RegDef *port, int pinnumber, uint8_t bitstate);
void LCDEnable(void);
void LCDSetToWrite(void);
void LCDSetToRead(void);
void LCDCommandMode(void);
void LCDCharacterMode(void);
void LCDByte(uint8_t character);
void LCDSendCharacter(char character);
void LCDSendCommand(uint8_t command);    
void LCDClear(void);
void LCDBegin(void);
void LCDSendString(char *stringofcharacters);
void LCDSendInteger(uint32_t Integer ,uint8_t MaxLengthOfString);
void LCDSendFloat(float floatnumber ,uint8_t MaxLengthOfString);
void LCDCursorPositionBitCheck(void);
void LCDSetCursorPosition(int X, int Y);
//

#endif

