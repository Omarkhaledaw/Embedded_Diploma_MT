/*
 * olm35.h
 *
 *  Created on: Oct 9, 2022
 *      Author: Dell
 */

#ifndef OLM35_H_
#define OLM35_H_

#include "std_define_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define SENSOR_CHANNEL			2
#define SENSOR_MAX_VOLT			1.5
#define SENSOR_MAX_TEMPERATURE	150

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for calculate the temperature from the ADC digital value.
 */
uint8 LM35_getTemp();

#endif /* OLM35_H_ */
