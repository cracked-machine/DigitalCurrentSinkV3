/*
 * dac_utils.h
 *
 *  Created on: Aug 3, 2019
 *      Author: chris
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

dacmode_t DU_GetDACMode(uint32_t Channel);
char* DU_GetDACMode2String(uint32_t Channel);
void DU_SetDACMode(uint32_t Channel, dacmode_t mode);

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

#endif /* DAC_UTILS_H_ */
