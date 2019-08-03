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


void Utils_UpdateDisplay()
{

    ssd1306_Fill(Black);

    ssd1306_SetCursor(0, 0);
    char dac1cnt[16];
    snprintf(dac1cnt, sizeof(dac1cnt), "DAC1 (TIM6): %lu", htim6.Instance->CNT);
    ssd1306_WriteString(dac1cnt, Font_7x10, White, 0);

    ssd1306_SetCursor(0, 15);
    char dac2cnt[16];
	snprintf(dac2cnt, sizeof(dac2cnt), "DAC2 (TIM7): %lu", htim7.Instance->CNT);
	ssd1306_WriteString(dac2cnt, Font_7x10, White, 0);

    ssd1306_UpdateScreen();


}

////////////////////////////////////////////////////////
///
///	Name: _write
///
/// Description: Redirect stdout to ITM/SWO
///
////////////////////////////////////////////////////////

void Utils_Init()
{
	Utils_i2c_scan();
	printf("Initialising Display...\n");
	ssd1306_Init();
	//ssd1306_TestAll();
	printf("Initialising Timers/DACs...\n");
	HAL_TIM_Base_Start_IT(&htim5);
	HAL_TIM_Base_Start_IT(&htim6);
	HAL_TIM_Base_Start_IT(&htim7);


	HAL_DAC_Start(&hdac1,DAC_CHANNEL_1);
	HAL_DAC_Start(&hdac1,DAC_CHANNEL_2);


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

