/*
 * ADCUtilities.h
 *
 *  Created on: Aug 25, 2019
 *      Author: chris
 */

#ifndef ADCUTILITIES_H_
#define ADCUTILITIES_H_

#include "stm32l4xx_hal.h"

typedef enum
{
	ADC_CH0 = ADC_CHANNEL_6,
	ADC_CH1 = ADC_CHANNEL_7,

	numChannels
} AU_ADC_Channels_t;

uint32_t* AU_GetADCOut();
uint32_t AU_GetADCOutChannel(uint32_t Channel);
float AU_CalcVoltage(uint32_t Channel);
float AU_CalcCurrent(uint32_t Channel);


#endif /* ADCUTILITIES_H_ */
