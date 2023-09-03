#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void INT0_Initial(); //Prototype
void INT1_Initial(); //Prototype
void INT2_Initial(); //Prototype
void TIMER1_Initial(); //Prototype

unsigned int seconds=0; //Global variable
unsigned int minutes=0; //Global variable
unsigned int hours=0; //Global variable


int main (){
	//Setup
	unsigned int seg1 = 0; // Temporary variable
	unsigned int seg2 = 0; // Temporary variable
	unsigned int seg3 = 0; // Temporary variable
	unsigned int seg4 = 0; // Temporary variable
	unsigned int seg5 = 0; // Temporary variable
	unsigned int seg6 = 0; // Temporary variable

	DDRC = DDRC | 0x0F; //Declaring the first 4 pins in PORTC as OUTPUT
	DDRA = DDRA | 0x3F; //Declaring the first 6 pins in PORTA as OUTPUT

	PORTC = PORTC &0xF0; //Initializing the first 4 pins in PORTA with 0 (OFF)
	PORTA = PORTA &0xC0; //Initializing the first 6 pins in PORTA with 0 (OFF)

	SREG = SREG | (1<<7); //Enabling global interrupt

	INT0_Initial();
	INT1_Initial();
	INT2_Initial();
	TIMER1_Initial();
	//Loop
	while(1){
		PORTA = (1<<PA5);
		seg1 = seconds%10;
		PORTC = (PORTC & 0xF0) | (seg1 & 0x0F);
		_delay_ms(4);

		PORTA = (1<<PA4);
		seg2 = seconds/10;
		PORTC = (PORTC & 0xF0) | (seg2 & 0x0F);
		_delay_ms(4);

		PORTA = (1<<PA3);
		seg3 = minutes%10;
		PORTC = (PORTC & 0xF0) | (seg3 & 0x0F);
		_delay_ms(4);

		PORTA = (1<<PA2);
		seg4 = minutes/10;
		PORTC = (PORTC & 0xF0) | (seg4 & 0x0F);
		_delay_ms(4);

		PORTA = (1<<PA1);
		seg5 = hours%10;
		PORTC = (PORTC & 0xF0) | (seg5 & 0x0F);
		_delay_ms(4);

		PORTA = (1<<PA0);
		seg6 = hours/10;
		PORTC = (PORTC & 0xF0) | (seg6 & 0x0F);
		_delay_ms(4);

	}
}
void INT0_Initial(){
	DDRD = DDRD & ~(1<<PD2); //Declaring the 3rd pin in PORTD as INPUT
	GICR = GICR | (1<<INT0); //Enabling external interrupt request 0
	MCUCR = MCUCR | (1<<ISC01); //Enabling the falling edge of INT0
}
void INT1_Initial(){
	DDRD = DDRD & ~(1<<PD3); //Declaring the 4th pin in PORTD as INPUT
	GICR = GICR | (1<<INT1); //Enabling external interrupt request 0
	MCUCR = MCUCR | (1<<ISC11) | (1<<ISC10); //Enabling the rising edge of INT1
}
void INT2_Initial(){
	DDRB = DDRB & ~(1<<PB2); //Declaring the 3rd pin in PORTB as INPUT
	GICR = GICR | (1<<INT2); //Enabling external interrupt request 0
	// MCUCSR = MCUCSR & ~(1<<ISC2); Enabling the falling edge of INT2
}
void TIMER1_Initial(){
	TCNT1 = 0;
	OCR1A = 978; //Counts needed for timer1 with 1024 preascaler to reach 1 second
	TCCR1A = TCCR1A | (1<<FOC1A); //Specifying that non-PWM is used
	TCCR1B = TCCR1B | (1<<WGM12) | (1<<CS12) | (1<<CS10); //Specifying that CTC (OCR1) and 1024 prescaler is used
	TIMSK = TIMSK | (1<<OCIE1A); //Enabling output compare match A interrupt
}
ISR(INT0_vect){
	//Reset interrupt
	seconds=0;
	minutes=0;
	hours=0;
}
ISR(INT1_vect){
	//Pause interrupt
	TCCR1B = TCCR1B & ~(1<<CS10) & ~(1<<CS12); //Switching from 1024 prescaler to no clock source

}
ISR(INT2_vect){
	//Resume interrupt
	TCCR1B = TCCR1B | (1<<WGM12) | (1<<CS12) | (1<<CS10);

}
ISR(TIMER1_COMPA_vect){
	seconds++;
	if(seconds == 60){
		minutes++;
		seconds=0;
	}else if(minutes == 60){
		hours++;
		minutes=0;
	}
}
