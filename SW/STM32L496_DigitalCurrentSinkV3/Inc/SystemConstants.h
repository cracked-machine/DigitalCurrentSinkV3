/*
 * SystemConstants.h
 *
 *  Created on: Aug 25, 2019
 *      Author: chris
 */

#ifndef SYSTEMCONSTANTS_H_
#define SYSTEMCONSTANTS_H_

/* Max resolution for 16-bit timer */
#define TIMRES 				65535

/* MCU clock speed in hertz */
#define MASTERCLK 			80000000

/* DAC VREF */
#define VREF 				3.3

/* DAC resolution */
#define DACRES 				4096

/* increment amounts for nudging voltage/frequency values */
#define MAXFREQSTEP 		32
#define MAXAMPSTEP 			1

/* ADC Resolution */
#define ADCRES				4095

#define CH0_PWR_RESISTOR	0.15
#define CH1_PWR_RESISTOR	0.15

/* gain compensation. must not be zero! */
#define INAMP_GAIN_COMP		8.5

void SYS_Init();

#endif /* SYSTEMCONSTANTS_H_ */
