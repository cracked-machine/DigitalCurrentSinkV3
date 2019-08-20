/*
 * dac_utils.c
 *
 *  Created on: Aug 3, 2019
 *      Author: Chris Sutton
 */

#include <DacUtilities.h>
#include <DisplayManager.h>
#include "stm32l4xx_hal.h"

#include "dac.h"
#include "tim.h"
#include <stdio.h>
#include <math.h>


/* Max resolution for 16-bit timer */
#define TIMRES 				65535

/* MCU clock speed in hertz */
#define MASTERCLK 			80000000

/* DAC VREF */
#define VREF 				3.3

/* DAC resolution */
#define DACRES 				4096

/* increment amounts for nudging voltage/frequency values */
#define MAXFREQSTEP 		32
#define MAXAMPSTEP 			1

/*  DAC channel context set from user menu button selection. See IM_MenuEXTIHandler() */
uint32_t 	selected_dac_channel = DAC_CHANNEL_1;

/* Should settings be applied independently (0) in parallel (1) */
uint8_t dual_channel_mode = 0;

/* preview variables for DAC mode. These values are applied to registers
 * when user has confirmed settings in menu screens */
dacmode_t channel1_dacmode_preview = DAC_USER;
dacmode_t channel2_dacmode_preview = DAC_USER;

/* 	Preview of DAC_CHANNEL_1 output register stored as 2^12 decimal number */
uint32_t chan1_amp_count_preview = 0;

/* 	Preview of Timer6 count register stored as 2^12 decimal number.
	Default to slowest count period (TIMRES) prevents reset to zero/infinity
	NOTE: Zero value is illegal for timer ARR!	*/
uint32_t chan1_freq_count_preview = TIMRES;

/* Hertz conversion of chan1_freq_count_preview for display */
float chan1_freq_hertz = 0;

/* 	Preview of DAC_CHANNEL_2 output register stored as 2^12 decimal number */
uint32_t chan2_amp_count_preview = 0;

/* 	Preview of Timer7 count register stored as 2^12 decimal number
 	Default to slowest count period (TIMRES) prevents reset to zero/infinity */
 uint32_t chan2_freq_count_preview = TIMRES;

 /* Hertz conversion of chan2_freq_count_preview for display */
float chan2_freq_hertz = 0;

/**
  * @brief 	set temporary DAC mode (to be applied later on confirmation)
  *
  * @param  pNewMode The new DAC mode
  *         This parameter can be one of the following values:
  *            		DAC_ERROR 	= 	0x00,	// illegal channel request
  *					DAC_USER 	=	0x01,
  *					DAC_AUTO		= 	0x02,
  *					DAC_RAND	= 	0x03
  *
  * @retval none
  */

void DU_SetDACModePreview(uint32_t Channel, dacmode_t pNewMode)
{
	if(Channel == DAC_CHANNEL_1)
		channel1_dacmode_preview = pNewMode;
	else
		channel2_dacmode_preview = pNewMode;

}

/**
  * @brief 	get the temporary DAC mode
  *
  *
  * @retval DAC mode
  *         This parameter can be one of the following values:
  *            		DAC_ERROR 	= 	0x00,	// illegal channel request
  *					DAC_USER 	=	0x01,
  *					DAC_AUTO		= 	0x02,
  *					DAC_RAND	= 	0x03
  */

dacmode_t DU_GetDACModePreview(uint32_t Channel)
{
	if(Channel == DAC_CHANNEL_1)
		return channel1_dacmode_preview;
	else
		return channel2_dacmode_preview;
}



char* DU_GetDACModePreview2String(uint32_t Channel)
{
	if(Channel == DAC_CHANNEL_1)
	{
		switch(channel1_dacmode_preview)
		{
			case DAC_USER:
				return "USER";
				break;
			case DAC_RAND:
				return "RAND";
				break;
			case DAC_AUTO:
				return "AUTO";
				break;
			default:
				break;
		}
	}
	else
	{
		switch(channel2_dacmode_preview)
		{
			case DAC_USER:
				return "USER";
				break;
			case DAC_RAND:
				return "RAND";
				break;
			case DAC_AUTO:
				return "AUTO";
				break;
			default:
				break;

		}
	}

	// something went wrong
	return "ERR:DU146";

}



/**
  * @brief 	Calculate the DAC channel output voltage based
  *  		on chanX_amp_count_preview or DOR register
  *
  * @param  Channel The selected DAC channel.
  *         This parameter can be one of the following values:
  *            	@arg DAC_CHANNEL_1: DAC Channel1 selected
  *            	@arg DAC_CHANNEL_2: DAC Channel2 selected (Whenever present)
  * @param	preview Select chanX_amp_count_preview or DOR register
  *
  * @retval DAC channel output voltage
  */

float DU_CalcDACVolts(uint32_t Channel, uint8_t preview)
{
	float result = 0;
	if(Channel == DAC_CHANNEL_1)
	{
		if(preview)
			result = (float)(VREF * ((float)chan1_amp_count_preview/(float)DACRES));
		else
			result = (float)(VREF * ((float)hdac1.Instance->DOR1/(float)DACRES));
	}
	if(Channel == DAC_CHANNEL_2)
	{
		if(preview)
			result = (float)(VREF * ((float)chan2_amp_count_preview/(float)DACRES));
		else
			result = (float)(VREF * ((float)hdac1.Instance->DOR2/(float)DACRES));
	}
	return result;
}

/**
  * @brief	Calculate new register value for DAC output register (DOR) in decimal-counted binary
  *
  *
  * @param volts The requested voltage to be converted
  *
  * @retval The decimal-counted binary version of the volts parameter
  */

uint32_t _CalcNewDOR(float volts)
{
	uint32_t result = (volts * DACRES) / VREF;
	return result;
}

/**
  * @brief	Calculate new register value for auto-reload register (ARR) in decimal-counted binary
  *
  * @param  Channel The selected DAC channel.
  *         This parameter can be one of the following values:
  *            	@arg DAC_CHANNEL_1: DAC Channel1 selected
  *            	@arg DAC_CHANNEL_2: DAC Channel2 selected (Whenever present)
  * @param	hertz The frequency to convert to decimal-counted binary
  *
  *
  * @retval The decimal-counted binary version of the hertz parameter
  */

uint16_t _CalcNewARR(uint16_t Channel, float hertz)
{
	uint32_t result = 0;
	if(Channel == DAC_CHANNEL_1)
		result = (MASTERCLK / hertz) / htim6.Instance->PSC;
	if(Channel == DAC_CHANNEL_2)
		result = (MASTERCLK / hertz) / htim7.Instance->PSC;
	// clamp new ARR max to timer resolution, increase the PSC to get a lower ARR ceiling
	if(result > TIMRES)
		result = TIMRES;
	return result;
}



/**
  * @brief	Calculate the Timer frequency based
  *  		on chanX_freq_count_preview or auto-reload (ARR) register
  *
  * @param  Channel The selected DAC channel.
  *         This parameter can be one of the following values:
  *            	@arg DAC_CHANNEL_1: DAC Channel1 selected
  *            	@arg DAC_CHANNEL_2: DAC Channel2 selected (Whenever present)
  * @param	preview Select the chanX_freq_count_preview or auto-reload (ARR) register
  *
  * @retval The calculated frequency of the timer
  */

float DU_CalcDACFreq(uint32_t Channel, uint8_t preview)
{
	float result = 0;
	if(Channel == DAC_CHANNEL_1)
	{
		if(preview)
			result = (float)MASTERCLK/((float)htim6.Instance->PSC * (float)chan1_freq_count_preview);
		else
			result = (float)MASTERCLK/((float)htim6.Instance->PSC * (float)htim6.Instance->ARR);
	}
	if(Channel == DAC_CHANNEL_2)
	{
		if(preview)
			result = (float)MASTERCLK/((float)htim7.Instance->PSC * (float)chan2_freq_count_preview);
		else
			result = (float)MASTERCLK/((float)htim7.Instance->PSC * (float)htim7.Instance->ARR);
	}
	return result;
}



/**
  * @brief Set chan1_amp_count_preview to new voltage
  *
  * @param  Channel The selected DAC channel.
  *         This parameter can be one of the following values:
  *            	@arg DAC_CHANNEL_1: DAC Channel1 selected
  *            	@arg DAC_CHANNEL_2: DAC Channel2 selected (Whenever present)
  * @param	new_volts The new voltage value to set to chan1_amp_count_preview
  *
  * @retval none
  */

void DU_SetVoltagePreview(uint32_t Channel, float new_volts)
{
	if (Channel == DAC_CHANNEL_1)
	{
		chan1_amp_count_preview = _CalcNewDOR(new_volts);
		printf("New DAC_CHANNEL_1 Volt Request: %2.2fV\n", (float)DU_CalcDACVolts(DAC_CHANNEL_1, 1));
	}

	else if (Channel == DAC_CHANNEL_2)
	{
		chan2_amp_count_preview = _CalcNewDOR(new_volts);
		printf("New DAC_CHANNEL_2 Volt Request: %2.2fV\n", (float)DU_CalcDACVolts(DAC_CHANNEL_2,1));
	}
}

/**
  * @brief	Set the DAC DHR12R1 register to output a new voltage value
  *
  * @param  Channel The selected DAC channel.
  *         This parameter can be one of the following values:
  *            	@arg DAC_CHANNEL_1: DAC Channel1 selected
  *            	@arg DAC_CHANNEL_2: DAC Channel2 selected (Whenever present)
  *
  * @retval none
  */

void DU_SetVoltage(uint32_t Channel)
{
	// start debug counter (DAC requires 1-3 cycles before completing conversion)
	__HAL_TIM_CLEAR_FLAG(&htim15, TIM_FLAG_UPDATE);
	HAL_TIM_Base_Start_IT(&htim15);

	if(DU_isDualChannelMode())
	{
		// update register from the preview variable
		if(chan1_amp_count_preview > (DACRES-1))
		{
			hdac1.Instance->DHR12R1 = (DACRES-1);
			chan1_amp_count_preview = (DACRES-1);
		}
		else
		{
			hdac1.Instance->DHR12R1 = chan1_amp_count_preview;
		}
		// update register from the preview variable
		if(chan2_amp_count_preview > (DACRES-1))
		{
			hdac1.Instance->DHR12R2 = (DACRES-1);
			chan2_amp_count_preview = (DACRES-1);
		}
		else
		{
			hdac1.Instance->DHR12R2 = chan2_amp_count_preview;
		}
	}
	else
	{
		if (Channel == DAC_CHANNEL_1)
		{
			// update register from the preview variable
			if(chan1_amp_count_preview > (DACRES-1))
			{
				hdac1.Instance->DHR12R1 = (DACRES-1);
				chan1_amp_count_preview = (DACRES-1);
			}
			else
			{
				hdac1.Instance->DHR12R1 = chan1_amp_count_preview;
			}

		}

		else if (Channel == DAC_CHANNEL_2)
		{
			// update register from the preview variable
			if(chan2_amp_count_preview > (DACRES-1))
			{
				hdac1.Instance->DHR12R2 = (DACRES-1);
				chan2_amp_count_preview = (DACRES-1);
			}
			else
			{
				hdac1.Instance->DHR12R2 = chan2_amp_count_preview;
			}

		}
	}

}

/**
  * @brief	Zero the preview variable
  *
  * @retval none
  */

void DU_ClearVoltagePreview(uint32_t Channel)
{
	if(Channel == DAC_CHANNEL_1)
		chan1_amp_count_preview = 0;
	else
		chan2_amp_count_preview = 0;
}

/**
  * @brief	Increase or decrease the chan1_amp_count_preview variable
  *
  * @param  Channel The selected DAC channel.
  *         This parameter can be one of the following values:
  *            	@arg DAC_CHANNEL_1: DAC Channel1 selected
  *            	@arg DAC_CHANNEL_2: DAC Channel2 selected (Whenever present)
  * @param	Increase 1=Increase,0=Decrease
  *
  * @retval
  */

void _ChangeVoltage(uint32_t Channel, int increase)
{
	if (Channel == DAC_CHANNEL_1)
	{
		if(increase)
			chan1_amp_count_preview += MAXAMPSTEP;
		else
			chan1_amp_count_preview -= MAXAMPSTEP;

		if((chan1_amp_count_preview < 1) | (chan1_amp_count_preview > DACRES))
			chan1_amp_count_preview = 0;

	}
	else if (Channel == DAC_CHANNEL_2)
	{
		if(increase)
			chan2_amp_count_preview += MAXAMPSTEP;
		else
			chan2_amp_count_preview -= MAXAMPSTEP;

		if((chan2_amp_count_preview < 1) | (chan2_amp_count_preview > DACRES))
			chan2_amp_count_preview = 0;

	}
}

/**
  * @brief	Zero the DAC output register and the preview variable
  *
  * @param  Channel The selected DAC channel.
  *         This parameter can be one of the following values:
  *            	@arg DAC_CHANNEL_1: DAC Channel1 selected
  *            	@arg DAC_CHANNEL_2: DAC Channel2 selected (Whenever present)
  * @param
  * 		@arg @ref
  *
  *
  * @retval none
  */

void _ResetDACVoltage(uint32_t Channel)
{
	HAL_DAC_SetValue(&hdac1,Channel, DAC_ALIGN_8B_R, 0);
	if (Channel == DAC_CHANNEL_1)
	{
		chan1_amp_count_preview = 0;
	}
	else if (Channel == DAC_CHANNEL_2)
	{
		chan2_amp_count_preview = 0;
	}

}

/**
  * @brief Reset the selected DAC channel freq and update chanX_freq_hertz variable
  *
  * @param  Channel The selected DAC channel.
  *         This parameter can be one of the following values:
  *            	@arg DAC_CHANNEL_1: DAC Channel1 selected
  *            	@arg DAC_CHANNEL_2: DAC Channel2 selected (Whenever present)
  *
  * @retval none
  */

void _ResetDACFreq(uint32_t Channel)
{
	HAL_DAC_SetValue(&hdac1,Channel, DAC_ALIGN_8B_R, 0);
	if (Channel == DAC_CHANNEL_1)
	{
		//chan1FreqCount = 0;
		// recalculate freq (hertz) output
		chan1_freq_hertz = DU_CalcDACFreq(Channel, 0);
		//chan1_freq_hertz = (float)MASTERCLK/(htim6.Instance->PSC * htim6.Instance->ARR);
	}
	else if (Channel == DAC_CHANNEL_2)
	{
		//chan2FreqCount = 0;
		// recalculate freq (hertz) output
		chan2_freq_hertz = DU_CalcDACFreq(Channel, 0);
		//chan2_freq_hertz = (float)MASTERCLK/(htim7.Instance->PSC * htim7.Instance->ARR);
	}

}

/**
  * @brief Sets Timer auto-reload register (ARR) with chanX_freq_count_preview variable
  *
  * @param  Channel The selected DAC channel.
  *         This parameter can be one of the following values:
  *            	@arg DAC_CHANNEL_1: DAC Channel1 selected
  *            	@arg DAC_CHANNEL_2: DAC Channel2 selected (Whenever present)
  *
  * @retval none
  */

void DU_SetFreq(uint32_t Channel)
{

	// start debug counter (DAC requires 1-3 cycles before completing conversion)
	__HAL_TIM_CLEAR_FLAG(&htim15, TIM_FLAG_UPDATE);
	HAL_TIM_Base_Start_IT(&htim15);


	if (Channel == DAC_CHANNEL_1)
	{
		htim6.Instance->ARR = chan1_freq_count_preview;
		//printf("New DAC_CHANNEL_1 Freq Setting: %2.2fHz\n", (float)DU_CalcDACFreq(DAC_CHANNEL_1, 0 ));
		//chan1_freq_hertz = (float)MASTERCLK/(htim6.Instance->PSC * htim6.Instance->ARR);
		//printf("Chan1 Freq: %2.4fHz (%u)\n", chan1_freq_hertz, chan1FreqCount);
	}
	else if (Channel == DAC_CHANNEL_2)
	{
		htim7.Instance->ARR = chan2_freq_count_preview;
		//printf("New DAC_CHANNEL_2 Freq Setting: %2.2fHz\n", (float)DU_CalcDACFreq(DAC_CHANNEL_2, 0 ));
		//chan2_freq_hertz = (float)MASTERCLK/(htim7.Instance->PSC * htim7.Instance->ARR);
		//printf("Chan2 Freq: %2.4fHz (%u)\n", chan2_freq_hertz, chan2FreqCount);
	}
}

/**
  * @brief Reset the chanX_freq_count_preview variable
  *
  * @retval none
  */

void DU_ClearFreqPreview(uint32_t Channel)
{

	if(Channel == DAC_CHANNEL_1)
		chan1_freq_count_preview = TIMRES;
	else
		chan2_freq_count_preview = TIMRES;
}

/**
  * @brief	Update the chanX_freq_count_preview variable
  *
  * @param  Channel The selected DAC channel.
  *         This parameter can be one of the following values:
  *            	@arg DAC_CHANNEL_1: DAC Channel1 selected
  *            	@arg DAC_CHANNEL_2: DAC Channel2 selected (Whenever present)
  * @param new_hertz The new value
  *
  * @retval none
  */

void DU_SetFreqPreview(uint32_t Channel, float new_hertz)
{
	if (Channel == DAC_CHANNEL_1)
	{
		chan1_freq_count_preview = _CalcNewARR(DAC_CHANNEL_1, new_hertz);
		printf("New DAC_CHANNEL_1 Freq Request: %2.2fHz\n", (float)DU_CalcDACFreq(DAC_CHANNEL_1,1));
		//htim6.Instance->ARR = (uint32_t)(MASTERCLK/(htim6.Instance->PSC * newHertz));
		//printf("New Freq request: %lu\n", newHertz);
		//chan1FreqHz = (float)MASTERCLK/(htim6.Instance->PSC * htim6.Instance->ARR);
		//printf("Chan1 Freq: %2.4fHz (%u)\n", chan1FreqHz, chan1FreqCount);
	}
	else if (Channel == DAC_CHANNEL_2)
	{
		chan2_freq_count_preview = _CalcNewARR(DAC_CHANNEL_2, new_hertz);
		printf("New DAC_CHANNEL_2 Freq Request: %2.2fHz\n", (float)DU_CalcDACFreq(DAC_CHANNEL_2,1));
		/*htim7.Instance->ARR = (uint32_t)(MASTERCLK/(htim7.Instance->PSC * newHertz));
		printf("New Freq request: %lu\n", newHertz);
		chan2FreqHz = (float)MASTERCLK/(htim7.Instance->PSC * htim7.Instance->ARR);
		printf("Chan2 Freq: %2.4fHz (%u)\n", chan2FreqHz, chan2FreqCount);
		*/
	}
}

/**
  * @brief 	Increase or decrease the chan1_amp_count_preview variable
  *
  * @param  Channel The selected DAC channel.
  *         This parameter can be one of the following values:
  *            	@arg DAC_CHANNEL_1: DAC Channel1 selected
  *            	@arg DAC_CHANNEL_2: DAC Channel2 selected (Whenever present)
  * @param	increase 1=Increase, 0=Decrease
  *
  * @retval none
  */

void _ChangeFreq(uint32_t Channel, int increase)
{
	if (Channel == DAC_CHANNEL_1)
	{
		// decrement cycle period to increase frequency
		if(increase)
			chan1_freq_count_preview -= MAXFREQSTEP;
		else
			chan1_freq_count_preview += MAXFREQSTEP;

		if((chan1_freq_count_preview < 1) | (chan1_freq_count_preview > TIMRES))
			chan1_freq_count_preview = TIMRES;

	}
	else if (Channel == DAC_CHANNEL_2)
	{
		// decrement cycle period to increase frequency
		if(increase)
			chan2_freq_count_preview -= MAXFREQSTEP;
		else
			chan2_freq_count_preview += MAXFREQSTEP;

		if((chan2_freq_count_preview < 1) | (chan2_freq_count_preview > TIMRES))
			chan2_freq_count_preview = TIMRES;

	}
}

/**
  * @brief 	Cycle to next DAC mode
  *
  * @param  Channel The selected DAC channel.
  *         This parameter can be one of the following values:
  *            	@arg DAC_CHANNEL_1: DAC Channel1 selected
  *            	@arg DAC_CHANNEL_2: DAC Channel2 selected (Whenever present)
  *
  * @retval none
  */

void _CycleDACMode(uint32_t Channel)
{
	uint8_t currentDacMode = DU_GetDACModeActual(Channel);
	if(currentDacMode == DAC_USER)
	{
		DU_SetDACModeActual(Channel, DAC_AUTO);
	}
	else if (currentDacMode == DAC_AUTO)
	{
		DU_SetDACModeActual(Channel, DAC_RAND);
	}
	else if (currentDacMode == DAC_RAND)
	{
		DU_SetDACModeActual(Channel, DAC_USER);
	}
}

/**
  * @brief Increase selected DAC channel voltage or frequency
  *
  * @param  Channel The selected DAC channel.
  *         This parameter can be one of the following values:
  *            	@arg DAC_CHANNEL_1: DAC Channel1 selected
  *            	@arg DAC_CHANNEL_2: DAC Channel2 selected (Whenever present)
  *
  * @retval none
  */

void DU_IncreaseDAC(uint32_t Channel)
{
	DM_SetBlinkTimer(1);
	uint8_t currentDacMode = DU_GetDACModeActual(Channel);
	if(currentDacMode == DAC_USER)
	{
		_ChangeVoltage(Channel, 1);
		DU_SetVoltage(Channel);
	}
	else if (currentDacMode == DAC_AUTO)
	{
		_ChangeFreq(Channel, 1);
		DU_SetFreq(Channel);
	}
	else if (currentDacMode == DAC_RAND)
	{
		_ChangeFreq(Channel, 1);
		DU_SetFreq(Channel);
	}
}

/**
  * @brief  Decrease selected DAC channel voltage or frequency
  *
  * @param  Channel The selected DAC channel.
  *         This parameter can be one of the following values:
  *            	@arg DAC_CHANNEL_1: DAC Channel1 selected
  *            	@arg DAC_CHANNEL_2: DAC Channel2 selected (Whenever present)

  * @retval none
  */

void DU_DecreaseDAC(uint32_t Channel)
{
	DM_SetBlinkTimer(1);
	uint8_t currentDacMode = DU_GetDACModeActual(Channel);
	if(currentDacMode == DAC_USER)
	{
		_ChangeVoltage(Channel, 0);
		DU_SetVoltage(Channel);
	}
	else if (currentDacMode == DAC_AUTO)
	{
		_ChangeFreq(Channel, 0);
		DU_SetFreq(Channel);
	}
	else if (currentDacMode == DAC_RAND)
	{
		_ChangeFreq(Channel, 0);
		DU_SetFreq(Channel);
	}
}

/**
  * @brief	Return the current DAC mode for the selected channel as enumerated value
  *
  * @param  Channel The selected DAC channel.
  *         This parameter can be one of the following values:
  *            	@arg DAC_CHANNEL_1: DAC Channel1 selected
  *            	@arg DAC_CHANNEL_2: DAC Channel2 selected (Whenever present)
  *
  * @retval  The DAC mode
  * 		@arg	DAC_ERROR: 	illegal mode request
  *			@arg 	DAC_USER:	Normal mode
  *			@arg 	DAC_AUTO:	Auto mode
  *			@arg 	DAC_RAND:	Random mode
  */

dacmode_t DU_GetDACModeActual(uint32_t Channel)
{
	volatile uint32_t hdac_cr = hdac1.Instance->CR;
	if (Channel == DAC_CHANNEL_1)
	{
		if	(hdac_cr & DAC_CR_WAVE1_0)
		{
			return DAC_RAND;
		}
		else if (hdac_cr & DAC_CR_WAVE1_1)
		{
			return DAC_AUTO;
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
			return DAC_RAND;
		}
		else if (hdac_cr & DAC_CR_WAVE2_1)
		{
			return DAC_AUTO;
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

/**
  * @brief	Return the current DAC mode for the selected channel as string
  *
  * @param  Channel The selected DAC channel.
  *         This parameter can be one of the following values:
  *            	@arg DAC_CHANNEL_1: DAC Channel1 selected
  *            	@arg DAC_CHANNEL_2: DAC Channel2 selected (Whenever present)
  *
  * @retval  The DAC mode
  *
  */

char* DU_GetDACModeActual2String(uint32_t Channel)
{
	volatile uint32_t hdac_cr = hdac1.Instance->CR;
	if (Channel == DAC_CHANNEL_1)
	{
		if	(hdac_cr & DAC_CR_WAVE1_0)
		{
			return "RAND";
		}
		else if (hdac_cr & DAC_CR_WAVE1_1)
		{
			return "AUTO";
		}
		else
		{
			return "USER";
		}
	}
	else if (Channel == DAC_CHANNEL_2)
	{
		if	(hdac_cr & DAC_CR_WAVE2_0)
		{
			return "RAND";
		}
		else if (hdac_cr & DAC_CR_WAVE2_1)
		{
			return "AUTO";
		}
		else
		{
			return "USER";
		}
	}
	else
	{
		return "Error";
	}

}

/**
  * @brief Set the DAC mode, resets the preview values
  *
  * @param  Channel The selected DAC channel.
  *         This parameter can be one of the following values:
  *            	@arg DAC_CHANNEL_1: DAC Channel1 selected
  *            	@arg DAC_CHANNEL_2: DAC Channel2 selected (Whenever present)
  * @param	mode The selected DAC mode
  * 			@arg 	DAC_ERROR: 	illegal mode request
  *				@arg 	DAC_USER:	Normal mode
  *				@arg 	DAC_AUTO:	Auto mode
  *				@arg 	DAC_RAND:	Random mode
  *
  * @retval none
  */

void DU_SetDACModeActual(uint32_t Channel, dacmode_t mode)
{

	if (Channel == DAC_CHANNEL_1)
	{
		hdac1.Instance->CR &= ~(DAC_CR_WAVE1_Msk | DAC_CR_MAMP1_Msk);
		if(mode == DAC_USER)
		{
			htim6.Instance->PSC = 255;
			hdac1.Instance->CR &= ~(DAC_CR_WAVE1_0 | DAC_CR_WAVE1_1);
			//_ResetDACVoltage(DAC_CHANNEL_1);
		}
		else if (mode == DAC_RAND)
		{
			htim6.Instance->PSC = 4096;
			hdac1.Instance->CR |= (DAC_CR_WAVE1_0 | DAC_LFSRUNMASK_BITS11_0);
			//_ResetDACFreq(DAC_CHANNEL_1);
		}
		else if (mode == DAC_AUTO)
		{
			htim6.Instance->PSC = 255;
			hdac1.Instance->CR |= (DAC_CR_WAVE1_1 | DAC_TRIANGLEAMPLITUDE_4095);
			//_ResetDACFreq(DAC_CHANNEL_1);
		}
	}
	else if (Channel == DAC_CHANNEL_2)
	{
		hdac1.Instance->CR &= ~(DAC_CR_WAVE2_Msk | DAC_CR_MAMP2_Msk);
		if(mode == DAC_USER)
		{
			htim7.Instance->PSC = 255;
			hdac1.Instance->CR &= ~(DAC_CR_WAVE2_0 | DAC_CR_WAVE2_1);
			//_ResetDACVoltage(DAC_CHANNEL_2);
		}
		else if (mode == DAC_RAND)
		{
			htim7.Instance->PSC = 4096;
			hdac1.Instance->CR |= (DAC_CR_WAVE2_0 | (DAC_LFSRUNMASK_BITS11_0 << (Channel & 0x10UL)));
			//_ResetDACFreq(DAC_CHANNEL_2);
		}
		else if (mode == DAC_AUTO)
		{
			htim7.Instance->PSC = 255;
			hdac1.Instance->CR |= (DAC_CR_WAVE2_1 | (DAC_TRIANGLEAMPLITUDE_4095 << (Channel & 0x10UL)));
			//_ResetDACFreq(DAC_CHANNEL_2);
		}
	}

}

/**
  * @brief	Debug output for output values. To be called by delayed action to
  * 		allow for 1-3 cycles required before register update
  *
  * @param  Channel The selected DAC channel.
  *         This parameter can be one of the following values:
  *            	@arg DAC_CHANNEL_1: DAC Channel1 selected
  *            	@arg DAC_CHANNEL_2: DAC Channel2 selected (Whenever present)
  *
  * @retval none
  */

void DU_CompleteCallback(uint32_t Channel)
{
	if(Channel == DAC_CHANNEL_1)
	{
		if(DU_GetDACModeActual(DAC_CHANNEL_1) == DAC_USER)
			printf("New DAC_CHANNEL_1 Volt Setting: %2.2fV\n", DU_CalcDACVolts(DAC_CHANNEL_1, 0 ));
		else
			printf("New DAC_CHANNEL_1 Freq Setting: %2.2fHz\n", (float)DU_CalcDACFreq(DAC_CHANNEL_1, 0 ));
	}
	if(Channel == DAC_CHANNEL_2)
	{
		if(DU_GetDACModeActual(DAC_CHANNEL_2) == DAC_USER)
			printf("New DAC_CHANNEL_2 Volt Setting: %2.2fV\n", DU_CalcDACVolts(DAC_CHANNEL_2, 0 ));
		else
			printf("New DAC_CHANNEL_2 Freq Setting: %2.2fHz\n", (float)DU_CalcDACFreq(DAC_CHANNEL_2, 0 ));
	}

}


/**
  * @brief	Set the active DAC channel
  *
  * @param The active DAC channel.
  *         One of the following values:
  *            	@arg DAC_CHANNEL_1: DAC Channel1 selected
  *            	@arg DAC_CHANNEL_2: DAC Channel2 selected
  *
  *  @retval None
  */

void DU_setActiveDACChannel(uint32_t Channel)
{
	selected_dac_channel = Channel;
	printf("Active DAC Channel = %s", DU_getActiveDACChannel2String());
}

/**
  * @brief	Get the active DAC channel
  *
  * @retval The active DAC channel.
  *         One of the following values:
  *            	@arg DAC_CHANNEL_1: DAC Channel1 selected
  *            	@arg DAC_CHANNEL_2: DAC Channel2 selected
  *
  */

uint32_t DU_getActiveDACChannel()
{
	return selected_dac_channel;
}

/**
  * @brief	Get the active DAC channel
  *
  * @retval The active DAC channel.
  *         One of the following values:
  *            	@arg "CHANNEL 1"
  *            	@arg "CHANNEL 2"
  *
  */

char* DU_getActiveDACChannel2String()
{
	if(selected_dac_channel == DAC_CHANNEL_1)
		return "CH1";
	else
		return "CH2";
}

/**
  * @brief	Set the DAC dual mode status
  *
  * @param enable: 1=Dual Mode enabled, 0=Dual Mode disabled
  *
  * @retval None
  */

void DU_setDualChannelMode(uint8_t enable)
{
	dual_channel_mode = enable;
}


/**
  * @brief	Get the DAC dual mode status
  *
  * @retval boolean: 1=Dual Mode enabled, 0=Dual Mode disabled
  *
  */

uint8_t DU_isDualChannelMode()
{
	return dual_channel_mode;
}

