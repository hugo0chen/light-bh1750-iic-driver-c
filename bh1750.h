#ifndef _BH1750_H
#define _BH1750_H
#include "stm32l1xx.h"

#define BH1750_Addr 0x46
#define BH1750_ON   0x01
#define BH1750_CON  0x10
#define BH1750_ONE  0x20
#define BH1750_RSET 0x07

void Init_BH1750(void);	
void Cmd_Write_BH1750(uint8_t cmd);
void Start_BH1750(void);			
uint16_t Read_BH1750(void);                           
float Convert_BH1750(uint16_t light_value);


#endif
