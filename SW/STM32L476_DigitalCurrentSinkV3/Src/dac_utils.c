/*
 * dac_utils.c
 *
 *  Created on: Aug 3, 2019
 *      Author: chris
 */

#include "dac_utils.h"
#include "displaymanager.h"
#include "stm32l4xx_hal.h"

#include "dac.h"
#include "tim.h"
#include <stdio.h>
#include <math.h>

// system constants

#define TIMRES 65535
#define MAXFREQSTEP 32

#define MASTERCLK 80000000
#define CALCFREQ(PSC,ARR) (MASTERCLK/(PSC*ARR))

#define VREF 3.3
#define DACRES 4096
#define MAXAMPSTEP 1

// DAC Channel 1 variables

uint8_t chan1Mode = DAC_USER;


uint32_t chan1AmpCountPreview = 0;


uint16_t chan1FreqCount = 0;
uint32_t chan1FreqCountPreview = 0;
float chan1FreqHz = 0;

// DAC Channel 2 variables

uint8_t chan2Mode = DAC_USER;


uint32_t chan2AmpCountPreview = 0;

uint16_t chan2FreqCount = 0;
uint32_t chan2FreqCountPreview = 0;
float chan2FreqHz = 0;



float calcDACVolts(uint32_t Channel, uint8_t preview)
{
	float result = 0;
	if(Channel == DAC_CHANNEL_1)
	{
		if(preview)
			result = (float)(VREF * ((float)chan1AmpCountPreview/(float)DACRES));
		else
			result = (float)(VREF * ((float)hdac1.Instance->DOR1/(float)DACRES));
	}
	if(Channel == DAC_CHANNEL_2)
	{
		if(preview)
			result = (float)(VREF * ((float)chan2AmpCountPreview/(float)DACRES));
		else
			result = (float)(VREF * ((float)hdac1.Instance->DOR2/(float)DACRES));
	}
	return result;
}

uint32_t calcNewDOR(float volts)
{
	uint32_t result = ((uint32_t)volts * DACRES) / VREF;
	return result;
}

float calcDACFreq(uint32_t Channel, uint8_t preview)
{
	float result = 0;
	if(Channel == DAC_CHANNEL_1)
	{
		if(preview)
			result = (float)MASTERCLK/((float)htim6.Instance->PSC * (float)chan1FreqCountPreview);
		else
			result = (float)MASTERCLK/((float)htim6.Instance->PSC * (float)htim6.Instance->ARR);
	}
	if(Channel == DAC_CHANNEL_2)
	{
		if(preview)
			result = (float)MASTERCLK/((float)htim7.Instance->PSC * (float)chan2FreqCountPreview);
		else
			result = (float)MASTERCLK/((float)htim7.Instance->PSC * (float)htim7.Instance->ARR);
	}
	return result;
}

uint16_t calcNewARR(uint16_t Channel, float hertz)
{
	uint32_t result = 0;
	if(Channel == DAC_CHANNEL_1)
		result = (MASTERCLK / (uint16_t)hertz) / htim6.Instance->PSC;
	if(Channel == DAC_CHANNEL_2)
		result = (MASTERCLK / (uint16_t)hertz) / htim7.Instance->PSC;
	if(result > TIMRES)
		result = TIMRES;
	return result;
}

void setVoltagePreview(uint32_t Channel, float newVolts)
{
	if (Channel == DAC_CHANNEL_1)
	{
		chan1AmpCountPreview = calcNewDOR(newVolts);
		printf("New DAC_CHANNEL_1 Volt Request: %2.2fV\n", (float)calcDACVolts(DAC_CHANNEL_1, 1));
		//HAL_DAC_SetValue(&hdac1,DAC_CHANNEL_1, DAC_ALIGN_8B_R, chan1AmpCount);
		//printf("Chan1 Volts: %uHz (%2.2fV)\n", chan1AmpCount, (float)calcDACVolts(DAC_CHANNEL_1));

	}

	else if (Channel == DAC_CHANNEL_2)
	{
		chan2AmpCountPreview = calcNewDOR(newVolts);
		printf("New DAC_CHANNEL_2 Volt Request: %2.2fV\n", (float)calcDACVolts(DAC_CHANNEL_2,1));
		//HAL_DAC_SetValue(&hdac1,DAC_CHANNEL_2, DAC_ALIGN_8B_R, chan2AmpCount);
		//printf("Chan2 Volts: %uHz (%2.2fV)\n", chan2AmpCount, (float)calcDACVolts(DAC_CHANNEL_2));

	}
}

void setVoltage(uint32_t Channel)
{
	// start debug counter (DAC requires 1-3 cycles before completing conversion)
	__HAL_TIM_CLEAR_FLAG(&htim15, TIM_FLAG_UPDATE);
	HAL_TIM_Base_Start_IT(&htim15);


	if (Channel == DAC_CHANNEL_1)
	{
		// update register from the preview variable
		hdac1.Instance->DHR12R1 = chan1AmpCountPreview;
		// calc voltage from the new register value (0)
		//printf("New DAC_CHANNEL_1 Volt Setting: %2.2fV\n", calcDACVolts(DAC_CHANNEL_1, 0 ));


	}

	else if (Channel == DAC_CHANNEL_2)
	{
		// update register from the preview variable
		hdac1.Instance->DHR12R2 = chan2AmpCountPreview;
		// calc voltage from the new register value (0)
		//printf("New DAC_CHANNEL_2 Volt Setting: %2.2fV\n", calcDACVolts(DAC_CHANNEL_2, 0 ));


	}
}

void clearVoltagePreview()
{
	chan1AmpCountPreview = 0;
	chan2AmpCountPreview = 0;
}

void changeVoltage(uint32_t Channel, int increase)
{
	if (Channel == DAC_CHANNEL_1)
	{
		if(increase)
			chan1AmpCountPreview += MAXAMPSTEP;
		else
			chan1AmpCountPreview -= MAXAMPSTEP;

		if((chan1AmpCountPreview < 1) | (chan1AmpCountPreview > DACRES))
			chan1AmpCountPreview = 0;

		//HAL_DAC_SetValue(&hdac1,DAC_CHANNEL_1, DAC_ALIGN_8B_R, chan1AmpCountPreview);
	}
	else if (Channel == DAC_CHANNEL_2)
	{
		if(increase)
			chan2AmpCountPreview += MAXAMPSTEP;
		else
			chan2AmpCountPreview -= MAXAMPSTEP;

		if((chan2AmpCountPreview < 1) | (chan2AmpCountPreview > DACRES))
			chan2AmpCountPreview = 0;

		//HAL_DAC_SetValue(&hdac1,DAC_CHANNEL_2, DAC_ALIGN_8B_R, chan2AmpCountPreview);
	}
}

void resetDACVoltage(uint32_t Channel)
{
	HAL_DAC_SetValue(&hdac1,Channel, DAC_ALIGN_8B_R, 0);
	if (Channel == DAC_CHANNEL_1)
	{
		chan1AmpCountPreview = 0;
	}
	else if (Channel == DAC_CHANNEL_2)
	{
		chan2AmpCountPreview = 0;
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

void setFreqPreview(uint32_t Channel, uint32_t newHertz)
{
	if (Channel == DAC_CHANNEL_1)
	{
		chan1FreqCountPreview = calcNewARR(DAC_CHANNEL_1, newHertz);
		printf("New DAC_CHANNEL_1 Freq Request: %2.2fHz\n", (float)calcDACFreq(DAC_CHANNEL_1,1));
		//htim6.Instance->ARR = (uint32_t)(MASTERCLK/(htim6.Instance->PSC * newHertz));
		//printf("New Freq request: %lu\n", newHertz);
		//chan1FreqHz = (float)MASTERCLK/(htim6.Instance->PSC * htim6.Instance->ARR);
		//printf("Chan1 Freq: %2.4fHz (%u)\n", chan1FreqHz, chan1FreqCount);
	}
	else if (Channel == DAC_CHANNEL_2)
	{
		chan2FreqCountPreview = calcNewARR(DAC_CHANNEL_2, newHertz);
		printf("New DAC_CHANNEL_2 Freq Request: %2.2fHz\n", (float)calcDACFreq(DAC_CHANNEL_2,1));
		/*htim7.Instance->ARR = (uint32_t)(MASTERCLK/(htim7.Instance->PSC * newHertz));
		printf("New Freq request: %lu\n", newHertz);
		chan2FreqHz = (float)MASTERCLK/(htim7.Instance->PSC * htim7.Instance->ARR);
		printf("Chan2 Freq: %2.4fHz (%u)\n", chan2FreqHz, chan2FreqCount);
		*/
	}
}
void setFreq(uint32_t Channel)
{

	// start debug counter (DAC requires 1-3 cycles before completing conversion)
	__HAL_TIM_CLEAR_FLAG(&htim15, TIM_FLAG_UPDATE);
	HAL_TIM_Base_Start_IT(&htim15);


	if (Channel == DAC_CHANNEL_1)
	{
		htim6.Instance->ARR = chan1FreqCountPreview;
		//printf("New DAC_CHANNEL_1 Freq Setting: %2.2fHz\n", (float)calcDACFreq(DAC_CHANNEL_1, 0 ));
		//chan1FreqHz = (float)MASTERCLK/(htim6.Instance->PSC * htim6.Instance->ARR);
		//printf("Chan1 Freq: %2.4fHz (%u)\n", chan1FreqHz, chan1FreqCount);
	}
	else if (Channel == DAC_CHANNEL_2)
	{
		htim7.Instance->ARR = chan2FreqCountPreview;
		//printf("New DAC_CHANNEL_2 Freq Setting: %2.2fHz\n", (float)calcDACFreq(DAC_CHANNEL_2, 0 ));
		//chan2FreqHz = (float)MASTERCLK/(htim7.Instance->PSC * htim7.Instance->ARR);
		//printf("Chan2 Freq: %2.4fHz (%u)\n", chan2FreqHz, chan2FreqCount);
	}
}

void clearFreqPreview()
{
	chan1FreqCountPreview = 0;
	chan2FreqCountPreview = 0;
}

void changeFreq(uint32_t Channel, int increase)
{
	if (Channel == DAC_CHANNEL_1)
	{
		chan1FreqCount = htim6.Instance->ARR;

		// decrement cycle period to increase frequency
		if(increase)
			chan1FreqCountPreview -= MAXFREQSTEP;
		else
			chan1FreqCountPreview += MAXFREQSTEP;

		if((chan1FreqCountPreview < 1) | (chan1FreqCountPreview > TIMRES))
			chan1FreqCountPreview = TIMRES;

		//htim6.Instance->ARR = (chan1FreqCount);

		//chan1FreqHz = (float)MASTERCLK/(htim6.Instance->PSC * htim6.Instance->ARR);
		// recalculate freq (hertz) output
		//printf("Chan1 Freq: %2.4fHz (%u)\n", chan1FreqHz, chan1FreqCount);
	}
	else if (Channel == DAC_CHANNEL_2)
	{
		// decrement cycle period to increase frequency
		if(increase)
			chan2FreqCountPreview -= MAXFREQSTEP;
		else
			chan2FreqCountPreview += MAXFREQSTEP;

		if((chan2FreqCountPreview < 1) | (chan2FreqCountPreview > TIMRES))
			chan2FreqCountPreview = TIMRES;

		//htim7.Instance->ARR = (chan2FreqCount);

		//chan2FreqHz = (float)MASTERCLK/(htim7.Instance->PSC * htim7.Instance->ARR);
		// recalculate freq (hertz) output
		//printf("Chan2 Freq: %2.4fHz (%u)\n", chan2FreqHz, chan2FreqCount);
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
	dm_setBlinkTimer(1);
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
	dm_setBlinkTimer(1);
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


char* getDACMode2String(uint32_t Channel)
{
	volatile uint32_t hdac_cr = hdac1.Instance->CR;
	if (Channel == DAC_CHANNEL_1)
	{
		if	(hdac_cr & DAC_CR_WAVE1_0)
		{
			return "Random";
		}
		else if (hdac_cr & DAC_CR_WAVE1_1)
		{
			return "Auto";
		}
		else
		{
			return "User";
		}
	}
	else if (Channel == DAC_CHANNEL_2)
	{
		if	(hdac_cr & DAC_CR_WAVE2_0)
		{
			return "Random";
		}
		else if (hdac_cr & DAC_CR_WAVE2_1)
		{
			return "Auto";
		}
		else
		{
			return "User";
		}
	}
	else
	{
		return "Error";
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


void DAC_CompleteCallback(uint32_t Channel)
{
	if(Channel == DAC_CHANNEL_1)
	{
		if(getDACMode(DAC_CHANNEL_1) == DAC_USER)
			printf("New DAC_CHANNEL_1 Volt Setting: %2.2fV\n", calcDACVolts(DAC_CHANNEL_1, 0 ));
		else
			printf("New DAC_CHANNEL_1 Freq Setting: %2.2fHz\n", (float)calcDACFreq(DAC_CHANNEL_1, 0 ));
	}
	if(Channel == DAC_CHANNEL_2)
	{
		if(getDACMode(DAC_CHANNEL_1) == DAC_USER)
			printf("New DAC_CHANNEL_1 Volt Setting: %2.2fV\n", calcDACVolts(DAC_CHANNEL_1, 0 ));
		else
			printf("New DAC_CHANNEL_1 Freq Setting: %2.2fHz\n", (float)calcDACFreq(DAC_CHANNEL_1, 0 ));
	}

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


