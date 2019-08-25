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
	HOME_DISP,
	CHANSEL_DISP,
	PROGSEL_DISP,
	PARAMS_DISP,
	AMPLITUDE_DISP,

	numStates

} displayState_t;


typedef enum
{
	SHOWBITS,
	SHOWVOLT,
	SHOWCURR
} unitmode_t;



void DM_SetUnitMode(unitmode_t mode);
unitmode_t DM_GetUnitMode();

void DM_SetState(uint32_t Channel, displayState_t State);

displayState_t DM_GetState();

uint32_t DM_GetSelectedDac();

void DM_UpdateDisplay();

void DM_ToggleBlink();

void DM_SetBlinkTimer(uint8_t pBlink);

void DM_ChangeScreen(displayState_t State);


#endif /* DISPLAYMANAGER_H_ */
