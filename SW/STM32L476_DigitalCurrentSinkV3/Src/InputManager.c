/*
 * inputmanager.c
 *
 *  Created on: Aug 6, 2019
 *      Author: Chris Sutton
 *
 *      State-machine functions:
 *
 *      IM_ReadKeyCol0()		- 	state transitions for keypad btns 1,4,7,*
 *      IM_ReadKeyCol1()		- 	state transitions for keypad btns 2,5,8,0
 *      IM_ReadKeyCol2()		- 	state transitions for keypad btns 3,6,9,#
 *      IM_MenuEXTIHandler()	- 	state transitions for tactile btns 1-4
 *
 *      _Concatenate() manages keypad buffer and resolves digit/decimal positioning
 *
 *      Note, _SetKeypadBuffer() also applies the settings via call to DU_SetVoltagePreview()/DU_SetFreqPreview()
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
		if(DU_isDualChannelMode())
		{
			if(DU_GetDACModePreview(DU_getActiveDACChannel()) == DAC_USER)
			{
				DU_SetVoltagePreview(DAC_CHANNEL_1, (float)keypad_buffer);
				DU_SetVoltagePreview(DAC_CHANNEL_2, (float)keypad_buffer);
			}
			if(DU_GetDACModePreview(DU_getActiveDACChannel()) != DAC_USER)
			{
				DU_SetFreqPreview(DAC_CHANNEL_1, (float)keypad_buffer);
				DU_SetFreqPreview(DAC_CHANNEL_2, (float)keypad_buffer);
			}

		}
		else
		{
			if(DU_GetDACModePreview(DU_getActiveDACChannel()) == DAC_USER)
				DU_SetVoltagePreview(DU_getActiveDACChannel(), (float)keypad_buffer);
			if(DU_GetDACModePreview(DU_getActiveDACChannel()) != DAC_USER)
				DU_SetFreqPreview(DU_getActiveDACChannel(), (float)keypad_buffer);
		}


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
    	printf("Increment DP Count: %d\n", decimal_point_count);
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
		displayState_t mode = DM_GetState();
		// BUTTON 1
		if(HAL_GPIO_ReadPin(GPIOE, KP1_GPOUT_Pin))
		{
			switch(mode)
			{
				case PROGSEL_DISP:
					if(DU_isDualChannelMode())
					{
						DU_SetDACModePreview(DAC_CHANNEL_1, DAC_USER);
						DU_SetDACModePreview(DAC_CHANNEL_2, DAC_USER);

					}
					else
					{
						DU_SetDACModePreview(DU_getActiveDACChannel(), DAC_USER);
					}

					DM_SetBlinkTimer(1);
					DM_ChangeScreen(PARAMS_DISP);
					break;
				case PARAMS_DISP:
					_SetKeypadBuffer(_Concatenate(keypad_buffer, 1));
					break;
				case HOME_DISP:
					DU_setActiveDACChannel(DAC_CHANNEL_1);
					DU_setDualChannelMode(0);
					break;
				case CHANSEL_DISP:
				case DISPMAIN:
				case DISPMODE:
				case DISPVAL:
				default:
					break;
			}

			printf("Key1 Pressed = %2.2f\n", keypad_buffer);
		}

		// BUTTON 4
		if(HAL_GPIO_ReadPin(GPIOE, KP2_GPOUT_Pin))
		{
			switch(mode)
			{
				case PARAMS_DISP:
					_SetKeypadBuffer(_Concatenate(keypad_buffer, 4));
					break;
				case PROGSEL_DISP:
				case CHANSEL_DISP:
				case HOME_DISP:
				case DISPMAIN:
				case DISPMODE:
				case DISPVAL:
				default:
					break;
			}

			printf("Key4 Pressed = %2.2f\n", keypad_buffer);
		}

		// BUTTON 7
		if(HAL_GPIO_ReadPin(GPIOE, KP3_GPOUT_Pin))
		{
			switch(mode)
			{
				case PARAMS_DISP:
					_SetKeypadBuffer(_Concatenate(keypad_buffer, 7));
					break;
				case PROGSEL_DISP:
				case CHANSEL_DISP:
				case HOME_DISP:
				case DISPMAIN:
				case DISPMODE:
				case DISPVAL:
				default:
					break;
			}

			printf("Key7 Pressed = %2.2f\n", keypad_buffer);
		}

		// BUTTON *
		if(HAL_GPIO_ReadPin(GPIOE, KP4_GPOUT_Pin))
		{
			switch(mode)
			{
				case PARAMS_DISP:
					// enable decimal point count (incremented further by other digit presses)
					if(!decimal_point_count)
					{
						printf("Enabled DP Count\n");
						decimal_point_count=1;
					}
					break;
				case HOME_DISP:
					DU_ClearVoltagePreview(DAC_CHANNEL_1);
					DU_SetVoltage(DAC_CHANNEL_1);
					DU_ClearFreqPreview(DAC_CHANNEL_1);
					DU_SetFreq(DAC_CHANNEL_1);
					DU_SetDACModeActual(DAC_CHANNEL_1,DAC_USER);

					break;
				case PROGSEL_DISP:
				case CHANSEL_DISP:
				case DISPMAIN:
				case DISPMODE:
				case DISPVAL:
				default:
					break;
			}

			printf("Key * Pressed = %2.2f\n", keypad_buffer);
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
		displayState_t mode = DM_GetState();
		// BUTTON 2
		if(HAL_GPIO_ReadPin(GPIOE, KP1_GPOUT_Pin))
		{
			switch(mode)
			{
				case PROGSEL_DISP:
					if(DU_isDualChannelMode())
					{
						DU_SetDACModePreview(DAC_CHANNEL_1, DAC_AUTO);
						DU_SetDACModePreview(DAC_CHANNEL_2, DAC_AUTO);
					}
					else
					{
						DU_SetDACModePreview(DU_getActiveDACChannel(), DAC_AUTO);
					}

					DM_SetBlinkTimer(1);
					DM_ChangeScreen(PARAMS_DISP);
					break;
				case PARAMS_DISP:
					_SetKeypadBuffer(_Concatenate(keypad_buffer, 2));
					break;
				case HOME_DISP:
					DU_setActiveDACChannel(DAC_CHANNEL_2);
					DU_setDualChannelMode(0);
					break;
				case CHANSEL_DISP:
				case DISPMAIN:
				case DISPMODE:
				case DISPVAL:
				default:
					break;
			}

			printf("Key2 Pressed = %2.2f\n", keypad_buffer);
		}

		// BUTTON 5
		if(HAL_GPIO_ReadPin(GPIOE, KP2_GPOUT_Pin))
		{
			switch(mode)
			{
				case PARAMS_DISP:
					_SetKeypadBuffer(_Concatenate(keypad_buffer, 5));
					break;
				case PROGSEL_DISP:
				case CHANSEL_DISP:
				case HOME_DISP:
				case DISPMAIN:
				case DISPMODE:
				case DISPVAL:
				default:
					break;
			}
			printf("Key5 Pressed = %2.2f\n", keypad_buffer);
		}

		// BUTTON 8
		if(HAL_GPIO_ReadPin(GPIOE, KP3_GPOUT_Pin))
		{
			switch(mode)
			{
				case PARAMS_DISP:
					_SetKeypadBuffer(_Concatenate(keypad_buffer, 8));
					break;
				case PROGSEL_DISP:
				case CHANSEL_DISP:
				case HOME_DISP:
				case DISPMAIN:
				case DISPMODE:
				case DISPVAL:
				default:
					break;
			}
			printf("Key8 Pressed = %2.2f\n", keypad_buffer);
		}

		// BUTTON 0
		if(HAL_GPIO_ReadPin(GPIOE, KP4_GPOUT_Pin))
		{
			switch(mode)
			{
				case PARAMS_DISP:
					_SetKeypadBuffer(_Concatenate(keypad_buffer, 0));
					break;
				case PROGSEL_DISP:
				case CHANSEL_DISP:
				case HOME_DISP:
				case DISPMAIN:
				case DISPMODE:
				case DISPVAL:
				default:
					break;
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
		displayState_t mode = DM_GetState();
		// BUTTON 3
		if(HAL_GPIO_ReadPin(GPIOE, KP1_GPOUT_Pin))
		{

			switch(mode)
			{
				case PROGSEL_DISP:
					if(DU_isDualChannelMode())
					{
						DU_SetDACModePreview(DAC_CHANNEL_1, DAC_RAND);
						DU_SetDACModePreview(DAC_CHANNEL_2, DAC_RAND);
					}
					else
					{
						DU_SetDACModePreview(DU_getActiveDACChannel(), DAC_RAND);
					}

					DM_SetBlinkTimer(1);
					DM_ChangeScreen(PARAMS_DISP);
					break;
				case PARAMS_DISP:
					_SetKeypadBuffer(_Concatenate(keypad_buffer, 3));
					break;
				case HOME_DISP:
					DU_setDualChannelMode(1);
					break;
				case CHANSEL_DISP:
				case DISPMAIN:
				case DISPMODE:
				case DISPVAL:
				default:
					break;
			}
			printf("Key3 Pressed = %2.2f\n", keypad_buffer);

		}

		// BUTTON 6
		if(HAL_GPIO_ReadPin(GPIOE, KP2_GPOUT_Pin))
		{
			switch(mode)
			{
				case PARAMS_DISP:
					_SetKeypadBuffer(_Concatenate(keypad_buffer, 6));
					break;
				case PROGSEL_DISP:
				case CHANSEL_DISP:
				case HOME_DISP:
				case DISPMAIN:
				case DISPMODE:
				case DISPVAL:
				default:
					break;
			}
			printf("Key6 Pressed = %2.2f\n", keypad_buffer);
		}

		// BUTTON 9
		if(HAL_GPIO_ReadPin(GPIOE, KP3_GPOUT_Pin))
		{
			switch(mode)
			{
				case PARAMS_DISP:
					_SetKeypadBuffer(_Concatenate(keypad_buffer, 9));
					break;
				case PROGSEL_DISP:
				case CHANSEL_DISP:
				case HOME_DISP:
				case DISPMAIN:
				case DISPMODE:
				case DISPVAL:
				default:
					break;
			}
			printf("Key9 Pressed = %2.2f\n", keypad_buffer);
		}

		// BUTTON #
		if(HAL_GPIO_ReadPin(GPIOE, KP4_GPOUT_Pin))
		{
			// RESET DAC CHANNEL 2
			switch(mode)
			{
				case HOME_DISP:
					DU_ClearVoltagePreview(DAC_CHANNEL_2);
					DU_SetVoltage(DAC_CHANNEL_2);
					DU_ClearFreqPreview(DAC_CHANNEL_2);
					DU_SetFreq(DAC_CHANNEL_2);
					DU_SetDACModeActual(DAC_CHANNEL_2,DAC_USER);

					break;
				case PARAMS_DISP:
				case PROGSEL_DISP:
				case CHANSEL_DISP:
				case DISPMAIN:
				case DISPMODE:
				case DISPVAL:
				default:
					break;
			}


			printf("Key # Pressed\n");
		}

		last_keypad_delay = new_keypad_delay;
	}
}

/**
  * @brief	State-machine for OLED display and menu buttons
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

	// DEPRECATED
			case DISPMAIN:	// GO FROM MAIN SCREEN TO DAC1 MODE SET SCREEN
				DM_SetBlinkTimer(1);
				DM_SetState(DAC_CHANNEL_1, DISPMODE);
				digit_length=4;
				break;
			case DISPMODE:	// NO ACTION
				break;
			case DISPVAL:	// "SET VALUE" SCREEN; NUDGE VALUE
				DU_IncreaseDAC(DU_getActiveDACChannel());
				digit_length=4;
				break;
	//

			case HOME_DISP:
				DM_ChangeScreen(CHANSEL_DISP);
				break;

			case CHANSEL_DISP:
				DU_setActiveDACChannel(DAC_CHANNEL_1);
				DU_setDualChannelMode(0);
				DM_ChangeScreen(PROGSEL_DISP);
				break;

			case PROGSEL_DISP:
				// NOTHING
				break;

			case PARAMS_DISP:
				// TODO: APPLY PARAM SETTINGS

				// apply voltage/freq values to actual register
				if(DU_GetDACModePreview(DU_getActiveDACChannel()) == DAC_USER)
					DU_SetVoltage(DU_getActiveDACChannel());
				if(DU_GetDACModePreview(DU_getActiveDACChannel()) != DAC_USER)
					DU_SetFreq(DU_getActiveDACChannel());


				// Apply DAC Mode preview to actual DAC mode register
				if(DU_isDualChannelMode())
				{
					DU_SetDACModeActual(DAC_CHANNEL_1, DU_GetDACModePreview(DAC_CHANNEL_1));
					DU_SetDACModeActual(DAC_CHANNEL_2, DU_GetDACModePreview(DAC_CHANNEL_2));

				}
				else
				{
					DU_SetDACModeActual(DU_getActiveDACChannel(), DU_GetDACModePreview(DU_getActiveDACChannel()));
				}


				_ClearKeypadBuffer();
				decimal_point_count=0;			// reset the decimal point counter
				digit_length=1;
				DM_ChangeScreen(HOME_DISP);
				break;

			default:
				break;
		}

	}
	else if(HAL_GPIO_ReadPin(GPIOD, Btn2_EXT11_Pin) == GPIO_PIN_RESET)
	{
		// MENU BUTTON 2

	// DEPRECATED
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
				DU_DecreaseDAC(DU_getActiveDACChannel());
				digit_length=4;
				break;
	//

			case HOME_DISP:
				// RESET
				DU_ClearVoltagePreview(DAC_CHANNEL_1);
				DU_SetVoltage(DAC_CHANNEL_1);
				DU_ClearFreqPreview(DAC_CHANNEL_1);
				DU_SetFreq(DAC_CHANNEL_1);
				DU_SetDACModeActual(DAC_CHANNEL_1,DAC_USER);

				DU_ClearVoltagePreview(DAC_CHANNEL_2);
				DU_SetVoltage(DAC_CHANNEL_2);
				DU_ClearFreqPreview(DAC_CHANNEL_2);
				DU_SetFreq(DAC_CHANNEL_2);
				DU_SetDACModeActual(DAC_CHANNEL_2,DAC_USER);
				break;

			case CHANSEL_DISP:
				DU_setActiveDACChannel(DAC_CHANNEL_2);
				DU_setDualChannelMode(0);
				DM_ChangeScreen(PROGSEL_DISP);
				break;

			case PROGSEL_DISP:
				// NOTHING

				break;

			case PARAMS_DISP:
				// TODO: APPLY PARAM SETTINGS
				DM_SetBlinkTimer(0);

				// apply voltage/freq values to actual register
				if(DU_GetDACModePreview(DU_getActiveDACChannel()) == DAC_USER)
					DU_SetVoltage(DU_getActiveDACChannel());
				if(DU_GetDACModePreview(DU_getActiveDACChannel()) != DAC_USER)
					DU_SetFreq(DU_getActiveDACChannel());

				// Apply DAC Mode preview to actual DAC mode register
				if(DU_isDualChannelMode())
				{
					DU_SetDACModeActual(DAC_CHANNEL_1, DU_GetDACModePreview(DAC_CHANNEL_1));
					DU_SetDACModeActual(DAC_CHANNEL_2, DU_GetDACModePreview(DAC_CHANNEL_2));

				}
				else
				{
					DU_SetDACModeActual(DU_getActiveDACChannel(), DU_GetDACModePreview(DU_getActiveDACChannel()));
				}

				_ClearKeypadBuffer();
				decimal_point_count=0;			// reset the decimal point counter
				digit_length=1;
				DM_ChangeScreen(HOME_DISP);
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

	// DEPRECATED
			case DISPMAIN:	// GO FROM MAIN SCREEN TO DAC2 MODE SET SCREEN
				DM_SetState(DAC_CHANNEL_2, DISPMODE);
				break;
			case DISPMODE:	// NO OPTION

				break;
			case DISPVAL:	// APPLY VALUE SET PREVIEW

				DM_SetBlinkTimer(0);
				if(DU_GetDACModeActual(DU_getActiveDACChannel()) == DAC_USER)
					DU_SetVoltage(DU_getActiveDACChannel());
				if(DU_GetDACModeActual(DU_getActiveDACChannel()) != DAC_USER)
					DU_SetFreq(DU_getActiveDACChannel());

				_ClearKeypadBuffer();
				decimal_point_count=0;			// reset the decimal point counter
				digit_length=1;
				break;

	//

			case HOME_DISP:
				// TODO: NUDGE (INCREASE) VOLTAGE/FREQ
				if(DU_isDualChannelMode())
				{
					DU_IncreaseDAC(DAC_CHANNEL_1);
					DU_IncreaseDAC(DAC_CHANNEL_2);
				}
				else
				{
					DU_IncreaseDAC(DU_getActiveDACChannel());
				}

				break;

			case CHANSEL_DISP:
				// TODO SET DUAL CHANNEL MODE
				DU_setDualChannelMode(1);
				DM_ChangeScreen(PROGSEL_DISP);
				break;

			case PROGSEL_DISP:
				// GO BACK TO PREVIOUS
				DM_ChangeScreen(CHANSEL_DISP);
				break;

			case PARAMS_DISP:
				// CANCEL ALL PREVIEW SETTINGS
				_ClearKeypadBuffer();
				decimal_point_count=0;
				digit_length=1;
				DU_ClearVoltagePreview(DAC_CHANNEL_1);
				DU_ClearVoltagePreview(DAC_CHANNEL_2);
				DU_ClearFreqPreview(DAC_CHANNEL_1);
				DU_ClearFreqPreview(DAC_CHANNEL_2);
				DM_ChangeScreen(PROGSEL_DISP);
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

	//DEPRECATED
			case DISPMAIN:	// GO FROM MAIN SCREEN TO DAC1 VALUE SET SCREEN
				DM_SetBlinkTimer(1);
				DM_SetState(DAC_CHANNEL_2, DISPVAL);
				digit_length=4;
				break;
			case DISPMODE:	// EXIT "MODE SET" SCREEN

				DM_SetState(DAC_CHANNEL_2, DISPMAIN);

				printf("DAC1 Mode: %s\n", DU_GetDACModeActual2String(DAC_CHANNEL_1));
				printf("DAC2 Mode: %s\n", DU_GetDACModeActual2String(DAC_CHANNEL_2));

				break;
			case DISPVAL:	// EXIT "VALUE SET" SCREEN (CLEAR VALUE PREVIEW)
/*
				if(DU_GetDACModeActual(DM_GetSelectedDac()) == DAC_USER)
					clearVoltagePreview();
				if(DU_GetDACModeActual(DM_GetSelectedDac()) != DAC_USER)
					reDU_DU_SetFreqPreview();
*/
				_ClearKeypadBuffer();
				decimal_point_count=0;					// reset the decimal point counter
				digit_length=1;
				DM_SetState(DAC_CHANNEL_2, DISPMAIN);

				break;

	//

			case HOME_DISP:

				if(DU_isDualChannelMode())
				{
					DU_DecreaseDAC(DAC_CHANNEL_1);
					DU_DecreaseDAC(DAC_CHANNEL_2);
				}
				else
				{
					DU_DecreaseDAC(DU_getActiveDACChannel());
				}

				break;

			case CHANSEL_DISP:
				// TODO:  CANCEL ALL PREVIEW SETTINGS
				DM_ChangeScreen(HOME_DISP);
				break;

			case PROGSEL_DISP:
				// TODO:  CANCEL ALL PREVIEW SETTINGS
				DM_ChangeScreen(HOME_DISP);
				break;

			case PARAMS_DISP:
				// CANCEL ALL PREVIEW SETTINGS
				_ClearKeypadBuffer();
				DU_ClearVoltagePreview(DAC_CHANNEL_1);
				DU_ClearVoltagePreview(DAC_CHANNEL_2);
				DU_ClearFreqPreview(DAC_CHANNEL_1);
				DU_ClearFreqPreview(DAC_CHANNEL_2);
				DM_ChangeScreen(HOME_DISP);
				break;
			default:
				break;

		}
	}
}
