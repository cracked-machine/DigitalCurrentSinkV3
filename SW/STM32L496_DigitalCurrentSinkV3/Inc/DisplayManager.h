/*
 * displaymanager.h
 *
 *  Created on: Aug 5, 2019
 *      Author: Chris Sutton
 */

#include "stdint.h"
#include "dac.h"

#ifndef DISPLAYMANAGER_H_
#define DISPLAYMANAGER_H_

typedef enum displayState
{
	DISPMAIN,
	DISPMODE,
	DISPVAL,
	HOME_DISP,
	CHANSEL_DISP,
	PROGSEL_DISP,
	PARAMS_DISP,

	numStates

} displayState_t;

// DAC_CHANNEL_1, DAC_CHANNEL2 defined in STM32L4xx_HAL_DAC.h


void DM_SetState(uint32_t Channel, displayState_t State);

displayState_t DM_GetState();

uint32_t DM_GetSelectedDac();

void DM_UpdateDisplay();

void DM_ToggleBlink();

void DM_SetBlinkTimer(uint8_t pBlink);

void DM_ChangeScreen(displayState_t State);


#endif /* DISPLAYMANAGER_H_ */
