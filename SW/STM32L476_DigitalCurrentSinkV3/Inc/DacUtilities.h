/*
 * dac_utils.h
 *
 *  Created on: Aug 3, 2019
 *      Author: Chris Sutton
 */

#ifndef DAC_UTILS_H_
#define DAC_UTILS_H_

#include <stdint.h>

typedef enum dacmode
{
	DAC_ERROR 	= 	0x00,	// illegal channel request
	DAC_USER 	=	0x01,
	DAC_TRI		= 	0x02,
	DAC_NOISE	= 	0x03

} dacmode_t;

dacmode_t DU_GetDACModeActual(uint32_t Channel);
char* DU_GetDACModeActual2String(uint32_t Channel);
void DU_SetDACModeActual(uint32_t Channel, dacmode_t mode);

void DU_SetDACModeActualPreview(uint32_t Channel, dacmode_t pNewMode);
dacmode_t DU_GetDACModeActualPreview(uint32_t Channel);
char* DU_GetDACModeActualPreview2String(uint32_t Channel);

void DU_IncreaseDAC(uint32_t Channel);
void DU_DecreaseDAC(uint32_t Channel);
void DU_SetVoltagePreview(uint32_t Channel, float newVolts);
void DU_SetVoltage(uint32_t Channel);
void DU_ClearVoltagePreview();


void DU_SetFreqPreview(uint32_t Channel, float newHertz);
void DU_SetFreq(uint32_t Channel);
void DU_ClearFreqPreview();


float DU_CalcDACVolts(uint32_t Channel, uint8_t preview);
float DU_CalcDACFreq(uint32_t Channel, uint8_t preview);

void DU_CompleteCallback(uint32_t Channel);

void DU_setActiveDACChannel(uint32_t Channel);
uint32_t DU_getActiveDACChannel();
char* DU_getActiveDACChannel2String();
void DU_setDualChannelMode(uint8_t enable);
uint8_t DU_isDualChannelMode();

#endif /* DAC_UTILS_H_ */
