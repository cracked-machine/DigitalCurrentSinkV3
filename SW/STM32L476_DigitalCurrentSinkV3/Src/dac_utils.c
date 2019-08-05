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

// system constants

#define DACARR 65535
#define MAXFREQSTEP 1024

#define MASTERCLK 80000000
#define CALCFREQ(PSC,ARR) (MASTERCLK/(PSC*ARR))

#define VREF 3.3
#define MAXDVAL 4096
#define MAXAMPSTEP 1

// DAC Channel 1 variables

uint8_t chan1Mode = DAC_USER;

uint16_t chan1AmpCount = 0;
float chan1AmpMVolts = 0;

uint16_t chan1FreqCount = 0;
float chan1FreqHz = 0;

// DAC Channel 2 variables

uint8_t chan2Mode = DAC_USER;

uint16_t chan2AmpCount = 0;
float chan2AmpMVolts = 0;

uint16_t chan2FreqCount = 0;
float chan2FreqHz = 0;

float calcDACVolts(uint16_t dor)
{
	float result = (float)(VREF * ((float)dor/(float)MAXDVAL));
	return result;
}

void changeVoltage(uint32_t Channel, int increase)
{
	if (Channel == DAC_CHANNEL_1)
	{
		if(increase)
			chan1AmpCount += MAXAMPSTEP;
		else
			chan1AmpCount -= MAXAMPSTEP;

		if((chan1AmpCount < 1) | (chan1AmpCount > MAXDVAL))
			chan1AmpCount = 0;

		HAL_DAC_SetValue(&hdac1,DAC_CHANNEL_1, DAC_ALIGN_8B_R, chan1AmpCount);
		// recalculate millvolts output
		//chan1AmpMVolts = (VREF / MAXDVAL) * chan1AmpCount;
		chan1AmpMVolts = (float)calcDACVolts(hdac1.Instance->DOR1);

	}
	else if (Channel == DAC_CHANNEL_2)
	{
		if(increase)
			chan2AmpCount += MAXAMPSTEP;
		else
			chan2AmpCount -= MAXAMPSTEP;

		if((chan2AmpCount < 1) | (chan2AmpCount > MAXDVAL))
			chan2AmpCount = 0;

		HAL_DAC_SetValue(&hdac1,DAC_CHANNEL_2, DAC_ALIGN_8B_R, chan2AmpCount);
		// recalculate millvolts output
		//chan2AmpMVolts = (VREF / MAXDVAL) * chan2AmpCount;
		chan2AmpMVolts = (float)calcDACVolts(hdac1.Instance->DOR2);
	}
}

void resetDACVoltage(uint32_t Channel)
{
	HAL_DAC_SetValue(&hdac1,Channel, DAC_ALIGN_8B_R, 0);
	if (Channel == DAC_CHANNEL_1)
	{
		chan1AmpCount = 0;
		// recalculate millvolts output
		//chan1AmpMVolts = (VREF / MAXDVAL) * chan1AmpCount;
		chan1AmpMVolts = (float)calcDACVolts(hdac1.Instance->DOR1);
	}
	else if (Channel == DAC_CHANNEL_2)
	{
		chan2AmpCount = 0;
		// recalculate millvolts output
		//chan1AmpMVolts = (VREF / MAXDVAL) * chan1AmpCount;
		chan2AmpMVolts = (float)calcDACVolts(hdac1.Instance->DOR2);
	}

}

void resetDACFreq(uint32_t Channel)
{
	HAL_DAC_SetValue(&hdac1,Channel, DAC_ALIGN_8B_R, 0);
	if (Channel == DAC_CHANNEL_1)
	{
		chan1FreqCount = 0;
		// recalculate freq (hertz) output
		chan1FreqHz = (float)MASTERCLK/(htim6.Instance->PSC * htim6.Instance->ARR);
	}
	else if (Channel == DAC_CHANNEL_2)
	{
		chan2FreqCount = 0;
		// recalculate freq (hertz) output
		chan2FreqHz = (float)MASTERCLK/(htim7.Instance->PSC * htim7.Instance->ARR);
	}

}

void changeFreq(uint32_t Channel, int increase)
{
	if (Channel == DAC_CHANNEL_1)
	{
		chan1FreqCount = htim6.Instance->ARR;

		// decrement cycle period to increase frequency
		if(increase)
			chan1FreqCount -= MAXFREQSTEP;
		else
			chan1FreqCount += MAXFREQSTEP;

		if((chan1FreqCount < 1) | (chan1FreqCount > DACARR))
			chan1FreqCount = DACARR;

		htim6.Instance->ARR = (chan1FreqCount);

		chan1FreqHz = (float)MASTERCLK/(htim6.Instance->PSC * htim6.Instance->ARR);
		// recalculate freq (hertz) output
		printf("Chan1 Freq: %2.4fHz (%u)\n", chan1FreqHz, chan1FreqCount);
	}
	else if (Channel == DAC_CHANNEL_2)
	{
		// decrement cycle period to increase frequency
		if(increase)
			chan2FreqCount -= MAXFREQSTEP;
		else
			chan2FreqCount += MAXFREQSTEP;

		if((chan2FreqCount < 1) | (chan2FreqCount > DACARR))
			chan2FreqCount = DACARR;

		htim7.Instance->ARR = (chan2FreqCount);

		chan2FreqHz = (float)MASTERCLK/(htim7.Instance->PSC * htim7.Instance->ARR);
		// recalculate freq (hertz) output
		printf("Chan2 Freq: %2.4fHz (%u)\n", chan2FreqHz, chan2FreqCount);
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
		changeVoltage(Channel, 1);
	}
	else if (currentDacMode == DAC_TRI)
	{
		changeFreq(Channel, 1);
	}
	else if (currentDacMode == DAC_NOISE)
	{
		changeFreq(Channel, 1);
	}
}

void decreaseDAC(uint32_t Channel)
{
	uint8_t currentDacMode = getDACMode(Channel);
	if(currentDacMode == DAC_USER)
	{
		changeVoltage(Channel, 0);
	}
	else if (currentDacMode == DAC_TRI)
	{
		changeFreq(Channel, 0);
	}
	else if (currentDacMode == DAC_NOISE)
	{
		changeFreq(Channel, 0);
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
			htim6.Instance->PSC = 255;
			hdac1.Instance->CR &= ~(DAC_CR_WAVE1_0 | DAC_CR_WAVE1_1);
			resetDACVoltage(DAC_CHANNEL_1);
		}
		else if (mode == DAC_NOISE)
		{
			htim6.Instance->PSC = 4096;
			hdac1.Instance->CR |= (DAC_CR_WAVE1_0 | DAC_LFSRUNMASK_BITS11_0);
			resetDACFreq(DAC_CHANNEL_1);
		}
		else if (mode == DAC_TRI)
		{
			htim6.Instance->PSC = 255;
			hdac1.Instance->CR |= (DAC_CR_WAVE1_1 | DAC_TRIANGLEAMPLITUDE_4095);
			resetDACFreq(DAC_CHANNEL_1);
		}
	}
	else if (Channel == DAC_CHANNEL_2)
	{
		hdac1.Instance->CR &= ~(DAC_CR_WAVE2_Msk | DAC_CR_MAMP2_Msk);
		if(mode == DAC_USER)
		{
			htim7.Instance->PSC = 255;
			hdac1.Instance->CR &= ~(DAC_CR_WAVE2_0 | DAC_CR_WAVE2_1);
			resetDACVoltage(DAC_CHANNEL_2);
		}
		else if (mode == DAC_NOISE)
		{
			htim7.Instance->PSC = 4096;
			hdac1.Instance->CR |= (DAC_CR_WAVE2_0 | (DAC_LFSRUNMASK_BITS11_0 << (Channel & 0x10UL)));
			resetDACFreq(DAC_CHANNEL_2);
		}
		else if (mode == DAC_TRI)
		{
			htim7.Instance->PSC = 255;
			hdac1.Instance->CR |= (DAC_CR_WAVE2_1 | (DAC_TRIANGLEAMPLITUDE_4095 << (Channel & 0x10UL)));
			resetDACFreq(DAC_CHANNEL_2);
		}
	}

}

float getDACVoltage(uint32_t Channel)
{
	if(Channel == DAC_CHANNEL_1)
		return chan1AmpMVolts;
	if(Channel == DAC_CHANNEL_2)
		return chan2AmpMVolts;
	else
		return 0;
}

float getDACFreq(uint32_t Channel)
{
	if(Channel == DAC_CHANNEL_1)
		return chan1FreqHz;
	if(Channel == DAC_CHANNEL_2)
		return chan2FreqHz;
	else
		return 0;
}


