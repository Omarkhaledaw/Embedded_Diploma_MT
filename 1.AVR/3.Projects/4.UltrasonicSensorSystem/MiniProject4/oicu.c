#include "oicu.h"
#include "ogpio.h"
#include "ocommon_macros.h" /* To use the macros */
#include <avr/io.h> /* To use ICU/Timer1 Registers */
#include <avr/interrupt.h> /* For ICU ISR */

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)() = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/
ISR(TIMER1_CAPT_vect){

	if(g_callBackPtr != NULL_PTR){
		(*g_callBackPtr)();
	}
}
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description : Function to initialize the ICU driver
 * 	1. Set the required clock.
 * 	2. Set the required edge detection.
 * 	3. Enable the Input Capture Interrupt.
 * 	4. Initialize Timer1 Registers
 */
void ICU_initial(const ICU_Config * Config_Ptr){
	GPIO_setupPin(ICU_PORT,ICU_PIN,PIN_INPUT);
	/* Timer1 always operates in Normal Mode */
	TCCR1A = (1<<FOC1A)|(1<<FOC1B);
	/* insert the required clock and edge value of TCCR1B Register */
	TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->clock) | ((Config_Ptr->edge)<<6);
	TCNT1 = 0;/* Initial Value for Timer1 */
	ICR1 = 0;/* Initial Value for the input capture register */
	/* Enable the Input Capture interrupt to generate an interrupt when edge is detected*/
	TIMSK = TIMSK | (1<<TICIE1);
}

/*
 * Description: Function to set the Call Back function address.
 */
void ICU_setCallBack(void(*a_ptr)()){

	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}

/*
 * Description: Function to set the required edge detection.
 */
void ICU_setEdgeDetection(const ICU_Edge_Type a_edgeType){

	TCCR1B = (TCCR1B & 0xBF) | ((a_edgeType)<<6);
}

/*
 * Description: Function to get the Timer1 Value when the input is captured
 *              The value stored at Input Capture Register ICR1
 */
uint16 ICU_getInputCaptureValue(){
	return ICR1;
}

/*
 * Description: Function to clear the Timer1 Value to start count from ZERO
 */
void ICU_clearTimerValue(){
	TCNT1 = 0;
}

/*
 * Description: Function to disable the Timer1 to stop the ICU Driver
 */
void ICU_DeInitial(){
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;

	/* Disable the Input Capture interrupt*/
		TIMSK = TIMSK & ~(1<<TICIE1);
}
