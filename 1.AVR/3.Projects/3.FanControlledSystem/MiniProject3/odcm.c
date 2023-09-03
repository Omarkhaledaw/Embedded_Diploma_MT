#include "odcm.h"
#include "opwm.h"
#include "ogpio.h"

/*
*Description
* The Function responsible for setup the direction for the two motor pins through the GPIO driver.
* Stop at the DC-Motor at the beginning through the GPIO driver.*/
void DcMotor_Init(){
	/* configuring pins as output */
	GPIO_setupPin(MOTOR_PORT,MOTOR_PIN0,PIN_OUTPUT);
	GPIO_setupPin(MOTOR_PORT,MOTOR_PIN1,PIN_OUTPUT);
	/*Motor not working at the beginning*/
	GPIO_writePin(MOTOR_PORT,MOTOR_PIN0,LOW);
	GPIO_writePin(MOTOR_PORT,MOTOR_PIN1,LOW);
}
/*Description:
*The function responsible for rotate the DC Motor CW/ or A-CW or stop the motor based on the state input state value.
*Send the required duty cycle to the PWM driver based on the required speed value.*/
void DcMotor_Rotate(DcMotor_State state,uint8 speed){
		/*Switch case for the 4 speed cases*/
		switch (state){
		case Clockwise:
			/*Rotate Clockwise*/
			GPIO_writePin(MOTOR_PORT,MOTOR_PIN0,HIGH);
			GPIO_writePin(MOTOR_PORT,MOTOR_PIN1,LOW);
			break;
		case Anti_Clockwise:
			/*Rotate Anti Clockwise*/
			GPIO_writePin(MOTOR_PORT,MOTOR_PIN0,LOW);
			GPIO_writePin(MOTOR_PORT,MOTOR_PIN1,HIGH);
			break;
		case Stop:
			/*No rotation*/
			GPIO_writePin(MOTOR_PORT,MOTOR_PIN0,LOW);
			GPIO_writePin(MOTOR_PORT,MOTOR_PIN1,LOW);
			break;
		}
		/*Using PWM timer0_start to rotate the motor at the desired speed*/
		PWM_Timer0_Start(speed);
}
