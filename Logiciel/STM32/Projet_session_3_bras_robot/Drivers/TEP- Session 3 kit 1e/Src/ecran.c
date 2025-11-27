#include "main.h"
#include "stm32f1xx_hal.h"
#include "ecran.h"

void LCD_Mode(uint8_t rs, uint8_t rw);
void LCD_write4bits(uint8_t data);
void LCD_CustomChar(uint8_t CGram_adress, uint8_t logo[8]);

void LCD_Init(void)
{
	HAL_Delay(50);
	LCD_Mode(0, 0);
	LCD_write4bits(0x03);
	HAL_Delay(5);
	LCD_write4bits(0x03);
	HAL_Delay(5);
	LCD_write4bits(0x03);
	HAL_Delay(1);
	LCD_write4bits(0x02);

	LCD_command(0x28);
	LCD_command(0x0F);
	LCD_command(0x01);
	HAL_Delay(3);
	LCD_command(0x06);
	HAL_Delay(10);

	uint8_t pacman[8] = {0x00, 0x1F, 0x1C, 0x18, 0x1C, 0x1F, 0x0E, 0x00};
	LCD_CustomChar(0x48, pacman);

	HAL_Delay(10);

	return;
}

void LCD_Mode(uint8_t rs, uint8_t rw)
{
	// RS	Register Select	Choisit le registre cible (0 = commande, 1 = DDRAM)
	// RW	Read / Write	Choisit le sens du transfert (0 = ecriture, 1 = lecture)

	HAL_GPIO_WritePin(screen_rs_GPIO_Port, screen_rs_Pin, rs);
	HAL_GPIO_WritePin(screen_r_w_GPIO_Port, screen_r_w_Pin, rw);

	return;
}

void LCD_write4bits(uint8_t data)
{
	HAL_GPIO_WritePin(screen_d4_GPIO_Port, screen_d4_Pin, (data & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(screen_d5_GPIO_Port, screen_d5_Pin, (data & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(screen_d6_GPIO_Port, screen_d6_Pin, (data & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(screen_d7_GPIO_Port, screen_d7_Pin, (data & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);

	HAL_GPIO_WritePin(screen_en_GPIO_Port, screen_en_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(screen_en_GPIO_Port, screen_en_Pin, GPIO_PIN_RESET);

	return;
}

void LCD_command(uint8_t data)
{
	LCD_Mode(0, 0);
	LCD_write4bits(data >> 4);
	LCD_write4bits(data);

	return;
}

void LCD_Char(uint8_t data)
{
	LCD_Mode(1, 0);
	LCD_write4bits(data >> 4);
	LCD_write4bits(data & 0x0F);

	return;
}

void LCD_String(uint8_t message[])
{
	for (uint16_t i = 0; message[i] != 0x00; ++i)
	{
		LCD_Char(message[i]);
		HAL_Delay(1);
	}
}

void LCD_CustomChar(uint8_t CGram_adress, uint8_t logo[8])
{
	LCD_command(CGram_adress);

	for (uint8_t i = 0; i < 8; i++) {
		LCD_Char(logo[i]);
		HAL_Delay(1);
	}

	LCD_command(0x80);

	return;
}
