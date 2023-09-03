/*
 * olm35.c
 *
 *  Created on: Oct 9, 2022
 *      Author: Dell
 */
#include <util/delay.h> /* For the delay functions */
#include "olm35.h"
#include "oadc.h"

uint8 LM35_getTemp(){
	uint8 temp = 0;
	uint8 adc = 0;

	/* Read ADC channel where the temperature sensor is connected */
	adc = ADC_read(SENSOR_CHANNEL);

	/* Make delay for some time until g_adcResult value is updated with the ADC interrupt */
	_delay_ms(10);
	/* Calculate the temperature from the ADC value*/
	temp = (uint8)(((uint32)adc*SENSOR_MAX_TEMPERATURE*ADC_REF_VOLT)/(ADC_MAXIMUM*SENSOR_MAX_VOLT));

	return temp;
}

