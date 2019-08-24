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




/*	Current display state set from user menu button selection. See IM_MenuEXTIHandler() */
displayState_t 		current_display_state = HOME_DISP;

/* Boolean state for blink_display_texting display text */
uint8_t blink_display_text = 0;


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
  * @brief	Draw display overlay (no data) for main screen
  *
  * @retval None
  */


void _DrawMainOverlay()
{
	// TOP BORDER
/*
	for(int x=0; x < SSD1306_WIDTH; x++)
	{
		ssd1306_DrawPixel(x, 0, White);
	}
*/
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
	ssd1306_SetCursor(4,3);
	ssd1306_WriteString("SET", Font_5x7, White, 1);

	ssd1306_SetCursor(38,3);
	ssd1306_WriteString("RST", Font_5x7, White, 1);

	ssd1306_SetCursor(76,3);
	ssd1306_WriteString("+", Font_5x7, White, 1);

	ssd1306_SetCursor(107,3);
	ssd1306_WriteString("-", Font_5x7, White, 1);

	// BOTTOM BORDER

	for(int x=0; x < SSD1306_WIDTH; x++)
	{
		ssd1306_DrawPixel(x, 52, White);
	}
		// VERTICAL BARS
		for(int y=52; y <63 ; y++)
		{
			ssd1306_DrawPixel(39, y, White);
		}
		for(int y=52; y <63 ; y++)
		{
			ssd1306_DrawPixel(80, y, White);
		}

}

void _DrawADC1Value()
{
	char value[8];
	sprintf(value, "%lu", dfsdm_out[0] >> 8);
	ssd1306_WriteString(value, Font_5x7, White, 1);
}

void _DrawADC2Value()
{
	char value[8];
	snprintf(value, sizeof(value), "%lu", dfsdm_out[1] >> 8);
	ssd1306_WriteString(value, Font_5x7, White, 1);
}

/**
  * @brief	Draw data values for DAC_CHANNEL_1
  * 		Called by _DrawMainDisp() and _DrawValueDisp()
  *
  * @param	preview Passed to DU_CalcDACVolts/DU_CalcDACFreq to select register or preview variable
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
			new_dac_value = DU_CalcDACVolts(DAC_CHANNEL_1, preview);
			units = "V";
		}
		else
		{
			new_dac_value = DU_CalcDACFreq(DAC_CHANNEL_1, preview);
			units = "Hz";
		}

		uint8_t digit_length = IM_GetDigitLength();
		switch(digit_length)
		{
			case 0:
				snprintf(dac1cnt, sizeof(dac1cnt), "%lu%s", (uint32_t)new_dac_value, units);
				break;
			case 1:
				snprintf(dac1cnt, sizeof(dac1cnt), "%2.0f%s", new_dac_value, units);
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
		if(DU_GetDACModeActual(DAC_CHANNEL_1) == DAC_USER)
		{
			new_dac_value = DU_CalcDACVolts(DAC_CHANNEL_1, preview);
			units = "V";
		}
		else
		{
			new_dac_value = DU_CalcDACFreq(DAC_CHANNEL_1, preview);
			units = "Hz";
		}
		snprintf(dac1cnt, sizeof(dac1cnt), "%2.3f%s", new_dac_value, units);
	}
	ssd1306_WriteString(dac1cnt, Font_5x7, White, 1);
}

/**
  * @brief	Draw data values for DAC_CHANNEL_2
  * 		Called by _DrawMainDisp() and _DrawValueDisp()
  *
  * @param	preview Passed to DU_CalcDACVolts/DU_CalcDACFreq to select register or preview variable
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
			new_dac_value = DU_CalcDACVolts(DAC_CHANNEL_2, preview);
			units = "V";
		}
		else
		{
			new_dac_value = DU_CalcDACFreq(DAC_CHANNEL_2, preview);
			units = "Hz";
		}

		uint8_t placeCount = IM_GetDigitLength();
		switch(placeCount)
		{
			case 0:
				snprintf(dac2cnt, sizeof(dac2cnt), "%lu%s", (uint32_t)new_dac_value, units);
				break;
			case 1:
				snprintf(dac2cnt, sizeof(dac2cnt), "%2.0f%s", new_dac_value, units);
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
		if(DU_GetDACModeActual(DAC_CHANNEL_2) == DAC_USER)
		{
			new_dac_value = DU_CalcDACVolts(DAC_CHANNEL_2, preview);
			units = "V";
		}
		else
		{
			new_dac_value = DU_CalcDACFreq(DAC_CHANNEL_2, preview);
			units = "Hz";
		}
		snprintf(dac2cnt, sizeof(dac2cnt), "%2.3f%s", new_dac_value, units);
	}
	ssd1306_WriteString(dac2cnt, Font_5x7, White, 1);
}

/**
  * @brief	Draw data for main display
  * 		Called by DM_UpdateDisplay()
  *
  * @retval None
  */


void _DrawMainDisp()
{
    ssd1306_SetCursor(8, 20);
    _DrawDAC1Value(0);

    ssd1306_SetCursor(8, 35);
    _DrawDAC2Value(0);

    ssd1306_SetCursor(70, 20);
    _DrawADC1Value();

    ssd1306_SetCursor(70, 35);
    _DrawADC2Value();

    // bottom status
    // DAC_CHANNEL_1 mode status
	ssd1306_SetCursor(2, 55);
	ssd1306_WriteString("1", Font_5x7, White, 0);
	ssd1306_SetCursor(6, 55);
	ssd1306_WriteString(":", Font_5x7, White, 0);
	char dac1mode[16];
	snprintf(dac1mode, sizeof(dac1mode), "%s",DU_GetDACModeActual2String(DAC_CHANNEL_1));
	ssd1306_SetCursor(10, 55);
	ssd1306_WriteString(dac1mode, Font_5x7, White, 1);

	// DAC_CHANNEL_2 mode status
	ssd1306_SetCursor(42, 55);
	ssd1306_WriteString("2:", Font_5x7, White, 0);
	char dac2mode[16];
	snprintf(dac2mode, sizeof(dac2mode), "%s",DU_GetDACModeActual2String(DAC_CHANNEL_2));
	ssd1306_SetCursor(51, 55);
	ssd1306_WriteString(dac2mode, Font_5x7, White, 1);

	// adjustment channel status
	ssd1306_SetCursor(82, 55);
	ssd1306_WriteString("ADJ", Font_5x7, White, 1);
	ssd1306_SetCursor(101, 55);
	ssd1306_WriteString(":", Font_5x7, White, 0);
	char dac_adjust[16];
	// set string to active dac channel CH1 or CH2; OR set to "1+2" for dual mode
	snprintf(dac_adjust, sizeof(dac_adjust), "%s",DU_getActiveDACChannel2String());
	if(DU_isDualChannelMode())
		snprintf(dac_adjust, sizeof(dac_adjust), "1+2");
	ssd1306_SetCursor(105, 55);
	ssd1306_WriteString(dac_adjust, Font_5x7, White, 1);

}

/** // DEPRECATED
  * @brief	Draw mode screen overlay (no data)
  * 		Called by DM_UpdateDisplay()
  *
  * @retval None
  */


void _DrawModeOverlay()
{
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
	ssd1306_SetCursor(97,3);
	ssd1306_WriteString("EXIT", Font_5x7, White, 1);
}

/**	// DEPRECATED
  * @brief 	Draw mode screen data
  *			Called by DM_UpdateDisplay()
  *
  * @retval None
  */


void _DrawModeDisp()
{
    ssd1306_SetCursor(0, 20);

    switch(DU_getActiveDACChannel())
    {
    case DAC_CHANNEL_1:
    	ssd1306_WriteString("Enter DAC1 mode:", Font_7x10, White, 0);
    	ssd1306_SetCursor(10, 40);
    	ssd1306_WriteString(DU_GetDACModeActual2String(DAC_CHANNEL_1), Font_7x10, White, 0);
    	break;
    case DAC_CHANNEL_2:
    	ssd1306_WriteString("Enter DAC2 Mode:", Font_7x10, White, 0);
    	ssd1306_SetCursor(10, 40);
    	ssd1306_WriteString(DU_GetDACModeActual2String(DAC_CHANNEL_2), Font_7x10, White, 0);
    	break;
    default:
    	break;
    }
}

/** // DEPRECATED
  * @brief 	Draw Value Set screen overlay (no data)
  * 		Called by DM_UpdateDisplay()
  *
  * @retval None
  */


void _DrawValueOverlay()
{
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
	ssd1306_SetCursor(12,3);
	ssd1306_WriteString("+", Font_5x7, White, 1);
	ssd1306_SetCursor(45,3);
	ssd1306_WriteString("-", Font_5x7, White, 1);
	ssd1306_SetCursor(70,3);
	ssd1306_WriteString("SET", Font_5x7, White, 1);
	ssd1306_SetCursor(99,3);
	ssd1306_WriteString("EXIT", Font_5x7, White, 1);
}

/** // DEPRECATED
  * @brief 	Draw Value Set screen data
  * 		Called by DM_UpdateDisplay()
  *
  * @retval None
  */


void _DrawValueDisp()
{
    ssd1306_SetCursor(0, 20);

    switch(DU_getActiveDACChannel())
    {
    case DAC_CHANNEL_1:
    	ssd1306_WriteString("Enter DAC1 Value:", Font_7x10, White, 0);
        ssd1306_SetCursor(8, 40);
        if(!blink_display_text)
        	_DrawDAC1Value(1);
    	break;
    case DAC_CHANNEL_2:
    	ssd1306_WriteString("Enter DAC2 Value:", Font_7x10, White, 0);
        ssd1306_SetCursor(8, 40);
        if(!blink_display_text)
        	_DrawDAC2Value(1);
    	break;
    default:
    	break;
    }

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
	ssd1306_WriteString("BACK", Font_5x7, White, 1);
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
    if(DU_isDualChannelMode())
    	sprintf(mode,"[DUAL CHAN MODE]");
    else
    	snprintf(mode, sizeof(mode), "   [%s MODE]", DU_getActiveDACChannel2String());
    ssd1306_WriteString(mode, Font_5x7, White, 1);

    // display program options
    ssd1306_SetCursor(10, 28);
    ssd1306_WriteString("PROGRAMS:", Font_7x10, White, 0);

    ssd1306_SetCursor(10, 40);
    ssd1306_WriteString("1.USER", Font_5x7, White, 1);

    ssd1306_SetCursor(10, 48);
    ssd1306_WriteString("2.AUTO", Font_5x7, White, 1);

    ssd1306_SetCursor(10, 56);
    ssd1306_WriteString("3.RAND", Font_5x7, White, 1);
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
	ssd1306_WriteString("APPLY", Font_5x7, White, 1);
	ssd1306_SetCursor(45,3);
	ssd1306_WriteString("", Font_5x7, White, 1);
	ssd1306_SetCursor(66,3);
	ssd1306_WriteString("BACK", Font_5x7, White, 1);
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
	dacmode_t dacmode;

    ssd1306_SetCursor(0, 15);

    if(DU_isDualChannelMode())
    {
    	char mode[32] = "";
    	// both channels should be set to same mode, so either channel can be used as ref
    	sprintf(mode, "[CH1+2 MODE: %s]", DU_GetDACModePreview2String(DU_getActiveDACChannel()));
    	ssd1306_WriteString(mode, Font_5x7, White, 1);
    	dacmode = DU_GetDACModePreview(DAC_CHANNEL_1);
    }
    else
    {
    	char mode[32] = "";
    	// get the mode for this specific channel
    	sprintf(mode, " [%s MODE: %s]", DU_getActiveDACChannel2String(), DU_GetDACModePreview2String(DU_getActiveDACChannel()));
    	ssd1306_WriteString(mode, Font_5x7, White, 1);
    	dacmode = DU_GetDACModePreview(DU_getActiveDACChannel());
    }

    switch(dacmode)
    {
		case DAC_USER:
		    	if(DU_isDualChannelMode())
		    	{
		    		// show BOTH DAC 1 and DAC 2 params
		    		ssd1306_SetCursor(2, 30);
					ssd1306_WriteString("CH1:", Font_5x7, White, 1);
					ssd1306_SetCursor(27, 30);
					if(!blink_display_text)
						_DrawDAC1Value(1);

					ssd1306_SetCursor(2, 50);
					ssd1306_WriteString("CH2:", Font_5x7, White, 1);
					ssd1306_SetCursor(27, 50);
					if(!blink_display_text)
						_DrawDAC2Value(1);

		    	}
		    	else
		    	{
		    		// show DAC 1 OR DAC 2 params
		    		switch(DU_getActiveDACChannel())
					{
						case DAC_CHANNEL_1:
							ssd1306_SetCursor(2, 30);
							ssd1306_WriteString("CH1:", Font_5x7, White, 1);
							ssd1306_SetCursor(27, 30);
							if(!blink_display_text)
								_DrawDAC1Value(1);
							break;
						case DAC_CHANNEL_2:
							ssd1306_SetCursor(2, 30);
							ssd1306_WriteString("CH2:", Font_5x7, White, 1);
							ssd1306_SetCursor(27, 30);
							if(!blink_display_text)
								_DrawDAC2Value(1);
							break;
						default:
							break;
					}
		    	}


			break;
		case DAC_RAND:
		case DAC_AUTO:

	    	if(DU_isDualChannelMode())
	    	{
	    		// show BOTH DAC 1 and DAC 2 params
	    		ssd1306_SetCursor(2, 30);
				ssd1306_WriteString("CH1:", Font_5x7, White, 1);
				ssd1306_SetCursor(27, 30);
				if(!blink_display_text)
					_DrawDAC1Value(1);

				ssd1306_SetCursor(2, 50);
				ssd1306_WriteString("CH2:", Font_5x7, White, 1);
				ssd1306_SetCursor(27, 50);
				if(!blink_display_text)
					_DrawDAC2Value(1);

	    	}
	    	else
	    	{
	    		// show DAC 1 OR DAC 2 params
	    		switch(DU_getActiveDACChannel())
				{
					case DAC_CHANNEL_1:
						ssd1306_SetCursor(2, 30);
						ssd1306_WriteString("CH1:", Font_5x7, White, 1);
						ssd1306_SetCursor(27, 30);
						if(!blink_display_text)
							_DrawDAC1Value(1);
						break;
					case DAC_CHANNEL_2:
						ssd1306_SetCursor(2, 30);
						ssd1306_WriteString("CH2:", Font_5x7, White, 1);
						ssd1306_SetCursor(27, 30);
						if(!blink_display_text)
							_DrawDAC2Value(1);
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
  * @brief	Main loop for drawing display overlays and data to OLED
  *
  * @retval None
  */


void DM_UpdateDisplay()
{

	ssd1306_Fill(Black);

	switch(current_display_state)
	{
	// DEPRECATED
		case DISPMAIN:
			_DrawMainOverlay();
			_DrawMainDisp();
			break;
		case DISPMODE:
			_DrawModeOverlay();
			_DrawModeDisp();
			break;
		case DISPVAL:
			_DrawValueOverlay();
			_DrawValueDisp();
			break;
	//
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

	DU_setActiveDACChannel(Channel);

}

void DM_ChangeScreen(displayState_t State)
{
	if(State < numStates)
	{
		current_display_state = State;
	}
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
  * @brief 	Returns the DAC channel selected by user.
  * 		Menu button 1/2 for DAC1
  * 		Menu button 3/4 for DAC2
  *
  * @retval DAC_CHANNEL_1/DAC_CHANNEL_2
  */


// moved to DU_getActiveDACChannel()
/*uint32_t DM_GetSelectedDac()
{
	return selected_dac_channel;
}
*/
