 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Description: header file for the ATmega16 ADC driver
 *
 * Engineer: Youssef Taha
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"



/* #define ADC_INTERRUPT */

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
/* Description :
/* Function responsible for initialize the ADC driver.
*/
void ADC_init(void);

/*
/* Description :
/* Function responsible for read analog data from a certain ADC channel
/* and convert it to digital using the ADC driver.
*/
uint16 ADC_readChannel(uint8 channel_num);

#endif /* ADC_H_ */
