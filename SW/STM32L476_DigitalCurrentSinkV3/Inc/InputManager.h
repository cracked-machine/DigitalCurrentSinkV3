/*
 * inputmanager.h
 *
 *  Created on: Aug 6, 2019
 *      Author: chris
 */

#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

void IM_MenuEXTIHandler();

void IM_MuxKeysRows();
void IM_ReadKeyCol0();
void IM_ReadKeyCol1();
void IM_ReadKeyCol2();

void IM_SetKeypadDebounceCounter(uint16_t pValue);

uint8_t IM_GetDigitLength();

#endif /* INPUTMANAGER_H_ */
