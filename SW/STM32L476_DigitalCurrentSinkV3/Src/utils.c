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

    Utils_DrawOverlay();

    // centre screen
    ssd1306_SetCursor(0, 20);
    char dac1cnt[32];

    if(getDACMode(DAC_CHANNEL_1) != 1)
    {
    	snprintf(dac1cnt, sizeof(dac1cnt), "DAC1: %2.2fHz", getDACFreq(DAC_CHANNEL_1));
    	ssd1306_WriteString(dac1cnt, Font_7x10, White, 0);
    }
    else
    {
    	snprintf(dac1cnt, sizeof(dac1cnt), "DAC1: %2.3fV", getDACVoltage(DAC_CHANNEL_1));
    	ssd1306_WriteString(dac1cnt, Font_7x10, White, 0);
    }


    ssd1306_SetCursor(0, 35);
    char dac2cnt[32];
    if(getDACMode(DAC_CHANNEL_2) != 1)
    {
    	snprintf(dac2cnt, sizeof(dac2cnt), "DAC2: %2.2fHz", getDACFreq(DAC_CHANNEL_2));
    	ssd1306_WriteString(dac2cnt, Font_7x10, White, 0);
    }
    else
    {
    	snprintf(dac2cnt, sizeof(dac2cnt), "DAC2: %2.3fV", getDACVoltage(DAC_CHANNEL_2));
    	ssd1306_WriteString(dac2cnt, Font_7x10, White, 0);
    }

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

    ssd1306_UpdateScreen();


}

void Utils_DrawOverlay()
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
	HAL_DAC_Start(&hdac1,DAC_CHANNEL_1);
	HAL_DAC_Start(&hdac1,DAC_CHANNEL_2);

	printf("Initialising Display...\n");
	Utils_i2c_scan();
	ssd1306_Init();

	// OLED display timer
	HAL_TIM_Base_Start_IT(&htim5);

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


