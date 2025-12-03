#ifndef _DISPLAY_H
#define _DISPLAY_H

#include "main.h"

void LCD_PrintDec(uint16_t v);
void LCD_PrintHex(uint8_t v);
void LCD_PrintBloc(uint8_t blocState);
void LCD_UpdateDisplay(
        uint16_t Moteur1, uint16_t Moteur2, uint16_t Moteur3, uint16_t Moteur4, uint16_t Moteur5,
        uint8_t  TableauX, uint8_t  TableauY, uint8_t  Pince, uint8_t  Balance,
        uint8_t  Bloc,             // bloc state 0–3
        uint8_t  Increment, uint8_t Sequence,    // 0–10
        uint8_t  Step, uint8_t V14                  // 0 or 1 → OffL / OnL
    );
void LCD_PrintDec_1Dig(uint8_t v);



#endif /*_DISPLAY_H*/
