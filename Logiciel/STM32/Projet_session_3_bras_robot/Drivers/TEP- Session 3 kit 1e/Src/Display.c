
#include "ecran.h"

void LCD_PrintDec_1Dig(uint8_t v)
{
	uint8_t b[2];       // one digit + null

    if (v > 9)
        v = 9;       // clamp

    b[0] = '0' + v;  // convert digit
    b[1] = '\0';     // terminate

    LCD_String(b);
}

void LCD_PrintDec(uint8_t v)
{
	uint8_t b[3];   // two digits + null

    if (v > 99)
        v = 99;  // clamp if needed

    b[0] = '0' + (v / 10);  // dizaines
    b[1] = '0' + (v % 10);  // unités
    b[2] = '\0';

    LCD_String(b);
}


void LCD_PrintHex(uint8_t v)
{
	uint8_t hex[3];   // "AB" + null

    uint8_t high = (v >> 4) & 0x0F;
    uint8_t low  = v & 0x0F;

    hex[0] = (high < 10) ? ('0' + high) : ('A' + (high - 10));
    hex[1] = (low  < 10) ? ('0' + low)  : ('A' + (low  - 10));
    hex[2] = '\0';

    LCD_String(hex);
}

// -------------------------------------------------------------
// Helper: print 2-letter BLOC mode
// -------------------------------------------------------------
void LCD_PrintBloc(uint8_t blocState)
{
    switch(blocState)
    {
        case 1: LCD_String("Pe"); break;
        case 2: LCD_String("Mo"); break;
        case 3: LCD_String("Gr"); break;
        default: LCD_String("--"); break;
    }
}

// -------------------------------------------------------------
// MAIN LCD FORMAT DISPLAY
// -------------------------------------------------------------
void LCD_UpdateDisplay(
        uint16_t Moteur1, uint16_t Moteur2, uint16_t Moteur3, uint16_t Moteur4, uint16_t Moteur5,
        uint8_t  TableauX, uint8_t  TableauY, uint8_t  Pince, uint8_t  Balance,
        uint8_t  Bloc,             // bloc state 0–3
        uint8_t  Increment, uint8_t Sequence,    // 0–10
        uint8_t  Step, uint8_t État_Communication                  // 0 or 1 → OffL / OnL
    )
{
    LCD_Clear();

    // ---------------- LINE 1 ----------------
    LCD_command(0x80);    // pos(0,0)
    LCD_String(" 1:"); LCD_PrintHex(Moteur1);  LCD_Char(' ');
    LCD_String(" 2:"); LCD_PrintHex(Moteur2); LCD_Char(' ');
    LCD_String(" 3:"); LCD_PrintHex(Moteur3); LCD_Char(' ');
    LCD_String(" 4:"); LCD_PrintHex(Moteur4);



    // ---------------- LINE 2 ----------------
    LCD_command(0xC0);    // pos(1,0)
    LCD_String(" 5:"); LCD_PrintHex(Moteur5); LCD_Char(' ');
    LCD_String(" X:"); LCD_PrintHex(TableauX); LCD_Char(' ');
    LCD_String(" Y:"); LCD_PrintHex(TableauY); LCD_Char(' ');
    LCD_String(" P:"); LCD_PrintHex(Pince);

    // ---------------- LINE 3 ----------------
    LCD_command(0x94);    // pos(2,0)
    LCD_String(" B:"); LCD_PrintHex(Balance); LCD_Char(' ');
    LCD_String(" Bloc:");
    LCD_PrintBloc(Bloc);

    // ---------------- LINE 4 ----------------
    LCD_command(0xD4);    // pos(3,0)
    LCD_PrintHex(Increment); LCD_Char(' ');
    LCD_String(" Seq:"); LCD_PrintDec_1Dig(Sequence); LCD_Char(' ');
    LCD_String(" Step:"); LCD_PrintDec(Step); LCD_Char(' ');
    if (État_Communication) LCD_String(" OnL");
    else     LCD_String(" OffL");
}
