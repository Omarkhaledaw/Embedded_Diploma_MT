#include "olcd.h"
#include "oultrasonic.h"
#include<avr/interrupt.h> /* to enable global interrupt */
#include<util/delay.h>    /* to use delay function */

int main(){
	/* initialization */
	uint8 Distance =0;/* variable to store the value returned from sensor */
	SREG |= (1<<7);/* Enable Global Interrupt I-Bit */

	Ultrasonic_init();
	LCD_initial();
	LCD_stringRowColumn(0,0,"Distance=     Cm");
	while(1){
		/*Calculating distance*/
		Distance = Ultrasonic_readDistance();
		LCD_move(0,10);
		LCD_integer2String(Distance);
		/*Adding a space to clear that zero appearing when distance less than 100*/
		if(Distance<100){
			LCD_displayCharacter(' ');
		}
	}
}
