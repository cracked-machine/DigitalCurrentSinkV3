/*
 * displaymanager.c
 *
 *  Created on: Aug 5, 2019
 *      Author: chris
 */

#include "displaymanager.h"

#include "tim.h"
#include "stm32l4xx_hal.h"
#include "dac_utils.h"
#include "ssd1306.h"
#include "ssd1306_tests.h"

selectedDacChan_t 	DACSELECT = DAC_CHANNEL_1;
displayState_t 		DISPSTATE = DISPMAIN;
uint8_t blink = 0;

void dm_toggleblink()
{
	if(blink)
	{
		blink = 0;
	}
	else
	{
		blink = 1;
	}
}

void dm_setBlinkTimer(uint8_t pBlink)
{
	if(pBlink)
	{
		HAL_TIM_Base_Start_IT(&htim16);
	}
	else
	{
		HAL_TIM_Base_Stop_IT(&htim16);
		blink = 0;
	}
}



void dm_updateDisplay()
{

	ssd1306_Fill(Black);

	switch(DISPSTATE)
	{
		case DISPMAIN:
			dm_drawMainOverlay();
			dm_drawMainDisp();
			break;
		case DISPMODE:
			dm_drawModeOverlay();
			dm_drawModeDisp();
			break;
		case DISPVAL:
			dm_drawValueOverlay();
			dm_drawValueDisp();
			break;
		default:
			break;
	}

	ssd1306_UpdateScreen();
}

void dm_setState(uint32_t Channel, displayState_t State)
{
	if(State < numStates)
	{
		DISPSTATE = State;
	}
	if(Channel < numDacs)
	{
		DACSELECT = Channel;
	}
}

displayState_t dm_getState()
{
	return DISPSTATE;
}

selectedDacChan_t dm_getSelectedDac()
{
	return DACSELECT;
}

void dm_drawModeOverlay()
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

void dm_drawModeDisp()
{
    ssd1306_SetCursor(0, 20);

    switch(DACSELECT)
    {
    case DAC_CHANNEL_1:
    	ssd1306_WriteString("Enter DAC1 mode:", Font_7x10, White, 0);
    	ssd1306_SetCursor(10, 40);
    	ssd1306_WriteString(getDACMode2String(DAC_CHANNEL_1), Font_7x10, White, 0);
    	break;
    case DAC_CHANNEL_2:
    	ssd1306_WriteString("Enter DAC2 Mode:", Font_7x10, White, 0);
    	ssd1306_SetCursor(10, 40);
    	ssd1306_WriteString(getDACMode2String(DAC_CHANNEL_2), Font_7x10, White, 0);
    	break;
    default:
    	break;
    }
}

void dm_drawValueOverlay()
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

void dm_drawValueDisp()
{
    ssd1306_SetCursor(0, 20);

    switch(DACSELECT)
    {
    case DAC_CHANNEL_1:
    	ssd1306_WriteString("Enter DAC1 Value:", Font_7x10, White, 0);
        ssd1306_SetCursor(8, 40);
        if(!blink)
        	dm_drawDac1Value(1);
    	break;
    case DAC_CHANNEL_2:
    	ssd1306_WriteString("Enter DAC2 Value:", Font_7x10, White, 0);
        ssd1306_SetCursor(8, 40);
        if(!blink)
        	dm_drawDac2Value(1);
    	break;
    default:
    	break;
    }

}

void dm_drawDac1Value(uint8_t preview)
{
    char dac1cnt[32];

    if(getDACMode(DAC_CHANNEL_1) != 1)
    {
    	snprintf(dac1cnt, sizeof(dac1cnt), "DAC1: %2.2fHz", calcDACFreq(DAC_CHANNEL_1, preview));
    	ssd1306_WriteString(dac1cnt, Font_7x10, White, 0);
    }
    else
    {
    	snprintf(dac1cnt, sizeof(dac1cnt), "DAC1: %2.3fV", calcDACVolts(DAC_CHANNEL_1, preview));
    	ssd1306_WriteString(dac1cnt, Font_7x10, White, 0);
    }
}

void dm_drawDac2Value(uint8_t preview)
{
    char dac2cnt[32];
    if(getDACMode(DAC_CHANNEL_2) != 1)
    {
    	snprintf(dac2cnt, sizeof(dac2cnt), "DAC2: %2.2fHz", calcDACFreq(DAC_CHANNEL_2, preview));
    	ssd1306_WriteString(dac2cnt, Font_7x10, White, 0);
    }
    else
    {
    	snprintf(dac2cnt, sizeof(dac2cnt), "DAC2: %2.3fV", calcDACVolts(DAC_CHANNEL_2, preview));
    	ssd1306_WriteString(dac2cnt, Font_7x10, White, 0);
    }

}

void dm_drawMainDisp()
{
    ssd1306_SetCursor(8, 20);
    dm_drawDac1Value(0);

    ssd1306_SetCursor(8, 35);
    dm_drawDac2Value(0);

    // bottom status
	ssd1306_SetCursor(2, 50);
	uint8_t mode = getDACMode(DAC_CHANNEL_1);
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
	mode = getDACMode(DAC_CHANNEL_2);
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

void dm_drawMainOverlay()
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
