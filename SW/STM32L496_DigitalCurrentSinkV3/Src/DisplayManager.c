/*
 * displaymanager.c
 *
 *  Created on: Aug 5, 2019
 *      Author: Chris Sutton
 */

#include <DacUtilities.h>
#include <DisplayManager.h>
#include <InputManager.h>
#include "tim.h"
#include "stm32l4xx_hal.h"
#include "ssd1306.h"
#include "ssd1306_tests.h"
#include "utils.h"
#include "ADCUtilities.h"
#include "SystemConstants.h"


/* the unit (volts/amps/hertz) to draw to the display. Set by InputManager IMReadKeyCol0/1/2 functions */
unitmode_t 		current_unit_mode	= SHOWCURR;

/*	Current display state set from user menu button selection. Set by InputManager IM_MenuEXTIHandler() */
displayState_t 		current_display_state = HOME_DISP;

/* Boolean state for blink_display_texting display text. Don't draw to OLED when 1. Set by TIM1_UP_TIM16_IRQHandler.  */
uint8_t blink_display_text = 0;


// private function declarations
void _DrawDACAmplitudeValue(uint32_t Channel);
void _DrawAmplitudeSelDisp();
void _DrawAmplitudeSelOverlay();
void _DrawParamSelDisp();
void _DrawParamSelOverlay();
void _DrawProgSelDisp();
void _DrawProgSelOverlay();
void _DrawChanSelDisp();
void _DrawChanSelOverlay();
void _DrawMainDisp();
void _DrawMainOverlay();
void _DrawDAC2Value(uint8_t preview);
void _DrawDAC1Value(uint8_t preview);
void _DrawADC2Value();
void _DrawADC1Value();

/**
  * @brief	Set the mode for type of unit to draw on OLED
  *
  *
  * @retval	None
  */

void DM_SetUnitMode(unitmode_t mode)
{
	printf("Changing Unit display mode to %i\n", mode);
	current_unit_mode = mode;
}

/**
  * @brief	Get the mode for type of unit to draw on OLED
  *
  *
  * @retval	None
  */

unitmode_t DM_GetUnitMode()
{
	return current_unit_mode;
}


/**
  * @brief	Toggles the blink_display_text flag used by DisplayManager.
  * 		Called by TIM1_UP_TIM16_IRQHandler
  *
  * @retval	None
  */

void DM_ToggleBlink()
{
	if(blink_display_text)
	{
		blink_display_text = 0;
	}
	else
	{
		blink_display_text = 1;
	}
}

/**
  * @brief	Enable/Disable display blink_display_text.   *
  *
  * @retval None
  */


void DM_SetBlinkTimer(uint8_t pblink_display_text)
{
	if(pblink_display_text)
	{
		HAL_TIM_Base_Start_IT(&htim16);
	}
	else
	{
		HAL_TIM_Base_Stop_IT(&htim16);
		blink_display_text = 0;
	}
}


/**
  * @brief	Main loop for drawing display overlays and data to OLED
  *
  * @retval None
  */


void DM_UpdateDisplay()
{

	ssd1306_Fill(Black);

	switch(current_display_state)
	{
		case HOME_DISP:
			_DrawMainOverlay();
			_DrawMainDisp();
			break;
		case CHANSEL_DISP:
			_DrawChanSelOverlay();
			_DrawChanSelDisp();
			break;

		case PROGSEL_DISP:
			_DrawProgSelOverlay();
			_DrawProgSelDisp();
			break;

		case PARAMS_DISP:
			_DrawParamSelOverlay();
			_DrawParamSelDisp();
			break;

		case AMPLITUDE_DISP:
			_DrawAmplitudeSelOverlay();
			_DrawAmplitudeSelDisp();
			break;

		default:
			break;
	}

	ssd1306_UpdateScreen();

	//printf("%lu - %lu\n", test[0], test[1]);
}

/**
  * @brief	Changes system state
  *
  *
  * @param  Channel The selected DAC channel.
  *         This parameter can be one of the following values:
  *            	@arg DAC_CHANNEL_1: DAC Channel1 selected
  *            	@arg DAC_CHANNEL_2: DAC Channel2 selected (Whenever present)
  *
  * @param	State The selected system states for OLED display.
  *			This paramater can be one of the following values:
  *				@arg DISPMAIN:	Main screen mode
  *				@arg DISPMODE:	Mode select screen mode
  *				@arg DISPVAL:	Value select screen mode
  *
  * @retval None
  */

void DM_SetState(uint32_t Channel, displayState_t State)
{
	if(State < numStates)
	{
		current_display_state = State;
	}

	DU_SetActiveDACChannel(Channel);

}

void DM_ChangeScreen(displayState_t State)
{
	if(State < numStates)
		current_display_state = State;
}

/**
  * @brief Returns the system state  *
  *
  * @retval	displayState_t state
  */


displayState_t DM_GetState()
{
	return current_display_state;
}



/**
  * @brief	Draw display overlay (no data) for main screen
  *
  * @retval None
  */

void _DrawMainOverlay()
{
	// TOP BORDER

	for(int x=0; x < SSD1306_WIDTH; x++)
	{
		ssd1306_DrawPixel(x, 12, White);
	}
	for(int y=0; y < 12; y++)
	{
		ssd1306_DrawPixel(32, y, White);
		ssd1306_DrawPixel(64, y, White);
		ssd1306_DrawPixel(96, y, White);
	}
	// top menu
	ssd1306_SetCursor(0,3);
	ssd1306_WriteString("CHANGE", Font_3x5, White, 0);

	ssd1306_SetCursor(36,3);
	ssd1306_WriteString("RESET", Font_3x5, White, 0);

	ssd1306_SetCursor(76,2);
	ssd1306_WriteString("+", Font_5x7, White, 1);

	ssd1306_SetCursor(107,2);
	ssd1306_WriteString("-", Font_5x7, White, 1);


	ssd1306_SetCursor(0, 26);
	ssd1306_WriteString("CH1:", Font_3x5, White, 0);

	ssd1306_SetCursor(0, 41);
	ssd1306_WriteString("CH2:", Font_3x5, White, 0);

	ssd1306_SetCursor(38, 16);
	ssd1306_WriteString("OUT:", Font_3x5, White, 1);

	ssd1306_SetCursor(95, 16);
	ssd1306_WriteString("IN:", Font_3x5, White, 1);

	// BOTTOM BORDER

	for(int x=0; x < SSD1306_WIDTH; x++)
	{
		ssd1306_DrawPixel(x, 52, White);
	}
		// VERTICAL BARS
		for(int y=52; y <63 ; y++)
		{
			ssd1306_DrawPixel(41, y, White);
		}
		for(int y=52; y <63 ; y++)
		{
			ssd1306_DrawPixel(86, y, White);
		}
}


/**
  * @brief	Draw data for main display
  * 		Called by DM_UpdateDisplay()
  *
  * @retval None
  */

void _DrawMainDisp()
{




    ssd1306_SetCursor(28, 25);
    _DrawDAC1Value(0);

    ssd1306_SetCursor(28, 40);
    _DrawDAC2Value(0);

    ssd1306_SetCursor(85, 25);
    _DrawADC1Value();

    ssd1306_SetCursor(85, 40);
    _DrawADC2Value();

    // bottom status
    // DAC_CHANNEL_1 mode status
	ssd1306_SetCursor(1, 56);
	ssd1306_WriteString("CH1", Font_3x5, White, 0);
	ssd1306_SetCursor(15, 56);
	ssd1306_WriteString(":", Font_3x5, White, 0);
	char dac1mode[16];
	snprintf(dac1mode, sizeof(dac1mode), "%s",DU_GetDACModeActual2String(DAC_CHANNEL_1));
	ssd1306_SetCursor(19, 56);
	ssd1306_WriteString(dac1mode, Font_3x5, White, 0);

	// DAC_CHANNEL_2 mode status
	ssd1306_SetCursor(44, 56);
	ssd1306_WriteString("CH2", Font_3x5, White, 0);
	ssd1306_SetCursor(58, 56);
	ssd1306_WriteString(":", Font_3x5, White, 0);
	char dac2mode[16];
	snprintf(dac2mode, sizeof(dac2mode), "%s",DU_GetDACModeActual2String(DAC_CHANNEL_2));
	ssd1306_SetCursor(63, 56);
	ssd1306_WriteString(dac2mode, Font_3x5, White, 0);

	// adjustment channel status
	ssd1306_SetCursor(89, 56);
	ssd1306_WriteString("ADJ", Font_3x5, White, 0);
	ssd1306_SetCursor(103, 56);
	ssd1306_WriteString(":", Font_3x5, White, 0);
	char dac_adjust[16];
	// set string to active dac channel CH1 or CH2; OR set to "1+2" for dual mode
	snprintf(dac_adjust, sizeof(dac_adjust), "%s",DU_GetActiveDACChannel2String());
	if(DU_IsDualChannelMode())
	{
		snprintf(dac_adjust, sizeof(dac_adjust), "DUAL");
		ssd1306_SetCursor(107, 56);
	}
	else
	{
		ssd1306_SetCursor(109, 56);
	}

	ssd1306_WriteString(dac_adjust, Font_3x5, White, 0);

}


/**
  * @brief 	Draw DAC Channel Select screen overlay (no data)
  * 		Called by DM_UpdateDisplay()
  *
  * @retval None
  */

void _DrawChanSelOverlay()
{
	// TOP HORIZ LINE
	for(int x=0; x < SSD1306_WIDTH; x++)
	{
		ssd1306_DrawPixel(x, 0, White);
	}
	for(int x=0; x < SSD1306_WIDTH; x++)
	{
		ssd1306_DrawPixel(x, 12, White);
	}
	for(int y=0; y < 12; y++)
	{
		ssd1306_DrawPixel(32, y, White);
		ssd1306_DrawPixel(64, y, White);
		ssd1306_DrawPixel(96, y, White);
	}
	ssd1306_SetCursor(7,3);
	ssd1306_WriteString("CH1", Font_5x7, White, 1);
	ssd1306_SetCursor(38,3);
	ssd1306_WriteString("CH2", Font_5x7, White, 1);
	ssd1306_SetCursor(66,3);
	ssd1306_WriteString("DUAL", Font_5x7, White, 1);
	ssd1306_SetCursor(99,3);
	ssd1306_WriteString("EXIT", Font_5x7, White, 1);
}

/**
  * @brief 	Draw DAC Channel Select screen data
  * 		Called by DM_UpdateDisplay()
  *
  * @retval None
  */

void _DrawChanSelDisp()
{
    ssd1306_SetCursor(15, 26);
    ssd1306_WriteString("SELECT CHANNEL", Font_5x7, White, 1);
}


/**
  * @brief 	Draw DAC Program Select screen overlay (no data)
  * 		Called by DM_UpdateDisplay()
  *
  * @retval None
  */

void _DrawProgSelOverlay()
{
	// TOP HORIZ LINE
	for(int x=0; x < SSD1306_WIDTH; x++)
	{
		ssd1306_DrawPixel(x, 0, White);
	}
	for(int x=0; x < SSD1306_WIDTH; x++)
	{
		ssd1306_DrawPixel(x, 12, White);
	}
	for(int y=0; y < 12; y++)
	{
		//ssd1306_DrawPixel(32, y, White);
		ssd1306_DrawPixel(64, y, White);
		ssd1306_DrawPixel(96, y, White);
	}
	ssd1306_SetCursor(15,3);
	ssd1306_WriteString("", Font_5x7, White, 1);
	ssd1306_SetCursor(45,3);
	ssd1306_WriteString("", Font_5x7, White, 1);
	ssd1306_SetCursor(66,3);
	ssd1306_WriteString("PREV", Font_5x7, White, 1);
	ssd1306_SetCursor(99,3);
	ssd1306_WriteString("EXIT", Font_5x7, White, 1);
}


/**
  * @brief 	Draw DAC Program Select screen data
  * 		Called by DM_UpdateDisplay()
  *
  * @retval None
  */

void _DrawProgSelDisp()
{
	// display mode status
	ssd1306_SetCursor(4, 15);

	char mode[32] = "";
    if(DU_IsDualChannelMode())
    	sprintf(mode,"[DUAL CHAN MODE]");
    else
    	snprintf(mode, sizeof(mode), "   [%s MODE]", DU_GetActiveDACChannel2String());
    ssd1306_WriteString(mode, Font_5x7, White, 1);

    // display program options
    ssd1306_SetCursor(10, 28);
    ssd1306_WriteString("PROGRAMS:", Font_5x7, White, 1);

    ssd1306_SetCursor(10, 40);
    ssd1306_WriteString("1.USER", Font_3x5, White, 0);

    ssd1306_SetCursor(10, 48);
    ssd1306_WriteString("2.AUTO", Font_3x5, White, 0);

    ssd1306_SetCursor(10, 56);
    ssd1306_WriteString("3.RAND", Font_3x5, White, 0);
}


/**
  * @brief 	Draw DAC Parameter Select screen overlay (no data)
  * 		Called by DM_UpdateDisplay()
  *
  * @retval None
  */

void _DrawParamSelOverlay()
{
	// TOP HORIZ LINE
	for(int x=0; x < SSD1306_WIDTH; x++)
	{
		ssd1306_DrawPixel(x, 0, White);
	}
	for(int x=0; x < SSD1306_WIDTH; x++)
	{
		ssd1306_DrawPixel(x, 12, White);
	}
	for(int y=0; y < 12; y++)
	{
		//ssd1306_DrawPixel(32, y, White);
		ssd1306_DrawPixel(64, y, White);
		ssd1306_DrawPixel(96, y, White);
	}
	ssd1306_SetCursor(15,3);
	ssd1306_WriteString("NEXT", Font_5x7, White, 1);
	ssd1306_SetCursor(45,3);
	ssd1306_WriteString("", Font_5x7, White, 1);
	ssd1306_SetCursor(66,3);
	ssd1306_WriteString("PREV", Font_5x7, White, 1);
	ssd1306_SetCursor(99,3);
	ssd1306_WriteString("EXIT", Font_5x7, White, 1);
}


/**
  * @brief 	Draw DAC Parameter Select screen data
  * 		Called by DM_UpdateDisplay()
  *
  * @retval None
  */

void _DrawParamSelDisp()
{

	if(DU_IsDualChannelMode())
	{
		// dual/single mode header
	   	char mode[32] = "";
    	sprintf(mode, "[DUAL MODE: %s]", DU_GetDACModePreview2String(DU_GetActiveDACChannel()));
		ssd1306_SetCursor(0, 15);
    	ssd1306_WriteString(mode, Font_5x7, White, 1);

    	// dac ch1 value
		ssd1306_SetCursor(32, 30);
		ssd1306_WriteString("CH1: ", Font_5x7, White, 1);
		ssd1306_SetCursor(65, 30);
		if(!blink_display_text)
			_DrawDAC1Value(1);

	 	// dac ch2 value
		ssd1306_SetCursor(32, 40);
		ssd1306_WriteString("CH2: ", Font_5x7, White, 1);
		ssd1306_SetCursor(65, 40);
		if(!blink_display_text)
			_DrawDAC2Value(1);

	 	// min value warning
		if(DU_GetDACModePreview(DAC_CHANNEL_1) != DAC_USER)
		{
			char min[32] = "";
			if(DU_GetDACModePreview(DAC_CHANNEL_1) == DAC_AUTO)
				snprintf(min, sizeof(min), "[ %2.3f HZ MIN ]", (float)MASTERCLK/(TIM_PSC_AUTOMODE*TIMRES));
			if(DU_GetDACModePreview(DAC_CHANNEL_1) == DAC_RAND)
				snprintf(min, sizeof(min), "[ %2.3f HZ MIN ]", (float)MASTERCLK/(TIM_PSC_RANDMODE*TIMRES));
			ssd1306_SetCursor(18, 55);
			ssd1306_WriteString(min, Font_3x5, White, 0);
		}

	}
	else
	{
		char mode[32] = "";
		char min[32] = "";
		// dual/single mode header
		sprintf(mode, " [%s MODE: %s]", DU_GetActiveDACChannel2String(), DU_GetDACModePreview2String(DU_GetActiveDACChannel()));
		ssd1306_SetCursor(0, 15);
		ssd1306_WriteString(mode, Font_5x7, White, 1);



		switch(DU_GetActiveDACChannel())
		{
			default:
			case DAC_CHANNEL_1:
			 	// dac ch1 value
				ssd1306_SetCursor(32, 30);
				ssd1306_WriteString("CH1: ", Font_5x7, White, 1);
				ssd1306_SetCursor(65, 30);
				if(!blink_display_text)
					_DrawDAC1Value(1);

			 	// min value warning
				if(DU_GetDACModePreview(DAC_CHANNEL_1) == DAC_RAND)
					snprintf(min, sizeof(min), "[ %2.3f HZ MIN ]", (float)MASTERCLK/(TIM_PSC_RANDMODE*TIMRES));
				if(DU_GetDACModePreview(DAC_CHANNEL_1) == DAC_AUTO)
					snprintf(min, sizeof(min), "[ %2.3f HZ MIN ]", (float)MASTERCLK/(TIM_PSC_AUTOMODE*TIMRES));

				break;

			case DAC_CHANNEL_2:
			 	// dac ch2 value
				ssd1306_SetCursor(32, 30);
				ssd1306_WriteString("CH2: ", Font_5x7, White, 1);
				ssd1306_SetCursor(65, 30);
				if(!blink_display_text)
					_DrawDAC2Value(1);

			 	// min value warning
				if(DU_GetDACModePreview(DAC_CHANNEL_2) == DAC_RAND)
					snprintf(min, sizeof(min), "[ %2.3f HZ MIN ]", (float)MASTERCLK/(TIM_PSC_RANDMODE*TIMRES));
				if(DU_GetDACModePreview(DAC_CHANNEL_2) == DAC_AUTO)
					snprintf(min, sizeof(min), "[ %2.3f HZ MIN ]", (float)MASTERCLK/(TIM_PSC_AUTOMODE*TIMRES));

				break;

		}

		ssd1306_SetCursor(18, 45);
		ssd1306_WriteString(min, Font_3x5, White, 0);


	}
}

/**
  * @brief 	Draw DAC Parameter Select screen overlay (no data)
  * 		Called by DM_UpdateDisplay()
  *
  * @retval None
  */

void _DrawAmplitudeSelOverlay()
{
	// TOP HORIZ LINE
	for(int x=0; x < SSD1306_WIDTH; x++)
	{
		ssd1306_DrawPixel(x, 0, White);
	}
	for(int x=0; x < SSD1306_WIDTH; x++)
	{
		ssd1306_DrawPixel(x, 12, White);
	}
	for(int y=0; y < 12; y++)
	{
		//ssd1306_DrawPixel(32, y, White);
		ssd1306_DrawPixel(64, y, White);
		ssd1306_DrawPixel(96, y, White);
	}
	ssd1306_SetCursor(15,3);
	ssd1306_WriteString("APPLY", Font_5x7, White, 1);
	ssd1306_SetCursor(45,3);
	ssd1306_WriteString("", Font_5x7, White, 1);
	ssd1306_SetCursor(66,3);
	ssd1306_WriteString("PREV", Font_5x7, White, 1);
	ssd1306_SetCursor(99,3);
	ssd1306_WriteString("EXIT", Font_5x7, White, 1);
}


/**
  * @brief 	Draw DAC Parameter Select screen data
  * 		Called by DM_UpdateDisplay()
  *
  * @retval None
  */

void _DrawAmplitudeSelDisp()
{
	dacmode_t dacmode;

    ssd1306_SetCursor(0, 15);

    if(DU_IsDualChannelMode())
    {
    	char mode[32] = "";
    	// both channels should be set to same mode, so either channel can be used as ref
    	sprintf(mode, "[DUAL MODE: %s]", DU_GetDACModePreview2String(DU_GetActiveDACChannel()));
    	ssd1306_WriteString(mode, Font_5x7, White, 1);
    	dacmode = DU_GetDACModePreview(DAC_CHANNEL_1);
    }
    else
    {
    	char mode[32] = "";
    	// get the mode for this specific channel
    	sprintf(mode, " [%s MODE: %s]", DU_GetActiveDACChannel2String(), DU_GetDACModePreview2String(DU_GetActiveDACChannel()));
    	ssd1306_WriteString(mode, Font_5x7, White, 1);
    	dacmode = DU_GetDACModePreview(DU_GetActiveDACChannel());
    }

    switch(dacmode)
    {
		case DAC_USER:
			// not applicable for setting triangle amplitude
			break;
		case DAC_RAND:
		case DAC_AUTO:

	    	if(DU_IsDualChannelMode())
	    	{
	    		// show BOTH DAC 1 and DAC 2 params
	    		_DrawDACAmplitudeValue(DAC_CHANNEL_1);
	    		_DrawDACAmplitudeValue(DAC_CHANNEL_2);

	    	}
	    	else
	    	{
	    		// show DAC 1 OR DAC 2 params
	    		switch(DU_GetActiveDACChannel())
				{
					case DAC_CHANNEL_1:
			    		_DrawDACAmplitudeValue(DAC_CHANNEL_1);
						break;
					case DAC_CHANNEL_2:
			    		_DrawDACAmplitudeValue(DAC_CHANNEL_2);
						break;
					default:
						break;
				}
	    	}
			break;
		default:
			break;
    }
}


/**
  * @brief	Draw ADC Channel 1 data
  *
  *
  * @retval None
  */

void _DrawADC1Value()
{
	unitmode_t unitmode = DM_GetUnitMode();
	char voltvalue[8];
	char currvalue[8];
	char bitvalue[8];


	switch(unitmode)
	{
		default:
		case SHOWCURR:

			snprintf(currvalue, sizeof(currvalue), "%2.3fA", AU_CalcCurrent(ADC_CH0));
			ssd1306_WriteString(currvalue, Font_5x7, White, 1);
			break;

		case SHOWBITS:
			snprintf(bitvalue, sizeof(bitvalue), "%lu", AU_GetADCOutChannel(ADC_CH0));
			ssd1306_WriteString(bitvalue, Font_5x7, White, 1);
			break;

		case SHOWVOLT:
			snprintf(voltvalue, sizeof(voltvalue), "%2.3fV", AU_CalcVoltage(ADC_CH0));
			ssd1306_WriteString(voltvalue, Font_5x7, White, 1);
			break;

	}

}

/**
  * @brief	Draw ADC Channel 2 data
  *
  *
  * @retval None
  */


void _DrawADC2Value()
{
	unitmode_t unitmode = DM_GetUnitMode();
	char voltvalue[8];
	char currvalue[8];
	char bitvalue[8];

	switch(unitmode)
	{
		default:
		case SHOWCURR:

			snprintf(currvalue, sizeof(currvalue), "%2.3fA", AU_CalcCurrent(ADC_CH1));
			ssd1306_WriteString(currvalue, Font_5x7, White, 1);
			break;

		case SHOWBITS:
			snprintf(bitvalue, sizeof(bitvalue), "%lu", AU_GetADCOutChannel(ADC_CH1));
			ssd1306_WriteString(bitvalue, Font_5x7, White, 1);
			break;

		case SHOWVOLT:

			snprintf(voltvalue, sizeof(voltvalue), "%2.3fV", AU_CalcVoltage(ADC_CH1));
			ssd1306_WriteString(voltvalue, Font_5x7, White, 1);
			break;
	}

}

/**
  * @brief	Draw data values for DAC_CHANNEL_1
  * 		Called by _DrawMainDisp() and _DrawValueDisp()
  *
  * @param	preview Passed to DU_CalcVoltsFromBits/DU_CalcFreqFromBits to select register or preview variable
  *
  * @retval None
  */

void _DrawDAC1Value(uint8_t preview)
{
    char dac1cnt[32];
    float new_dac_value;

    char* units;


    // "preview view"expands number length as digits are typed
	if(preview)
	{
		if(DU_GetDACModePreview(DAC_CHANNEL_1) == DAC_USER)
		{
			//new_dac_value = DU_CalcVoltsFromBits(DAC_CHANNEL_1, preview);
			// convert DAC output voltage back to Amps to show on OLED
			new_dac_value = DU_CalcCurrentFromOhmsLaw(DAC_CHANNEL_1, preview);
			units = "A";
		}
		else
		{
			new_dac_value = DU_CalcFreqFromBits(DAC_CHANNEL_1, preview);
			units = "Hz";
		}

		uint8_t digit_length = IM_GetDigitLength();
		switch(digit_length)
		{
			case 0:
				snprintf(dac1cnt, sizeof(dac1cnt), "%lu%s", (uint32_t)new_dac_value, units);
				break;
			case 1:
				snprintf(dac1cnt, sizeof(dac1cnt), "%2.1f%s", new_dac_value, units);
				break;
			case 2:
				snprintf(dac1cnt, sizeof(dac1cnt), "%2.1f%s", new_dac_value, units);
				break;
			case 3:
				snprintf(dac1cnt, sizeof(dac1cnt), "%2.2f%s", new_dac_value, units);
				break;
			case 4:
				snprintf(dac1cnt, sizeof(dac1cnt), "%2.3f%s", new_dac_value, units);
				break;
			default:
				snprintf(dac1cnt, sizeof(dac1cnt), "%2.3f%s", new_dac_value, units);
				break;
    	}


	}
	// "actual view" shows fixed number length
	else
	{
		unitmode_t mode = DM_GetUnitMode();
		switch(mode)
		{
			default:
			case SHOWCURR:
				snprintf(dac1cnt, sizeof(dac1cnt), "%2.3fA", DU_CalcCurrentFromOhmsLaw(DAC_CHANNEL_1, 0));
				break;
			case SHOWVOLT:
				snprintf(dac1cnt, sizeof(dac1cnt), "%2.3fV", DU_CalcVoltsFromBits(DAC_CHANNEL_1, 0));
				break;
			case SHOWBITS:
				snprintf(dac1cnt, sizeof(dac1cnt), "%lu", DU_GetDATDOR(DAC_CHANNEL_1));
				break;
		}
	}

	ssd1306_WriteString(dac1cnt, Font_5x7, White, 1);

}

/**
  * @brief	Draw data values for DAC_CHANNEL_2
  * 		Called by _DrawMainDisp() and _DrawValueDisp()
  *
  * @param	preview Passed to DU_CalcVoltsFromBits/DU_CalcFreqFromBits to select register or preview variable
  *
  * @retval None
  */

void _DrawDAC2Value(uint8_t preview)
{
    char dac2cnt[32];
    char* units;
    float new_dac_value;



    // "preview view"expands number length as digits are typed
	if(preview)
    {
		if(DU_GetDACModePreview(DAC_CHANNEL_2) == DAC_USER)
		{
			//new_dac_value = DU_CalcVoltsFromBits(DAC_CHANNEL_2, preview);
			// convert DAC output voltage back to Amps to show on OLED
			new_dac_value = DU_CalcCurrentFromOhmsLaw(DAC_CHANNEL_2, preview);
			units = "A";
		}
		else
		{
			new_dac_value = DU_CalcFreqFromBits(DAC_CHANNEL_2, preview);
			units = "Hz";
		}

		uint8_t placeCount = IM_GetDigitLength();
		switch(placeCount)
		{
			case 0:
				snprintf(dac2cnt, sizeof(dac2cnt), "%lu%s", (uint32_t)new_dac_value, units);
				break;
			case 1:
				snprintf(dac2cnt, sizeof(dac2cnt), "%2.1f%s", new_dac_value, units);
				break;
			case 2:
				snprintf(dac2cnt, sizeof(dac2cnt), "%2.1f%s", new_dac_value, units);
				break;
			case 3:
				snprintf(dac2cnt, sizeof(dac2cnt), "%2.2f%s", new_dac_value, units);
				break;
			case 4:
				snprintf(dac2cnt, sizeof(dac2cnt), "%2.3f%s", new_dac_value, units);
				break;
			default:
				snprintf(dac2cnt, sizeof(dac2cnt), "%2.3f%s", new_dac_value, units);
				break;
		}


	}
	// "actual view" shows fixed number length
	else
	{
		unitmode_t mode = DM_GetUnitMode();
		switch(mode)
		{
			default:
			case SHOWCURR:
				snprintf(dac2cnt, sizeof(dac2cnt), "%2.3fA", DU_CalcCurrentFromOhmsLaw(DAC_CHANNEL_2, 0));
				break;
			case SHOWVOLT:
				snprintf(dac2cnt, sizeof(dac2cnt), "%2.3fV", DU_CalcVoltsFromBits(DAC_CHANNEL_2, 0));
				break;
			case SHOWBITS:
				snprintf(dac2cnt, sizeof(dac2cnt), "%lu", DU_GetDATDOR(DAC_CHANNEL_2));
				break;
		}


	}
	ssd1306_WriteString(dac2cnt, Font_5x7, White, 1);
}

/**
  * @brief 	draws amplitude value to OLED
  *
  *
  * @retval none
  */

void _DrawDACAmplitudeValue(uint32_t Channel)
{
    if(DU_IsDualChannelMode() && Channel == DAC_CHANNEL_1)
    {
    	ssd1306_SetCursor(2, 30);
    }
    else if(DU_IsDualChannelMode() && Channel == DAC_CHANNEL_2)
    {
    	ssd1306_SetCursor(2, 50);
    }
    else
    {
    	ssd1306_SetCursor(2, 30);
    }


	if(Channel == DAC_CHANNEL_1)
	{
		ssd1306_WriteString("CH1:", Font_5x7, White, 1);
	}
	else
	{
		ssd1306_WriteString("CH2:", Font_5x7, White, 1);
	}


	if(DU_IsDualChannelMode() && Channel == DAC_CHANNEL_1)
	{
		ssd1306_SetCursor(30, 30);
	}
	else if(DU_IsDualChannelMode() && Channel == DAC_CHANNEL_2)
	{
		ssd1306_SetCursor(30, 50);
	}
	else
	{
		ssd1306_SetCursor(30, 30);
	}

	if(!blink_display_text)
	{
		if(DU_GetDACModePreview(Channel) == DAC_AUTO)
			ssd1306_WriteString(DU_GetRampAmplitudeSetting2String(Channel), Font_5x7, White, 1);
		else
			ssd1306_WriteString(DU_GetRandAmplitudeSetting2String(Channel), Font_5x7, White, 1);
	}
}


