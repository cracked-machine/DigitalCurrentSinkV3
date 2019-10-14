/*
 * ADCUtilities.c
 *
 *  Created on: Aug 25, 2019
 *      Author: chris
 */


#include "ADCUtilities.h"
#include "adc.h"
#include <stdio.h>
#include "DacUtilities.h"

#include "SystemConstants.h"

uint32_t adc_out[2] = {};



uint32_t* AU_GetADCOut()
{
	return adc_out;
}

uint32_t AU_GetADCOutChannel(uint32_t Channel)
{
	if(Channel < numChannels)
	{
		switch(Channel)
		{
			case ADC_CH0:
				return adc_out[0];
				break;
			case ADC_CH1:
				return adc_out[1];
				break;
			default:
				break;
		}
	}
	printf("ERR:AU_GetADCOutChannel:37\n");
	return 0;
}

float AU_CalcVoltage(uint32_t Channel)
{
	float result=0;
	switch(Channel)
	{
		case ADC_CH0:
			result = (VREF / ADCRES) * adc_out[0];
			result = result * CH0_INAMP_GAIN_COMP;
			break;
		case ADC_CH1:
			result = (VREF / ADCRES) * adc_out[1];
			result = result * CH1_INAMP_GAIN_COMP;
			break;
		default:
			break;
	}
	return result;
}

float AU_CalcCurrent(uint32_t Channel)
{
	float result=0;
	switch(Channel)
	{
		case ADC_CH0:
			result = (AU_CalcVoltage(ADC_CH0) / CH0_PWR_RESISTOR);
			break;
		case ADC_CH1:
			result = (AU_CalcVoltage(ADC_CH1) / CH1_PWR_RESISTOR);
			break;
		default:
			break;
	}

//	if(result > 3.1)
//		DU_FullReset();

	return result;
}
