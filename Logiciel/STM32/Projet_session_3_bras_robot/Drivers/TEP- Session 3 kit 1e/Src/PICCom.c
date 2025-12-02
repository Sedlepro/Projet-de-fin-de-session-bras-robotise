/*
 * PICCom.c
 *
 *  Created on: Nov 26, 2025
 *      Author: Sedrick
 */

#include "PICCom.h"
#include <string.h>
#include "ecran.h"

static UART_HandleTypeDef *PIC_UART = NULL;
static uint8_t rx_byte;
static uint8_t rx_frame[PIC_FRAME_SIZE];
static uint8_t rx_buffer_position = 0;
static PIC_Status_t last_status;
static bool new_status = false;

void PICCom_Init(UART_HandleTypeDef *huart)
{
	PIC_UART = huart;

	rx_buffer_position = 0;
	new_status = false;
	memset(rx_frame, 0, sizeof(rx_frame));
	HAL_UART_Receive_IT(PIC_UART, &rx_byte, 1);
}

void PICCom_RxCallback(UART_HandleTypeDef *huart)
{
	if (huart != PIC_UART) { return; }

	uint8_t byte_val = rx_byte;

	if (rx_buffer_position == 0 && byte_val != PIC_TRAME_START) {
		HAL_UART_Receive_IT(PIC_UART, &rx_byte, 1);
		return;
	}

	if (rx_buffer_position == 1 && byte_val != PIC_TRAME_CONFIRM) {
	    rx_buffer_position = 0;
	    HAL_UART_Receive_IT(PIC_UART, &rx_byte, 1);
	    return;
	}

	rx_frame[rx_buffer_position++] = byte_val;

	if (rx_buffer_position >= PIC_FRAME_SIZE) {
		rx_buffer_position = 0;
	}



	if (rx_frame[0] == PIC_TRAME_START && rx_frame[1] == PIC_TRAME_CONFIRM)
	{
		uint8_t checksum = 0;
		for (uint8_t i = 0;  i < 7; i++) { checksum += rx_frame[i]; }

		if (checksum == rx_frame[7])
		{
			last_status.x       = rx_frame[2];
			last_status.y       = rx_frame[3];
			last_status.pince   = rx_frame[4];
			last_status.balance = rx_frame[5];

			new_status = true;
		}
	}
	HAL_UART_Receive_IT(PIC_UART, &rx_byte, 1);
}

bool PICCom_NewStatus(void)
{
	return new_status;
}

PIC_Status_t PICCom_GetStatus(void)
{
	new_status = false;
	return last_status;
}

HAL_StatusTypeDef PICCom_SendPositions(const Motor_Positions_t *pos)
{
	if ((PIC_UART == NULL) || (pos ==NULL)) { return HAL_ERROR; }

	uint8_t frame_toSend[PIC_FRAME_SIZE];

	frame_toSend[0] = PIC_TRAME_START;
	frame_toSend[1] = PIC_TRAME_CONFIRM;

	frame_toSend[2] = pos->motor0;
	frame_toSend[3] = pos->motor1;
	frame_toSend[4] = pos->motor2;
	frame_toSend[5] = pos->motor3;
	frame_toSend[6] = pos->motor4;

	uint8_t checksum = 0;
	for (uint8_t i = 0; i < 7; i++) { checksum += frame_toSend[i]; }

	frame_toSend[7] = checksum;

	return HAL_UART_Transmit(PIC_UART, frame_toSend, PIC_FRAME_SIZE, 10);
}
