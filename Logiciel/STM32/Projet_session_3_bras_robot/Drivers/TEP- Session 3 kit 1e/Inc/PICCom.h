/*
 * PICCom.h
 *
 *  Created on: Nov 26, 2025
 *      Author: Sedrick
 */

#ifndef TEP__SESSION_3_KIT_1E_INC_PICCOM_H_
#define TEP__SESSION_3_KIT_1E_INC_PICCOM_H_

#include "stm32f1xx_hal.h"
#include "stdint.h"
#include "stdbool.h"

#define PIC_FRAME_SIZE 8
#define PIC_TRAME_START 'G'
#define PIC_TRAME_CONFIRM 'O'

typedef struct {
	uint8_t x;
	uint8_t y;
	uint8_t pince;
	uint8_t balance;
} PIC_Status_t;

typedef struct {
	uint8_t motor0;
	uint8_t motor1;
	uint8_t motor2;
	uint8_t motor3;
	uint8_t motor4;
} Motor_Positions_t;

void PICCom_Init(UART_HandleTypeDef *huart);
void PICCom_RxCallback(UART_HandleTypeDef *huart);
bool PICCom_HasUpdated(void);
PIC_Status_t PICCom_GetStatus(void);
HAL_StatusTypeDef PICCom_SendPositions(const Motor_Positions_t *pos);

#endif /* TEP__SESSION_3_KIT_1E_INC_PICCOM_H_ */
