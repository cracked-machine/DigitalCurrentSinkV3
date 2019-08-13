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

dacmode_t getDACMode(uint32_t Channel);
char* getDACMode2String(uint32_t Channel);
void setDACMode(uint32_t Channel, dacmode_t mode);



void cycleDACMode(uint32_t Channel);

void increaseDAC(uint32_t Channel);
void decreaseDAC(uint32_t Channel);
void setVoltagePreview(uint32_t Channel, float newVolts);
void setVoltage(uint32_t Channel);
void clearVoltagePreview();


void setFreqPreview(uint32_t Channel, float newHertz);
void setFreq(uint32_t Channel);
void clearFreqPreview();
void resetFreqPreview();

float calcDACVolts(uint32_t Channel, uint8_t preview);
float calcDACFreq(uint32_t Channel, uint8_t preview);
float getDACFreq(uint32_t Channel);

void DAC_CompleteCallback(uint32_t Channel);

#endif /* DAC_UTILS_H_ */