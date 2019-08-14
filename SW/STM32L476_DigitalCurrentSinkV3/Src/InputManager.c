/*
 * inputmanager.c
 *
 *  Created on: Aug 6, 2019
 *      Author: chris
 */

// HAL dependencies
#include <DacUtilities.h>
#include <DisplayManager.h>
#include <InputManager.h>
#include "stm32l4xx_hal.h"

// project dependencies
#include "ssd1306.h"

// C LIB
#include <string.h>
#include <stdarg.h>
#include <math.h>

/* Sequence of rows to enable/disable for MUX.
 * Used by IM_MuxKeysRows() */
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

};

/* counter used by TIM17 (TIM1_TRG_COM_TIM17_IRQHandler) to traverse the keypad rows */
int keypad_row_mux_count=0;

/* counter to track when user presses "decimal point" keypad button
 * along with any subsequent digits pressed thereafter.  */
uint8_t decimal_point_count = 0;

/* size of number to be drawn. Used by DisplayManager   */
uint8_t digit_length = 1;

/* Keypad debounce variables. Increase min_keypad_bounce_delay to decrease bouncing */
uint32_t keypad_debounce_counter = 0;
uint32_t last_keypad_delay = 0;
uint32_t min_keypad_bounce_delay = 250;

/* Buffers last four digits pressed by user. See _Concatenate() */
float keypad_buffer = 0;

/* Buffer limit. See _Concatenate() */
uint32_t keypadBufferMax = 5001;


/**
  * @brief Get digit_length variable
  *
  *
  * @param
  * 		@arg @ref
  * @param
  * 		@arg @ref
  *
  *
  * @retval digit_length
  */

uint8_t IM_GetDigitLength()
{
	return digit_length;
}

/**
  * @brief Set keypad_debounce_counter variable
  *
  *
  * @param
  * 		@arg @ref
  * @param
  * 		@arg @ref
  *
  *
  * @retval
  */

void IM_SetKeypadDebounceCounter(uint16_t pValue)
{
	keypad_debounce_counter += pValue;
}

/**
  * @brief get keypad_debounce_counter
  *
  *
  * @param
  * 		@arg @ref
  * @param
  * 		@arg @ref
  *
  *
  * @retval keypad_debounce_counter
  */

uint32_t _GetKeypadDebounceCounter()
{
	return keypad_debounce_counter;
}

/**
  * @brief Update the buffer and set the voltage/frequency preview variable
  *
  *
  * @param value The new value to update
  *
  * @retval none
  */

void _SetKeypadBuffer(double pValue)
{

		keypad_buffer = pValue;
		if(DU_GetDACMode(DM_GetSelectedDac()) == DAC_USER)
			DU_SetVoltagePreview(DM_GetSelectedDac(), (float)keypad_buffer);
		if(DU_GetDACMode(DM_GetSelectedDac()) != DAC_USER)
			DU_SetFreqPreview(DM_GetSelectedDac(), (float)keypad_buffer);

}

/**
  * @brief Zero the keypad_buffer
  *
  *
  * @retval none
  */

void _ClearKeypadBuffer()
{
	keypad_buffer = 0;
}

/**
  * @brief	Process integer or fractional positioning for appending new digit to keypad_buffer.
  * 		Integer parts: 		_buffer * exp + _newDigit
  *			Fractional parts:	_buffer + ( _newDigit / ( pow( exp,decimal_point_count ) )
  *
  * @param	_buffer The existing keypad buffer contents
  * @param	_newDigit The new digit to add to the keypad buffer
  *
  * @retval The new keypad buffer value
  */

double _Concatenate(double _buffer, double _newDigit) {
	double next_calculated_value = 0;
    double exp = 10;
    if(decimal_point_count > 0)
    {
    	_newDigit = _newDigit / (pow(exp,decimal_point_count));
    	decimal_point_count++;
    	next_calculated_value = (_buffer + _newDigit);
    	digit_length++;
    }
    else
    {
    	next_calculated_value = (_buffer * exp + _newDigit);
    }

    if(next_calculated_value >= keypadBufferMax)
    {
    	_SetKeypadBuffer(_buffer);						// set display using previous entered value
    	return 0;
    }

    return next_calculated_value;
}

/**
  * @brief	Set current row (keypad_row_mux_count) to logic high or low
  *			keypad_row_mux_count is incremented by Timer17
  *
  * @retval none
  */

void IM_MuxKeysRows()
{
	switch(keypad_row_mux_count)
	{
	case PIN1_ON:
		HAL_GPIO_WritePin(GPIOE, KP1_GPOUT_Pin, GPIO_PIN_SET);
		keypad_row_mux_count++;
		break;
	case PIN1_OFF:
		HAL_GPIO_WritePin(GPIOE, KP1_GPOUT_Pin, GPIO_PIN_RESET);
		keypad_row_mux_count++;
		break;
	case PIN2_ON:
		HAL_GPIO_WritePin(GPIOE, KP2_GPOUT_Pin, GPIO_PIN_SET);
		keypad_row_mux_count++;
		break;
	case PIN2_OFF:
		HAL_GPIO_WritePin(GPIOE, KP2_GPOUT_Pin, GPIO_PIN_RESET);
		keypad_row_mux_count++;
		break;
	case PIN3_ON:
		HAL_GPIO_WritePin(GPIOE, KP3_GPOUT_Pin, GPIO_PIN_SET);
		keypad_row_mux_count++;
		break;
	case PIN3_OFF:
		HAL_GPIO_WritePin(GPIOE, KP3_GPOUT_Pin, GPIO_PIN_RESET);
		keypad_row_mux_count++;
		break;
	case PIN4_ON:
		HAL_GPIO_WritePin(GPIOE, KP4_GPOUT_Pin, GPIO_PIN_SET);
		keypad_row_mux_count++;
		break;
	case PIN4_OFF:
		HAL_GPIO_WritePin(GPIOE, KP4_GPOUT_Pin, GPIO_PIN_RESET);
		keypad_row_mux_count=0;
		break;
	}
}

/**
  * @brief	Check if any buttons on this column read logic high
  *
  * @retval	none
  */

void IM_ReadKeyCol0()
{
	uint32_t new_keypad_delay = _GetKeypadDebounceCounter();
	if(new_keypad_delay - last_keypad_delay > min_keypad_bounce_delay)
	{
		// BUTTON 1
		if(HAL_GPIO_ReadPin(GPIOE, KP1_GPOUT_Pin))
		{

			if(DM_GetState() == DISPMODE)
			{

				DU_SetDACMode(DM_GetSelectedDac(), DAC_USER);
				DM_SetState(DM_GetSelectedDac(), DM_GetState());
			}
			if(DM_GetState() == DISPVAL)
			{
				DM_SetBlinkTimer(1);
				if(decimal_point_count > 0)
				{
					printf("Increment DP Count: %d\n", decimal_point_count);

				}
				_SetKeypadBuffer(_Concatenate(keypad_buffer, 1));
			}
			printf("Key1 Pressed = %2.2f\n", keypad_buffer);
		}

		// BUTTON 4
		if(HAL_GPIO_ReadPin(GPIOE, KP2_GPOUT_Pin))
		{

			if(DM_GetState() == DISPVAL)
			{
				DM_SetBlinkTimer(1);
				if(decimal_point_count > 0)
				{
					printf("Increment DP Count: %d\n", decimal_point_count);

				}
				_SetKeypadBuffer(_Concatenate(keypad_buffer, 4));
			}
			printf("Key4 Pressed = %2.2f\n", keypad_buffer);
		}

		// BUTTON 7
		if(HAL_GPIO_ReadPin(GPIOE, KP3_GPOUT_Pin))
		{

			if(DM_GetState() == DISPVAL)
			{
				DM_SetBlinkTimer(1);
				if(decimal_point_count > 0)
				{
					printf("Increment DP Count: %d\n", decimal_point_count);

				}
				_SetKeypadBuffer(_Concatenate(keypad_buffer, 7));
			}
			printf("Key7 Pressed = %2.2f\n", keypad_buffer);
		}

		// BUTTON *
		if(HAL_GPIO_ReadPin(GPIOE, KP4_GPOUT_Pin))
		{

			if(DM_GetState() == DISPVAL)
			{
				DM_SetBlinkTimer(1);
			}
			printf("Key * Pressed = %2.2f\n", keypad_buffer);

			// enable decimal point count (incremented further by other digit presses)
			if(!decimal_point_count)
			{
				printf("Enabled DP Count\n");
				decimal_point_count=1;
			}
/*			else
			{
				printf("Disabled DP Count");
				decimal_point_count=0;		// disable decimal point count if pressed again
			}
*/
		}

		last_keypad_delay = new_keypad_delay;
	}

}

/**
  * @brief	Check if any buttons on this column read logic high
  *
  * @retval	none
  */

void IM_ReadKeyCol1()
{
	uint32_t new_keypad_delay = _GetKeypadDebounceCounter();
	if(new_keypad_delay - last_keypad_delay > min_keypad_bounce_delay)
	{
		// BUTTON 2
		if(HAL_GPIO_ReadPin(GPIOE, KP1_GPOUT_Pin))
		{
			if(DM_GetState() == DISPMODE)
			{
				// change the mode
				DU_SetDACMode(DM_GetSelectedDac(), DAC_TRI);
				DM_SetState(DM_GetSelectedDac(), DM_GetState());
			}
			if(DM_GetState() == DISPVAL)
			{
				DM_SetBlinkTimer(1);
				if(decimal_point_count > 0)
				{
					printf("Increment DP Count: %d\n", decimal_point_count);

				}
				_SetKeypadBuffer(_Concatenate(keypad_buffer, 2));
			}
			printf("Key2 Pressed = %2.2f\n", keypad_buffer);

		}

		// BUTTON 5
		if(HAL_GPIO_ReadPin(GPIOE, KP2_GPOUT_Pin))
		{
			if(DM_GetState() == DISPVAL)
			{
				DM_SetBlinkTimer(1);
				if(decimal_point_count > 0)
				{
					printf("Increment DP Count: %d\n", decimal_point_count);

				}
				_SetKeypadBuffer(_Concatenate(keypad_buffer, 5));
			}
			printf("Key5 Pressed = %2.2f\n", keypad_buffer);
		}

		// BUTTON 8
		if(HAL_GPIO_ReadPin(GPIOE, KP3_GPOUT_Pin))
		{
			if(DM_GetState() == DISPVAL)
			{
				DM_SetBlinkTimer(1);
				if(decimal_point_count > 0)
				{
					printf("Increment DP Count: %d\n", decimal_point_count);

				}
				_SetKeypadBuffer(_Concatenate(keypad_buffer, 8));
			}
			printf("Key8 Pressed = %2.2f\n", keypad_buffer);
		}

		// BUTTON 0
		if(HAL_GPIO_ReadPin(GPIOE, KP4_GPOUT_Pin))
		{

			if(DM_GetState() == DISPVAL)
			{
				DM_SetBlinkTimer(1);
				if(decimal_point_count > 0)
				{
					printf("Increment DP Count: %d\n", decimal_point_count);

				}
				_SetKeypadBuffer(_Concatenate(keypad_buffer, 0));
			}
			printf("Key0 Pressed = %2.2f\n", keypad_buffer);
		}

		last_keypad_delay = new_keypad_delay;
	}

}

/**
  * @brief	Check if any buttons on this column read logic high
  *
  * @retval	none
  */

void IM_ReadKeyCol2()
{
	uint32_t new_keypad_delay = _GetKeypadDebounceCounter();
	if(new_keypad_delay - last_keypad_delay > min_keypad_bounce_delay)
	{
		// BUTTON 3
		if(HAL_GPIO_ReadPin(GPIOE, KP1_GPOUT_Pin))
		{
			if(DM_GetState() == DISPMODE)
			{
				// change the mode
				DU_SetDACMode(DM_GetSelectedDac(), DAC_NOISE);
				DM_SetState(DM_GetSelectedDac(), DM_GetState());
			}
			if(DM_GetState() == DISPVAL)
			{
				DM_SetBlinkTimer(1);
				if(decimal_point_count > 0)
				{
					printf("Increment DP Count: %d\n", decimal_point_count);

				}
				_SetKeypadBuffer(_Concatenate(keypad_buffer, 3));
			}
			printf("Key3 Pressed = %2.2f\n", keypad_buffer);

		}

		// BUTTON 6
		if(HAL_GPIO_ReadPin(GPIOE, KP2_GPOUT_Pin))
		{
			if(DM_GetState() == DISPVAL)
			{
				DM_SetBlinkTimer(1);
				_SetKeypadBuffer(_Concatenate(keypad_buffer, 6));
			}
			printf("Key6 Pressed = %2.2f\n", keypad_buffer);
		}

		// BUTTON 9
		if(HAL_GPIO_ReadPin(GPIOE, KP3_GPOUT_Pin))
		{

			if(DM_GetState() == DISPVAL)
			{
				DM_SetBlinkTimer(1);
				if(decimal_point_count > 0)
				{
					printf("Increment DP Count: %d\n", decimal_point_count);

				}
				_SetKeypadBuffer(_Concatenate(keypad_buffer, 9));
			}
			printf("Key9 Pressed = %2.2f\n", keypad_buffer);
		}

		// BUTTON #
		if(HAL_GPIO_ReadPin(GPIOE, KP4_GPOUT_Pin))
		{
			// # is the "enter" key
			//commitKeypadBuffer();
			_SetKeypadBuffer(0);


			if(DM_GetState() == DISPVAL)
			{
				DM_SetBlinkTimer(1);
			}

			printf("Key # Pressed\n");
		}

		last_keypad_delay = new_keypad_delay;
	}
}

/**
  * @brief	State-machine for menu buttons
  * 		Each button has different action depending on the current state
  *
  * @retval none
  */

void IM_MenuEXTIHandler()
{

	if(HAL_GPIO_ReadPin(GPIOD, Btn1_EXT10_Pin) == GPIO_PIN_RESET)
	{
		// MENU BUTTON 1

		displayState_t theDisplayState = DM_GetState();
		switch(theDisplayState)
		{
			case DISPMAIN:	// GO FROM MAIN SCREEN TO DAC1 MODE SET SCREEN
				DM_SetBlinkTimer(1);
				DM_SetState(DAC_CHANNEL_1, DISPMODE);
				digit_length=4;
				break;
			case DISPMODE:	// NO ACTION
				break;
			case DISPVAL:	// "SET VALUE" SCREEN; NUDGE VALUE
				DU_IncreaseDAC(DM_GetSelectedDac());
				digit_length=4;
				break;
			default:
				break;
		}

	}
	else if(HAL_GPIO_ReadPin(GPIOD, Btn2_EXT11_Pin) == GPIO_PIN_RESET)
	{
		// MENU BUTTON 2

		displayState_t theDisplayState = DM_GetState();
		switch(theDisplayState)
		{
			case DISPMAIN:			// GO FROM MAIN SCREEN TO DAC1 VALUE SET SCREEN
				DM_SetBlinkTimer(1);
				DM_SetState(DAC_CHANNEL_1, DISPVAL);
				digit_length=4;
				break;
			case DISPMODE:			// NO ACTION
				break;
			case DISPVAL:			// "SET VALUE" SCREEN; NUDGE VALUE
				DU_DecreaseDAC(DM_GetSelectedDac());
				digit_length=4;
				break;
			default:
				break;
		}
	}
	else if(HAL_GPIO_ReadPin(GPIOD, Btn3_EXT12_Pin) == GPIO_PIN_RESET)
	{
		// MENU BUTTON 3

		displayState_t theDisplayState = DM_GetState();
		switch(theDisplayState)
		{
			case DISPMAIN:	// GO FROM MAIN SCREEN TO DAC2 MODE SET SCREEN
				DM_SetState(DAC_CHANNEL_2, DISPMODE);
				break;
			case DISPMODE:	// NO OPTION

				break;
			case DISPVAL:	// APPLY VALUE SET PREVIEW

				DM_SetBlinkTimer(0);
				if(DU_GetDACMode(DM_GetSelectedDac()) == DAC_USER)
					DU_SetVoltage(DM_GetSelectedDac());
				if(DU_GetDACMode(DM_GetSelectedDac()) != DAC_USER)
					DU_SetFreq(DM_GetSelectedDac());

				_ClearKeypadBuffer();
				decimal_point_count=0;			// reset the decimal point counter
				//digit_length=1;
				break;
			default:
				break;
		}

	}
	else if(HAL_GPIO_ReadPin(GPIOD, Btn4_EXT13_Pin) == GPIO_PIN_RESET)
	{
		// MENU BUTTON 4

		displayState_t theDisplayState = DM_GetState();
		switch(theDisplayState)
		{
			case DISPMAIN:	// GO FROM MAIN SCREEN TO DAC1 VALUE SET SCREEN
				DM_SetBlinkTimer(1);
				DM_SetState(DAC_CHANNEL_2, DISPVAL);
				digit_length=4;
				break;
			case DISPMODE:	// EXIT "MODE SET" SCREEN

				DM_SetState(DAC_CHANNEL_2, DISPMAIN);

				printf("DAC1 Mode: %s\n", DU_GetDACMode2String(DAC_CHANNEL_1));
				printf("DAC2 Mode: %s\n", DU_GetDACMode2String(DAC_CHANNEL_2));

				break;
			case DISPVAL:	// EXIT "VALUE SET" SCREEN (CLEAR VALUE PREVIEW)
/*
				if(DU_GetDACMode(DM_GetSelectedDac()) == DAC_USER)
					clearVoltagePreview();
				if(DU_GetDACMode(DM_GetSelectedDac()) != DAC_USER)
					reDU_DU_SetFreqPreview();
*/
				_ClearKeypadBuffer();
				decimal_point_count=0;					// reset the decimal point counter
				digit_length=4;
				DM_SetState(DAC_CHANNEL_2, DISPMAIN);

				break;
			default:
				break;
		}
	}
}
