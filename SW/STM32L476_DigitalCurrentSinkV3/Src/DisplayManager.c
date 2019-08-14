/*
 * displaymanager.c
 *
 *  Created on: Aug 5, 2019
 *      Author: chris
 */

#include <DacUtilities.h>
#include <DisplayManager.h>
#include <InputManager.h>
#include "tim.h"
#include "stm32l4xx_hal.h"
#include "ssd1306.h"
#include "ssd1306_tests.h"


/*  DAC channel context set from user menu button selection. See IM_MenuEXTIHandler() */
uint32_t 	selected_dac_channel = DAC_CHANNEL_1;

/*	Current display state set from user menu button selection. See IM_MenuEXTIHandler() */
displayState_t 		current_display_state = DISPMAIN;

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
	// top menu
	ssd1306_SetCursor(2,3);
	ssd1306_WriteString("DAC1", Font_5x7, White, 1);

	ssd1306_SetCursor(34,3);
	ssd1306_WriteString("INCR", Font_5x7, White, 1);

	ssd1306_SetCursor(66,3);
	ssd1306_WriteString("DAC2", Font_5x7, White, 1);

	ssd1306_SetCursor(97,3);
	ssd1306_WriteString("INCR", Font_5x7, White, 1);

	for(int x=0; x < SSD1306_WIDTH; x++)
	{
		ssd1306_DrawPixel(x, 48, White);
	}
	for(int x=0; x < SSD1306_WIDTH; x++)
	{
		ssd1306_DrawPixel(x, 64, White);
	}

	for(int y=48; y <64 ; y++)
	{
		ssd1306_DrawPixel(64, y, White);
	}
}

/**
  * @brief	Draw data values for DAC_CHANNEL_1
  * 		Called by _DrawMainDisp() and _DrawValueDisp()
  *
  * @param	preview Passed to DU_CalcDACVolts/DU_CalcDACFreq to select register or preview variable
  *
  * @retval None
  */


void _DrawDac1Value(uint8_t preview)
{
    char dac1cnt[32];

    if(DU_GetDACMode(DAC_CHANNEL_1) == DAC_USER)
    {
    	if(preview)
    	{
    		uint8_t digit_length = IM_GetDigitLength();
			switch(digit_length)
			{
				case 0:
					snprintf(dac1cnt, sizeof(dac1cnt), "DAC1: %luV", (uint32_t)DU_CalcDACVolts(DAC_CHANNEL_1, preview));
					break;
				case 1:
					snprintf(dac1cnt, sizeof(dac1cnt), "DAC1: %2.0fV", DU_CalcDACVolts(DAC_CHANNEL_1, preview));
					break;
				case 2:
					snprintf(dac1cnt, sizeof(dac1cnt), "DAC1: %2.1fV", DU_CalcDACVolts(DAC_CHANNEL_1, preview));
					break;
				case 3:
					snprintf(dac1cnt, sizeof(dac1cnt), "DAC1: %2.2fV", DU_CalcDACVolts(DAC_CHANNEL_1, preview));
					break;
				case 4:
					snprintf(dac1cnt, sizeof(dac1cnt), "DAC1: %2.3fV", DU_CalcDACVolts(DAC_CHANNEL_1, preview));
					break;
				default:
					snprintf(dac1cnt, sizeof(dac1cnt), "DAC1: %2.3fV", DU_CalcDACVolts(DAC_CHANNEL_1, preview));
					break;
			}
    	}
    	else
    	{
    		snprintf(dac1cnt, sizeof(dac1cnt), "DAC1: %2.3fV", DU_CalcDACVolts(DAC_CHANNEL_1, preview));
    	}


        ssd1306_WriteString(dac1cnt, Font_7x10, White, 0);
    }
    else
    {
    	if(preview)
    	{
    		uint8_t digit_length = IM_GetDigitLength();
			switch(digit_length)
			{
				case 0:
					snprintf(dac1cnt, sizeof(dac1cnt), "DAC1: %luHz", (uint32_t)DU_CalcDACFreq(DAC_CHANNEL_1, preview));
					break;
				case 1:
					snprintf(dac1cnt, sizeof(dac1cnt), "DAC1: %2.0fHz", DU_CalcDACFreq(DAC_CHANNEL_1, preview));
					break;
				case 2:
					snprintf(dac1cnt, sizeof(dac1cnt), "DAC1: %2.1fHz", DU_CalcDACFreq(DAC_CHANNEL_1, preview));
					break;
				case 3:
					snprintf(dac1cnt, sizeof(dac1cnt), "DAC1: %2.2fHz", DU_CalcDACFreq(DAC_CHANNEL_1, preview));
					break;
				case 4:
					snprintf(dac1cnt, sizeof(dac1cnt), "DAC1: %2.3fHz", DU_CalcDACFreq(DAC_CHANNEL_1, preview));
					break;
				default:
					snprintf(dac1cnt, sizeof(dac1cnt), "DAC1: %2.3fHz", DU_CalcDACFreq(DAC_CHANNEL_1, preview));
					break;
			}

    	}
    	else
    	{
    		snprintf(dac1cnt, sizeof(dac1cnt), "DAC1: %2.2fHz", DU_CalcDACFreq(DAC_CHANNEL_1, preview));
    	}

    	ssd1306_WriteString(dac1cnt, Font_7x10, White, 0);
    }
}

/**
  * @brief	Draw data values for DAC_CHANNEL_2
  * 		Called by _DrawMainDisp() and _DrawValueDisp()
  *
  * @param	preview Passed to DU_CalcDACVolts/DU_CalcDACFreq to select register or preview variable
  *
  * @retval None
  */


void _DrawDac2Value(uint8_t preview)
{
    char dac2cnt[32];

    if(DU_GetDACMode(DAC_CHANNEL_2) == DAC_USER)
    {
    	if(preview)
    	{
    		uint8_t placeCount = IM_GetDigitLength();
			switch(placeCount)
			{
				case 0:
					snprintf(dac2cnt, sizeof(dac2cnt), "DAC2: %luV", (uint32_t)DU_CalcDACVolts(DAC_CHANNEL_2, preview));
					break;
				case 1:
					snprintf(dac2cnt, sizeof(dac2cnt), "DAC2: %2.0fV", DU_CalcDACVolts(DAC_CHANNEL_2, preview));
					break;
				case 2:
					snprintf(dac2cnt, sizeof(dac2cnt), "DAC2: %2.1fV", DU_CalcDACVolts(DAC_CHANNEL_2, preview));
					break;
				case 3:
					snprintf(dac2cnt, sizeof(dac2cnt), "DAC2: %2.2fV", DU_CalcDACVolts(DAC_CHANNEL_2, preview));
					break;
				case 4:
					snprintf(dac2cnt, sizeof(dac2cnt), "DAC2: %2.3fV", DU_CalcDACVolts(DAC_CHANNEL_2, preview));
					break;
				default:
					snprintf(dac2cnt, sizeof(dac2cnt), "DAC2: %2.3fV", DU_CalcDACVolts(DAC_CHANNEL_2, preview));
					break;
			}
    	}
    	else
    	{
    		snprintf(dac2cnt, sizeof(dac2cnt), "DAC2: %2.3fV", DU_CalcDACVolts(DAC_CHANNEL_2, preview));
    	}


        ssd1306_WriteString(dac2cnt, Font_7x10, White, 0);
    }
    else
    {
    	if(preview)
    	{
    		uint8_t placeCount = IM_GetDigitLength();
			switch(placeCount)
			{
				case 0:
					snprintf(dac2cnt, sizeof(dac2cnt), "DAC2: %luHz", (uint32_t)DU_CalcDACFreq(DAC_CHANNEL_2, preview));
					break;
				case 1:
					snprintf(dac2cnt, sizeof(dac2cnt), "DAC2: %2.0fHz", DU_CalcDACFreq(DAC_CHANNEL_2, preview));
					break;
				case 2:
					snprintf(dac2cnt, sizeof(dac2cnt), "DAC2: %2.1fHz", DU_CalcDACFreq(DAC_CHANNEL_2, preview));
					break;
				case 3:
					snprintf(dac2cnt, sizeof(dac2cnt), "DAC2: %2.2fHz", DU_CalcDACFreq(DAC_CHANNEL_2, preview));
					break;
				case 4:
					snprintf(dac2cnt, sizeof(dac2cnt), "DAC2: %2.3fHz", DU_CalcDACFreq(DAC_CHANNEL_2, preview));
					break;
				default:
					snprintf(dac2cnt, sizeof(dac2cnt), "DAC2: %2.3fHz", DU_CalcDACFreq(DAC_CHANNEL_2, preview));
					break;
			}

    	}
    	else
    	{
    		snprintf(dac2cnt, sizeof(dac2cnt), "DAC2: %2.2fHz", DU_CalcDACFreq(DAC_CHANNEL_2, preview));
    	}

    	ssd1306_WriteString(dac2cnt, Font_7x10, White, 0);
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
    ssd1306_SetCursor(8, 20);
    _DrawDac1Value(0);

    ssd1306_SetCursor(8, 35);
    _DrawDac2Value(0);

    // bottom status
	ssd1306_SetCursor(2, 50);
	uint8_t mode = DU_GetDACMode(DAC_CHANNEL_1);
	switch(mode)
	{
	case 1:
		ssd1306_WriteString("1:USER", Font_5x7, White, 1);
		break;
	case 2:
		ssd1306_WriteString("1:AUTO", Font_5x7, White, 1);
		break;
	case 3:
		ssd1306_WriteString("1:RAND", Font_5x7, White, 1);
		break;
	}

	ssd1306_SetCursor(65, 50);
	mode = DU_GetDACMode(DAC_CHANNEL_2);
	switch(mode)
	{
	case 1:
		ssd1306_WriteString("2:USER", Font_5x7, White, 1);
		break;
	case 2:
		ssd1306_WriteString("2:AUTO", Font_5x7, White, 1);
		break;
	case 3:
		ssd1306_WriteString("2:RAND", Font_5x7, White, 1);
		break;
	}

}

/**
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

/**
  * @brief 	Draw mode screen data
  *			Called by DM_UpdateDisplay()
  *
  * @retval None
  */


void _DrawModeDisp()
{
    ssd1306_SetCursor(0, 20);

    switch(selected_dac_channel)
    {
    case DAC_CHANNEL_1:
    	ssd1306_WriteString("Enter DAC1 mode:", Font_7x10, White, 0);
    	ssd1306_SetCursor(10, 40);
    	ssd1306_WriteString(DU_GetDACMode2String(DAC_CHANNEL_1), Font_7x10, White, 0);
    	break;
    case DAC_CHANNEL_2:
    	ssd1306_WriteString("Enter DAC2 Mode:", Font_7x10, White, 0);
    	ssd1306_SetCursor(10, 40);
    	ssd1306_WriteString(DU_GetDACMode2String(DAC_CHANNEL_2), Font_7x10, White, 0);
    	break;
    default:
    	break;
    }
}

/**
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

/**
  * @brief 	Draw Value Set screen data
  * 		Called by DM_UpdateDisplay()
  *
  * @retval None
  */


void _DrawValueDisp()
{
    ssd1306_SetCursor(0, 20);

    switch(selected_dac_channel)
    {
    case DAC_CHANNEL_1:
    	ssd1306_WriteString("Enter DAC1 Value:", Font_7x10, White, 0);
        ssd1306_SetCursor(8, 40);
        if(!blink_display_text)
        	_DrawDac1Value(1);
    	break;
    case DAC_CHANNEL_2:
    	ssd1306_WriteString("Enter DAC2 Value:", Font_7x10, White, 0);
        ssd1306_SetCursor(8, 40);
        if(!blink_display_text)
        	_DrawDac2Value(1);
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
		default:
			break;
	}

	ssd1306_UpdateScreen();
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

	selected_dac_channel = Channel;

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


uint32_t DM_GetSelectedDac()
{
	return selected_dac_channel;
}
