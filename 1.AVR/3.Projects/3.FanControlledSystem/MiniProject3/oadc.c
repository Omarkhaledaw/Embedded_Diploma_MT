#include "avr/io.h" /* To use the ADC Registers */
#include <avr/interrupt.h> /* For ADC ISR */
#include "oadc.h"  /*including the ADC header file*/
#include "ocommon_macros.h" /* To use the macros */

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define ADC_AREF 5;

/*******************************************************************************
 *                          Global Variables                                   *
 *******************************************************************************/

float ADC_REF_VOLT_VALUE ;

/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_initial(const ADC_ConfigType * Config_Ptr){
	/*Configuring the pointer to structure*/
	if(Config_Ptr->ref_volt == AREF_vref){
		ADC_REF_VOLT_VALUE = ADC_AREF;
	}else if(Config_Ptr->ref_volt == AVCC_vref){
		ADC_REF_VOLT_VALUE = 5;
	}else if(Config_Ptr->ref_volt == INERNAL_vref){
		ADC_REF_VOLT_VALUE = 2.56;
	}

	ADMUX = ((ADMUX & 0x3f) | ((Config_Ptr->ref_volt)& 0x03)<<6);
	/* 0x3f is 11110011 to clear ADMUX
	 * 0x03 is 0011 to clear ref_volt
	 *
	 * ADMUX Register Bits Description:
	 * REFS1 & REFS0: V-Reference selection (bits6,7)
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 */

	ADCSRA = (1<<ADEN);
	ADCSRA = ADCSRA | ((ADCSRA & 0xF8)|((Config_Ptr->prescaler)& 0x07));
	/* 0x07 is 01111
	 * 0xF8 11111000
	 *
	 * ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 0 Disable ADC Interrupt
	 * ADATE   = 0 Disable Auto Trigger
	 * ADPS2:0 = to choose ADC_Clock ADC must operate in range 50-200Khz
	 *
	 * */
}
/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.

  ATmega16/32 supports 8 ADC channels on PORTA we can only convert to one digital value at a time
 */
uint16 ADC_read(uint8 channel_number){
	/*Clearing channel number and ADMUX before setting it up*/
	ADMUX = (channel_number & 0x07) | (ADMUX & 0xE0);
	SET(ADCSRA,ADSC);/* Start conversion write '1' to ADSC */
	while(CHECK_CLEAR(ADCSRA,ADIF));/* Wait for conversion to complete, ADIF becomes '1' */
	SET(ADCSRA,ADIF);/* Clear ADIF by write '1' to it :) */
	return ADC; /*Return the digital value to ADC register*/
}
