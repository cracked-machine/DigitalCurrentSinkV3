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

enum
{
	PIN1_ON,
	PIN1_OFF,
	PIN2_ON,
	PIN2_OFF,
	PIN3_ON,
	PIN3_OFF,
	PIN4_ON,
	PIN4_OFF

} muxSequence;

int muxCount=0;

#define KPDEBUG

uint32_t keypadDebounceCounter = 0;
uint32_t newKeypadDelay = 0;
uint32_t lastKeypadDelay = 0;

// increase delay to decrease bouncing
uint32_t minKeypadBounceDelay = 1;

uint32_t keypadBuffer = 0;
uint32_t keypadBufferMax = 5001;


uint32_t lastKeyPressed = 0;

////////////////////////////////////////////////
///
///		Keypad Util Functions
///
////////////////////////////////////////////////

void setKeypadDebounceCounter(uint16_t pValue)
{
	keypadDebounceCounter += pValue;
}

uint32_t getKeypadDebounceCounter()
{
	return keypadDebounceCounter;
}


void setKeypadBuffer(uint32_t pValue)
{

		keypadBuffer = pValue;

}

uint32_t getKeypadBuffer()
{

	return keypadBuffer;
}


uint32_t getKeypadBufferMax()
{
	return keypadBufferMax;
}

void commitKeypadBuffer()
{
	uint8_t currentMode = getDACMode(dm_getSelectedDac());
	switch(currentMode)
	{
	case DAC_USER:
		setVoltage(dm_getSelectedDac(),(float)keypadBuffer);
		break;
	case DAC_TRI:
		setFreq(dm_getSelectedDac(),keypadBuffer);
		break;

	case DAC_NOISE:
		setFreq(dm_getSelectedDac(),(uint8_t)keypadBuffer);
		break;

	default:
		break;

	}
}

uint32_t concatenate(uint32_t x, uint32_t y) {
	lastKeyPressed = y;
    uint32_t pow = 10;
    uint32_t nextCalculatedValue = (x * pow + y);
    if(nextCalculatedValue >= keypadBufferMax)
    {
    	setKeypadBuffer(x);						// set display using previous entered value

    	//setKeypadBuffer(keypadBufferMax);		// set display using entered value round down to keypadBufferMax
    	commitKeypadBuffer();

    	// reset buffer
    	//setKeypadBuffer(0);
    	return 0;
    }
    return nextCalculatedValue;
}



void im_muxKeys1_4()
{
	switch(muxCount)
	{
	case PIN1_ON:
		HAL_GPIO_WritePin(GPIOE, KP1_GPOUT_Pin, GPIO_PIN_SET);
		muxCount++;
		break;
	case PIN1_OFF:
		HAL_GPIO_WritePin(GPIOE, KP1_GPOUT_Pin, GPIO_PIN_RESET);
		muxCount++;
		break;
	case PIN2_ON:
		HAL_GPIO_WritePin(GPIOE, KP2_GPOUT_Pin, GPIO_PIN_SET);
		muxCount++;
		break;
	case PIN2_OFF:
		HAL_GPIO_WritePin(GPIOE, KP2_GPOUT_Pin, GPIO_PIN_RESET);
		muxCount++;
		break;
	case PIN3_ON:
		HAL_GPIO_WritePin(GPIOE, KP3_GPOUT_Pin, GPIO_PIN_SET);
		muxCount++;
		break;
	case PIN3_OFF:
		HAL_GPIO_WritePin(GPIOE, KP3_GPOUT_Pin, GPIO_PIN_RESET);
		muxCount++;
		break;
	case PIN4_ON:
		HAL_GPIO_WritePin(GPIOE, KP4_GPOUT_Pin, GPIO_PIN_SET);
		muxCount++;
		break;
	case PIN4_OFF:
		HAL_GPIO_WritePin(GPIOE, KP4_GPOUT_Pin, GPIO_PIN_RESET);
		muxCount=0;
		break;
	}
}

void readKey5()
{
	newKeypadDelay = getKeypadDebounceCounter();
	if(newKeypadDelay - lastKeypadDelay > minKeypadBounceDelay)
	{
		if(HAL_GPIO_ReadPin(GPIOE, KP1_GPOUT_Pin))
		{

			printf("Key1 Pressed = %lu\n", keypadBuffer);
			if(dm_getState() == DISPMODE)
			{
				// change the mode
				setDACMode(dm_getSelectedDac(), DAC_USER);
				dm_setState(dm_getSelectedDac(), dm_getState());
			}
			if(dm_getState() == DISPVAL)
			{
				setKeypadBuffer(concatenate(keypadBuffer, 1));
			}
		}
		if(HAL_GPIO_ReadPin(GPIOE, KP2_GPOUT_Pin))
		{
			printf("Key4 Pressed = %lu\n", keypadBuffer);
			if(dm_getState() == DISPVAL)
			{
				setKeypadBuffer(concatenate(keypadBuffer, 4));
			}
		}
		if(HAL_GPIO_ReadPin(GPIOE, KP3_GPOUT_Pin))
		{
			printf("Key7 Pressed = %lu\n", keypadBuffer);
			if(dm_getState() == DISPVAL)
			{
				setKeypadBuffer(concatenate(keypadBuffer, 7));
			}
		}
		if(HAL_GPIO_ReadPin(GPIOE, KP4_GPOUT_Pin))
		{
			printf("Key * Pressed = %lu\n", keypadBuffer);
			if(dm_getState() == DISPVAL)
			{

			}
		}

		lastKeypadDelay = newKeypadDelay;
	}

}

void readKey6()
{
	newKeypadDelay = getKeypadDebounceCounter();
	if(newKeypadDelay - lastKeypadDelay > minKeypadBounceDelay)
	{
		if(HAL_GPIO_ReadPin(GPIOE, KP1_GPOUT_Pin))
		{
			printf("Key2 Pressed = %lu\n", keypadBuffer);

			if(dm_getState() == DISPMODE)
			{
				// change the mode
				setDACMode(dm_getSelectedDac(), DAC_TRI);
				dm_setState(dm_getSelectedDac(), dm_getState());
			}
			if(dm_getState() == DISPVAL)
			{
				setKeypadBuffer(concatenate(keypadBuffer, 2));
			}
		}
		if(HAL_GPIO_ReadPin(GPIOE, KP2_GPOUT_Pin))
		{
			printf("Key5 Pressed = %lu\n", keypadBuffer);
			if(dm_getState() == DISPVAL)
			{
				setKeypadBuffer(concatenate(keypadBuffer, 5));
			}
		}
		if(HAL_GPIO_ReadPin(GPIOE, KP3_GPOUT_Pin))
		{
			printf("Key8 Pressed = %lu\n", keypadBuffer);

			if(dm_getState() == DISPVAL)
			{
				setKeypadBuffer(concatenate(keypadBuffer, 8));
			}
		}
		if(HAL_GPIO_ReadPin(GPIOE, KP4_GPOUT_Pin))
		{
			printf("Key0 Pressed = %lu\n", keypadBuffer);

			if(dm_getState() == DISPVAL)
			{
				setKeypadBuffer(concatenate(keypadBuffer, 0));
			}
		}

		lastKeypadDelay = newKeypadDelay;
	}

}

void readKey7()
{
	newKeypadDelay = getKeypadDebounceCounter();
	if(newKeypadDelay - lastKeypadDelay > minKeypadBounceDelay)
	{
		if(HAL_GPIO_ReadPin(GPIOE, KP1_GPOUT_Pin))
		{
			printf("Key3 Pressed = %lu\n", keypadBuffer);

			if(dm_getState() == DISPMODE)
			{
				// change the mode
				setDACMode(dm_getSelectedDac(), DAC_NOISE);
				dm_setState(dm_getSelectedDac(), dm_getState());
			}
			if(dm_getState() == DISPVAL)
			{
				setKeypadBuffer(concatenate(keypadBuffer, 3));
			}
		}
		if(HAL_GPIO_ReadPin(GPIOE, KP2_GPOUT_Pin))
		{
			printf("Key6 Pressed = %lu\n", keypadBuffer);

			if(dm_getState() == DISPVAL)
			{
				setKeypadBuffer(concatenate(keypadBuffer, 6));
			}
		}
		if(HAL_GPIO_ReadPin(GPIOE, KP3_GPOUT_Pin))
		{
			printf("Key9 Pressed = %lu\n", keypadBuffer);

			if(dm_getState() == DISPVAL)
			{
				setKeypadBuffer(concatenate(keypadBuffer, 9));
			}
		}
		if(HAL_GPIO_ReadPin(GPIOE, KP4_GPOUT_Pin))
		{
			// # is the "enter" key
			commitKeypadBuffer();
			setKeypadBuffer(0);
			printf("Key # Pressed\n");

			if(dm_getState() == DISPVAL)
			{

			}
		}

		lastKeypadDelay = newKeypadDelay;
	}
}

////////////////////////////////////////////////
///
///		Menu Buttons Util Functions
///
////////////////////////////////////////////////

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
