/*
 * oicu.h
 *
 *  Created on: Oct 11, 2022
 *      Author: Dell
 */

#ifndef OICU_H_
#define OICU_H_

#include "std_define_types.h"

/*******************************************************************************
 *                      Definitions                                  *
 *******************************************************************************/
#define ICU_PORT	PORTD_ID
#define ICU_PIN		PIN6
/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum {
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}ICU_Clock;
typedef enum{
	FALLING,RISING
}ICU_Edge_Type;

typedef struct{
	ICU_Clock clock;
	ICU_Edge_Type edge;
}ICU_Config;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description : Function to initialize the ICU driver
 * 	1. Set the required clock.
 * 	2. Set the required edge detection.
 * 	3. Enable the Input Capture Interrupt.
 * 	4. Initialize Timer1 Registers
 */
void ICU_initial(const ICU_Config * Config_Ptr);
/*
 * Description: Function to set the Call Back function address.
 */
void ICU_setCallBack(void(*a_ptr)(void));
/*
 * Description: Function to set the required edge detection.
 */
void ICU_setEdgeDetectionType(const ICU_Edge_Type edgeType);

/*
 * Description: Function to get the Timer1 Value when the input is captured
 *              The value stored at Input Capture Register ICR1
 */
uint16 ICU_getInputCaptureValue(void);

/*
 * Description: Function to clear the Timer1 Value to start count from ZERO
 */
void ICU_clearTimerValue(void);

/*
 * Description: Function to disable the Timer1 to stop the ICU Driver
 */
void ICU_DeInitial(void);
#endif /* OICU_H_ */
