/*
 * dac_utils.c
 *
 *  Created on: Aug 3, 2019
 *      Author: chris
 */

#include "dac_utils.h"
#include "dac.h"
#include "tim.h"
#include <stdio.h>

#define MAXDACDIV 255

uint8_t chan1Mode = DAC_USER;
uint16_t chan1Voltage = 0;
uint16_t chan1Freq = 0;

uint8_t chan2Mode = DAC_USER;
uint16_t chan2Voltage = 0;
uint16_t chan2Freq = 0;


void increaseVoltage(uint32_t Channel)
{
	if (Channel == DAC_CHANNEL_1)
	{
		chan1Voltage += 1;
		if(chan1Voltage > 4095)
			chan1Voltage = 0;

		HAL_DAC_SetValue(&hdac1,Channel, DAC_ALIGN_8B_R, chan1Voltage);

	}
	else if (Channel == DAC_CHANNEL_2)
	{
		chan2Voltage += 1;
		if(chan2Voltage > 4095)
			chan2Voltage = 0;

		HAL_DAC_SetValue(&hdac1,Channel, DAC_ALIGN_8B_R, chan2Voltage);
	}
}

void resetDACVoltage(uint32_t Channel)
{
	HAL_DAC_SetValue(&hdac1,Channel, DAC_ALIGN_8B_R, 0);
	if (Channel == DAC_CHANNEL_1)
	{
		chan1Voltage = 0;
	}
	else if (Channel == DAC_CHANNEL_2)
	{
		chan2Voltage = 0;
	}

}

void increaseFreq(uint32_t Channel)
{
	if (Channel == DAC_CHANNEL_1)
	{
		chan1Freq = htim7.Instance->PSC;
		chan1Freq -= 1;
		if(chan1Freq < 1)
			chan1Freq = MAXDACDIV;
		htim6.Instance->PSC &= ~(0xFFFF);
		htim6.Instance->PSC = (chan1Freq - 50);
		printf("New Chan1: %u\n", chan1Freq);
	}
	else if (Channel == DAC_CHANNEL_2)
	{
		chan2Freq = htim7.Instance->PSC;
		if(chan2Freq < 1)
			chan2Freq = MAXDACDIV;
		htim7.Instance->PSC &= ~(0xFFFF);
		htim7.Instance->PSC = (chan2Freq - 50);
		printf("New Chan2: %u\n", chan2Freq);
	}
}



dacmode_t getDACMode(uint32_t Channel)
{
	volatile uint32_t hdac_cr = hdac1.Instance->CR;
	if (Channel == DAC_CHANNEL_1)
	{
		if	(hdac_cr & DAC_CR_WAVE1_0)
		{
			return DAC_NOISE;
		}
		else if (hdac_cr & DAC_CR_WAVE1_1)
		{
			return DAC_TRI;
		}
		else
		{
			return DAC_USER;
		}
	}
	else if (Channel == DAC_CHANNEL_2)
	{
		if	(hdac_cr & DAC_CR_WAVE2_0)
		{
			return DAC_NOISE;
		}
		else if (hdac_cr & DAC_CR_WAVE2_1)
		{
			return DAC_TRI;
		}
		else
		{
			return DAC_USER;
		}
	}
	else
	{
		return DAC_ERROR;
	}
}

void setDACMode(uint32_t Channel, dacmode_t mode)
{

	if (Channel == DAC_CHANNEL_1)
	{
		hdac1.Instance->CR &= ~(DAC_CR_WAVE1_Msk | DAC_CR_MAMP1_Msk);
		if(mode == DAC_USER)
		{
			hdac1.Instance->CR &= ~(DAC_CR_WAVE1_0 | DAC_CR_WAVE1_1);
			resetDACVoltage(Channel);
		}
		else if (mode == DAC_NOISE)
		{

			hdac1.Instance->CR |= (DAC_CR_WAVE1_0 | DAC_LFSRUNMASK_BITS11_0);
			resetDACVoltage(Channel);
		}
		else if (mode == DAC_TRI)
		{
			hdac1.Instance->CR |= (DAC_CR_WAVE1_1 | DAC_TRIANGLEAMPLITUDE_4095);
			resetDACVoltage(Channel);
		}
	}
	else if (Channel == DAC_CHANNEL_2)
	{
		hdac1.Instance->CR &= ~(DAC_CR_WAVE2_Msk | DAC_CR_MAMP2_Msk);
		if(mode == DAC_USER)
		{
			hdac1.Instance->CR &= ~(DAC_CR_WAVE2_0 | DAC_CR_WAVE2_1);
			resetDACVoltage(Channel);
		}
		else if (mode == DAC_NOISE)
		{
			hdac1.Instance->CR |= (DAC_CR_WAVE2_0 | (DAC_LFSRUNMASK_BITS11_0 << (Channel & 0x10UL)));
			resetDACVoltage(Channel);
		}
		else if (mode == DAC_TRI)
		{
			hdac1.Instance->CR |= (DAC_CR_WAVE2_1 | (DAC_TRIANGLEAMPLITUDE_4095 << (Channel & 0x10UL)));
			resetDACVoltage(Channel);
		}
	}

}

void cycleDACMode(uint32_t Channel)
{
	uint8_t currentDacMode = getDACMode(Channel);
	if(currentDacMode == DAC_USER)
	{
		setDACMode(Channel, DAC_TRI);
	}
	else if (currentDacMode == DAC_TRI)
	{
		setDACMode(Channel, DAC_NOISE);
	}
	else if (currentDacMode == DAC_NOISE)
	{

		setDACMode(Channel, DAC_USER);
	}
}

void increaseDAC(uint32_t Channel)
{
	uint8_t currentDacMode = getDACMode(Channel);
	if(currentDacMode == DAC_USER)
	{
		increaseVoltage(Channel);
	}
	else if (currentDacMode == DAC_TRI)
	{
		increaseFreq(Channel);
	}
	else if (currentDacMode == DAC_NOISE)
	{
		increaseVoltage(Channel);
	}
}
