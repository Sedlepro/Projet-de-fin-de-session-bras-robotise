/*
 * moteurs.h
 *
 *  Created on: Nov 26, 2025
 *      Author: Sedrick
 */

#ifndef TEP__SESSION_3_KIT_1E_INC_MOTEURS_H_
#define TEP__SESSION_3_KIT_1E_INC_MOTEURS_H_

#include <stdint.h>
#include <stdio.h>

typedef struct {
	uint8_t motor0;
	uint8_t motor1;
	uint8_t motor2;
	uint8_t motor3;
	uint8_t motor4;
} Motor_Positions_t;

typedef enum {
	MOTOR_BASE = 0,
	MOTOR_SOULDER,
	MOTOR_WRIST,
	MOTOR_ELBOW,
	MOTOR_GRABBER
}Motor_ID;

#define BASE_MIN 90
#define BASE_MAX 160
#define SHOULDER_MIN 90
#define SHOULDER_MAX 130
#define ELBOW_MIN 0
#define ELBOW_MAX 90
#define WRIST_MIN 10
#define WRIST_MAX 165
#define GRABBER_MIN 0
#define GRABBER_MAX 140

extern const Motor_Positions_t POSITION_REPOS;

extern const Motor_Positions_t POSITION_MEMBRANE_HAUT;

extern const Motor_Positions_t POSITION_CASE1;
extern const Motor_Positions_t POSITION_CASE2;
extern const Motor_Positions_t POSITION_CASE3;

extern const Motor_Positions_t POSITION_BALANCE_HAUT;
extern const Motor_Positions_t POSITION_BALANCE_PESEE;

extern const Motor_Positions_t POSITION_DEPOT20G;
extern const Motor_Positions_t POSITION_DEPOT50G;
extern const Motor_Positions_t POSITION_DEPOT80G;

void Motor_Init(void);
void Motor_Set(Motor_ID_t id, uint8_t value);
void Motor_Adjust(Motor_ID_t id, int8_t delta);
const Motor_Positions_t* Motor_GetPositions(void);
void Motor_ApplyPreset(const Motor_Positions_t *preset);
void Motor_SoftGoto(const Motor_Positions_t *target);

#endif /* TEP__SESSION_3_KIT_1E_INC_MOTEURS_H_ */
