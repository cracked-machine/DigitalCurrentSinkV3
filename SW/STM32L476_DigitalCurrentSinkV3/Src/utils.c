/*
 * utils.c
 *
 *  Created on: 20 Mar 2019
 *      Author: chris
 */


#include "utils.h"
#include "tim.h"



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

////////////////////////////////////////////////
///
///		i2c_scan
///
////////////////////////////////////////////////


void i2c_scan() {
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

