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

uint16_t getChan1AmpCountTemp();
uint16_t getChan1FreqCountTemp();
uint16_t getChan2AmpCountTemp();
uint16_t getChan2FreqCountTemp();

void cycleDACMode(uint32_t Channel);

void increaseDAC(uint32_t Channel);
void decreaseDAC(uint32_t Channel);
void setVoltage(uint32_t Channel, float newVolts);
void setFreq(uint32_t Channel, uint32_t newHertz);

float getDACVoltage(uint32_t Channel);
float getDACFreq(uint32_t Channel);

#endif /* DAC_UTILS_H_ */
