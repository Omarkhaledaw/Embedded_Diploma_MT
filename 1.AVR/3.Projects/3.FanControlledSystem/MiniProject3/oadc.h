/*
 * oadc.h
 *
 *  Created on: Oct 6, 2022
 *      Author: Dell
 */

#ifndef OADC_H_
#define OADC_H_

#include "std_define_types.h"
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
#define ADC_MAXIMUM    1023
#define ADC_REF_VOLT   5

/*******************************************************************************
 *                               Typedef                                       *
 *******************************************************************************/
typedef enum{
	AREF_vref,AVCC_vref,RESRVED_vref,INERNAL_vref
}ADC_ReferenceVolatge;
/*AREF_vref = 0 	(00)
 * AVCC_vref = 1	(01)
 * RESRVED_vref = 2 (10)
 * INERNAL_vref = 3 (11)
 * same as their value in table.83
 * */
typedef enum{
	F_CPU_CLOCK_2=1,F_CPU_CLOCK_4,F_CPU_CLOCK_8,F_CPU_CLOCK_16,F_CPU_CLOCK_32,F_CPU_CLOCK_64,F_CPU_CLOCK_128
}ADC_Prescaler;
/*F_CPU_CLOCK_2 = 1 	(00)
 * F_CPU_CLOCK_4 = 2 	(001)
 * F_CPU_CLOCK_8 = 3 	(010)
 * F_CPU_CLOCK_16 =4 	(011)
 * F_CPU_CLOCK_32 = 5 	(101)
 * F_CPU_CLOCK_64 = 6 	(110)
 * F_CPU_CLOCK_128 = 7 	(111)
 * same as their value in table.85
 * */
typedef struct{
	ADC_ReferenceVolatge ref_volt;
	ADC_Prescaler prescaler;
}ADC_ConfigType;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_initial(const ADC_ConfigType * Config_Ptr);
/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
uint16 ADC_read(uint8 channel_number);

#endif /* OADC_H_ */
