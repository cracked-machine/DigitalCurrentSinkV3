/*
 * utils.c
 *
 *  Created on: 20 Mar 2019
 *      Author: chris
 */


#include "utils.h"
#include "tim.h"
#include "stm32l4xx_hal.h"
#include "dac.h"
#include "ssd1306_tests.h"
#include "adc.h"

uint32_t test[2] = {};

////////////////////////////////////////////////////////
///
///	Name: _write
///
/// Description: Redirect stdout to ITM/SWO
///
////////////////////////////////////////////////////////

void Utils_Init()
{


	// start DAC and associated timers
	HAL_TIM_Base_Start_IT(&htim6);
	HAL_TIM_Base_Start_IT(&htim7);

	DAC_ChannelConfTypeDef sConfig = {0};
	HAL_DACEx_SelfCalibrate(&hdac1, &sConfig, DAC_CHANNEL_1);
	HAL_DACEx_SelfCalibrate(&hdac1, &sConfig, DAC_CHANNEL_2);
	HAL_DAC_Start(&hdac1,DAC_CHANNEL_1);
	HAL_DAC_Start(&hdac1,DAC_CHANNEL_2);

	DU_SetVoltagePreview(DAC_CHANNEL_1, 0.0f);
	DU_SetVoltage(DAC_CHANNEL_1);
	DU_SetVoltagePreview(DAC_CHANNEL_2, 0.0f);
	DU_SetVoltage(DAC_CHANNEL_2);

	printf("Initialising Display...\n");
	Utils_i2c_scan();
	ssd1306_Init();

	// OLED display timer
	HAL_TIM_Base_Start_IT(&htim5);

	// display blink counter
	HAL_TIM_Base_Start_IT(&htim16);

	// debounce counter
	HAL_TIM_Base_Start_IT(&htim17);

	HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
	HAL_ADC_Start_DMA(&hadc1, test, 2);
}




////////////////////////////////////////////////
///
///		Utils_i2c_scan
///
////////////////////////////////////////////////


void Utils_i2c_scan() {
    printf("Scanning I2C bus...\n");
    char msg[64];
    int DeviceFound=0;
    char notFound[160];
    HAL_StatusTypeDef res;
    for(uint16_t i = 0; i < 128; i++) {
        res = HAL_I2C_IsDeviceReady(&hi2c1, i << 1, 1, 10);
        if(res == HAL_OK) {

            snprintf(msg, sizeof(msg), "0x%02X", i);
            printf("Found %s\n", msg);
            DeviceFound=1;

        }
        if(res == HAL_ERROR)
        {
        	snprintf(notFound + strlen(notFound), sizeof("."), "%s", ".");

        }
    }
    if(!DeviceFound)
    {
    	printf("%s\n", notFound);
    	printf("No device found\n");
    }
}

////////////////////////////////////////////////////////
///
///	Name: _write
///
/// Description: Redirect stdout to ITM/SWO
///
////////////////////////////////////////////////////////

int _write(int file, char *ptr, int len)
{
	for (int i=0; i<len; i++)
	{
		ITM_SendChar((*ptr++));
	}
	return len;
}


