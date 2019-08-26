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
	DAC_AUTO	= 	0x02,
	DAC_RAND	= 	0x03

} dacmode_t;

dacmode_t DU_GetDACModeActual(uint32_t Channel);
char* DU_GetDACModeActual2String(uint32_t Channel);
void DU_SetDACModeActual(uint32_t Channel, dacmode_t mode);
void DU_SetDualDACModeActual(dacmode_t mode);

void DU_SetDACModePreview(uint32_t Channel, dacmode_t pNewMode);
dacmode_t DU_GetDACModePreview(uint32_t Channel);
char* DU_GetDACModePreview2String(uint32_t Channel);

void DU_IncreaseDAC(uint32_t Channel);
void DU_DecreaseDAC(uint32_t Channel);
void DU_SetVoltagePreview(uint32_t Channel, float newVolts);
void DU_SetVoltage(uint32_t Channel);
void DU_ClearVoltagePreview(uint32_t Channel);

uint32_t DU_GetRampAmplitudeSetting(uint32_t Channel);
char* DU_GetRampAmplitudeSetting2String(uint32_t Channel);
void DU_SetRampAmplitudeSetting(uint32_t Channel, uint32_t amplitude);
uint32_t DU_GetRandAmplitudeSetting(uint32_t Channel);
char* DU_GetRandAmplitudeSetting2String(uint32_t Channel);
void DU_SetRandAmplitudeSetting(uint32_t Channel, uint32_t amplitude);

void DU_SetFreqPreview(uint32_t Channel, float newHertz);
void DU_SetFreq(uint32_t Channel);
void DU_ClearFreqPreview(uint32_t Channel);


float DU_CalcVoltsFromBits(uint32_t Channel, uint8_t preview);
float DU_CalcFreqFromBits(uint32_t Channel, uint8_t preview);
float DU_CalcCurrentFromOhmsLaw(uint32_t Channel, int preview);
float DU_CalcVoltageFromOhmsLaw(uint32_t Channel, float reqAmps);
uint32_t DU_GetDATDOR(uint32_t Channel);

void DU_CompleteCallback(uint32_t Channel);

void DU_SetActiveDACChannel(uint32_t Channel);
uint32_t DU_GetActiveDACChannel();
char* DU_GetActiveDACChannel2String();
void DU_ToggleDualChannelMode(uint8_t enable);
uint8_t DU_IsDualChannelMode();

#endif /* DAC_UTILS_H_ */
