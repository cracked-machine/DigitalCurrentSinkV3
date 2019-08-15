/*
 * utils.h
 *
 *  Created on: 20 Mar 2019
 *      Author: chris
 */





#ifndef UTILS_H_
#define UTILS_H_

#include "stm32l4xx_hal.h"
#include "ssd1306.h"
#include <string.h>
#include <stdarg.h>
#include <DacUtilities.h>

uint32_t test[2];

void Utils_Init();
int _write(int file, char *ptr, int len);
void Utils_i2c_scan();


#endif /* UTILS_H_ */
