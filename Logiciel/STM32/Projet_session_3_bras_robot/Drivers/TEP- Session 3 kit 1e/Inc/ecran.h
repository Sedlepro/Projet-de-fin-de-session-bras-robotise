#ifndef _ECRAN_H
#define _ECRAN_H

#include "main.h"

//Defines
#define PACMAN 0x0E, 0x1F, 0x1C, 0x18, 0x1C, 0x1F, 0x0E, 0x00

//Functions
void LCD_Init(void);
void LCD_Char(uint8_t);
void LCD_command(uint8_t data);
void LCD_String(uint8_t message[]);
void LCD_Clear(void);
#endif /*_ECRAN_H*/
