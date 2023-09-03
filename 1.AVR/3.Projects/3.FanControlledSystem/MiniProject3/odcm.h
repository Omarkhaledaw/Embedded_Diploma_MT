/*
 * odcm.h
 *
 *  Created on: Oct 9, 2022
 *      Author: Dell
 */

#ifndef ODCM_H_
#define ODCM_H_

#include "std_define_types.h"

/*******************************************************************************
 *                               Definitions                                       *
 *******************************************************************************/
#define MOTOR_PORT	PORTB_ID
#define MOTOR_PIN0	PIN0
#define MOTOR_PIN1	PIN1
/*******************************************************************************
 *                               Typedef                                       *
 *******************************************************************************/

typedef enum{
	Clockwise,Anti_Clockwise,Stop
}DcMotor_State;

/*******************************************************************************
 *                               Prototypes                                    *
 *******************************************************************************/
/*
*Description
* The Function responsible for setup the direction for the two motor pins through the GPIO driver.
* Stop at the DC-Motor at the beginning through the GPIO driver.*/
void DcMotor_Init();
/*Description:
*The function responsible for rotate the DC Motor CW/ or A-CW or stop the motor based on the state input state value.
*Send the required duty cycle to the PWM driver based on the required speed value.*/
void DcMotor_Rotate(DcMotor_State state,uint8 speed);
#endif /* ODCM_H_ */
