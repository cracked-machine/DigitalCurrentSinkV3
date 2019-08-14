/*
 * displaymanager.h
 *
 *  Created on: Aug 5, 2019
 *      Author: chris
 */

#include "stdint.h"
#include "dac.h"

#ifndef DISPLAYMANAGER_H_
#define DISPLAYMANAGER_H_

typedef enum displayState
{
	DISPMAIN	=	0x00,
	DISPMODE	=	0x01,
	DISPVAL		=	0x02,
	numStates

} displayState_t;

// DAC_CHANNEL_1, DAC_CHANNEL2 defined in STM32L4xx_HAL_DAC.h


void DM_SetState(uint32_t Channel, displayState_t State);

displayState_t DM_GetState();

uint32_t DM_GetSelectedDac();

void DM_UpdateDisplay();

void DM_ToggleBlink();

void DM_SetBlinkTimer(uint8_t pBlink);



#endif /* DISPLAYMANAGER_H_ */