/*
 * opwm.h
 *
 *  Created on: Oct 9, 2022
 *      Author: Dell
 */

#ifndef OPWM_H_
#define OPWM_H_

#include "std_define_types.h"
/*******************************************************************************
 *                               Prototypes                                    *
 *******************************************************************************/
/*
 * Description:
 * The function responsible for trigger the Timer0 with the PWM Mode
 * The generated PWM signal frequency will be 500Hz to control the DC Motor speed.
 */
void PWM_Timer0_Start(uint8 duty_cycle);

#endif /* OPWM_H_ */
