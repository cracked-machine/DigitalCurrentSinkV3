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

/* ADC Resolution */
#define ADCRES				4095

/* increment amounts for nudging voltage/frequency values */
#define MAXFREQSTEP 		32
#define MAXAMPSTEP 			1

// adjust to match power resistor value, allows for variation according to tolerances
#define CH0_PWR_RESISTOR	0.13 // positive N-channel
#define CH1_PWR_RESISTOR	0.115 // negative P-channel

/* instrumentation amp gain compensation.
 * This can be done in HW using gain resistor or "fixed" here in SW
 * Absolute minimum value is 1 */
#define CH0_INAMP_GAIN_COMP		7.7
#define CH1_INAMP_GAIN_COMP		7.5

/* prescaler for RAND and AUTO modes. RAND PSC should be much larger than AUTO PSC */
#define TIM_PSC_RANDMODE	16383
#define TIM_PSC_AUTOMODE	1023

// not used
#define MAX_WATTAGE			36

// not used
void SYS_Init();

#endif /* SYSTEMCONSTANTS_H_ */
