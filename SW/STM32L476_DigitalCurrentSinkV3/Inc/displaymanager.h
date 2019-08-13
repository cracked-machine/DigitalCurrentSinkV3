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
typedef enum selectedDacChan
{
	SEL_CHAN_1	= 	DAC_CHANNEL_1,
	SEL_CHAN_2	= 	DAC_CHANNEL_2,
	numDacs

} selectedDacChan_t;

void dm_setState(uint32_t Channel, displayState_t State);
displayState_t dm_getState();

selectedDacChan_t dm_getSelectedDac();

void dm_updateDisplay();
void dm_drawDac1Value(uint8_t preview);
void dm_drawDac2Value(uint8_t preview);

void dm_drawMainOverlay();
void dm_drawMainDisp();

void dm_drawModeOverlay();
void dm_drawModeDisp();

void dm_drawValueOverlay();
void dm_drawValueDisp();

void dm_toggleblink();
void dm_setBlinkTimer(uint8_t pBlink);


#endif /* DISPLAYMANAGER_H_ */
