/*
 * opwm.c
 *
 *  Created on: Oct 9, 2022
 *      Author: Dell
 */
#include "opwm.h"
#include "ogpio.h"
#include "avr/io.h" /* To use the ADC Registers */
#include "ocommon_macros.h" /* To use the macros */
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description:
 * The function responsible for trigger the Timer0 with the PWM Mode
 * The generated PWM signal frequency will be 500Hz to control the DC Motor speed.
 */
void PWM_Timer0_Start(uint8 duty_cycle){

	TCNT0 = 0; //Set Timer Initial value

	OCR0  = duty_cycle; // Set Compare Value

	GPIO_setupPin(PORTB_ID,PIN3,PIN_OUTPUT); //set PB3/OC0 as output pin --> pin where the PWM signal is generated from MC.

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
}
