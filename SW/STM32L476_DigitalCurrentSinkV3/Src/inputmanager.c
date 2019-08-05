/*
 * inputmanager.c
 *
 *  Created on: Aug 6, 2019
 *      Author: chris
 */

// HAL dependencies
#include "stm32l4xx_hal.h"

// project dependencies
#include "inputmanager.h"
#include "displaymanager.h"
#include "dac_utils.h"

// 3rd party depedencies
#include "ssd1306.h"

// C LIB
#include <string.h>
#include <stdarg.h>


void im_menuExtiHandler()
{

	if(HAL_GPIO_ReadPin(GPIOD, Btn1_EXT10_Pin) == GPIO_PIN_RESET)
	{
		printf("Button1\n");
		//cycleDACMode(DAC_CHANNEL_1);

		displayState_t theDisplayState = dm_getState();
		switch(theDisplayState)
		{
		case DISPMAIN:
			dm_setState(DAC_CHANNEL_1, DISPMODE);
			break;
		case DISPMODE:
			break;
		case DISPVAL:
			increaseDAC(dm_getSelectedDac());
			break;
		default:
			break;
		}



		printf("DAC1 Mode: %d\n", getDACMode(DAC_CHANNEL_1));
	}
	else if(HAL_GPIO_ReadPin(GPIOD, Btn2_EXT11_Pin) == GPIO_PIN_RESET)
	{
		printf("Button2\n");

		displayState_t theDisplayState = dm_getState();
		switch(theDisplayState)
		{
		case DISPMAIN:
			dm_setState(DAC_CHANNEL_1, DISPVAL);
			break;
		case DISPMODE:
			break;
		case DISPVAL:
			decreaseDAC(dm_getSelectedDac());
			break;
		default:
			break;
		}

	}

	else if(HAL_GPIO_ReadPin(GPIOD, Btn3_EXT12_Pin) == GPIO_PIN_RESET)
	{
		printf("Button3\n");

		//cycleDACMode(DAC_CHANNEL_2);

		displayState_t theDisplayState = dm_getState();
		switch(theDisplayState)
		{
		case DISPMAIN:
			dm_setState(DAC_CHANNEL_2, DISPMODE);
			break;
		case DISPMODE:
			break;
		case DISPVAL:
			break;
		default:
			break;
		}


		printf("DAC2 Mode: %d\n", getDACMode(DAC_CHANNEL_2));
	}
	else if(HAL_GPIO_ReadPin(GPIOD, Btn4_EXT13_Pin) == GPIO_PIN_RESET)
	{
		printf("Button4\n");

		displayState_t theDisplayState = dm_getState();
		switch(theDisplayState)
		{
		case DISPMAIN:
			dm_setState(DAC_CHANNEL_2, DISPVAL);
			break;
		case DISPMODE:
			dm_setState(DAC_CHANNEL_2, DISPMAIN);
			break;
		case DISPVAL:
			dm_setState(DAC_CHANNEL_2, DISPMAIN);
			break;
		default:
			break;
		}
	}
}
