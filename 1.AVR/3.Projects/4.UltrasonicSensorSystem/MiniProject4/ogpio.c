#include "ogpio.h" /*including the GPIO header file*/
#include "ocommon_macros.h"/* To use the macros */
#include "avr/io.h" /* To use the IO Ports Registers */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description :
 * Setup the direction of the required pin input/output.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
void GPIO_setupPin(uint8 port_number,uint8 pin_number,GPIO_PinType direction){
	/*
		 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
		 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
		 * In this case the input is not valid port/pin number
		 */
	if(port_number >= MAX_PORT_NUM || pin_number >= MAX_PIN_NUM){
		/* Do nothing */
	}else{
		switch(port_number){
		/* Setup the pin direction as required */
		case PORTA_ID:
			if(direction == PIN_OUTPUT){
				SET(DDRA,pin_number);
			}else{
				CLEAR(DDRA,pin_number);
			}
			break;
		case PORTB_ID:
			if(direction == PIN_OUTPUT){
				SET(DDRB,pin_number);
			}else{
				CLEAR(DDRB,pin_number);
			}
			break;
		case PORTC_ID:
			if(direction == PIN_OUTPUT){
				SET(DDRC,pin_number);
			}else{
				CLEAR(DDRC,pin_number);
			}
			break;
		case PORTD_ID:
			if(direction == PIN_OUTPUT){
				SET(DDRD,pin_number);
			}else{
				CLEAR(DDRD,pin_number);
			}
			break;
		}
	}

}

/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
void GPIO_writePin(uint8 port_number,uint8 pin_number,uint8 value){
	/*
		 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
		 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
		 * In this case the input is not valid port/pin number
		 */
	if(port_number >= MAX_PORT_NUM || pin_number >= MAX_PIN_NUM){
		/* Do nothing */
	}else{
		/* Write the pin value as required */
		switch(port_number){
		case PORTA_ID:
			if(value == HIGH){
				SET(PORTA,pin_number);
			}else{
				CLEAR(PORTA,pin_number);
			}
			break;
		case PORTB_ID:
			if(value == HIGH){
				SET(PORTB,pin_number);
			}else{
				CLEAR(PORTB,pin_number);
			}
			break;
		case PORTC_ID:
			if(value == HIGH){
				SET(PORTC,pin_number);
			}else{
				CLEAR(PORTC,pin_number);
			}
			break;
		case PORTD_ID:
			if(value == HIGH){
				SET(PORTD,pin_number);
			}else{
				CLEAR(PORTD,pin_number);
			}
			break;
		}
	}
}
/*
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */
uint8 GPIO_readPin(uint8 port_number,uint8 pin_number){
	uint8 read_value = LOW;
	/*
		 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
		 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
		 * In this case the input is not valid port/pin number
		 */
	if(port_number >= MAX_PORT_NUM || pin_number >= MAX_PIN_NUM){
		/* Do nothing */
	}else{
		/* Read the pin value as required */
		switch(port_number){
		case PORTA_ID:
			if(CHECK_SET(PORTA,pin_number)){
				read_value = HIGH;
			}else{
				read_value = LOW;
			}
			break;
		case PORTB_ID:
			if(CHECK_SET(PORTB,pin_number)){
				read_value = HIGH;
			}else{
				read_value = LOW;
			}
			break;
		case PORTC_ID:
			if(CHECK_SET(PORTC,pin_number)){
				read_value = HIGH;
			}else{
				read_value = LOW;
			}
			break;
		case PORTD_ID:
			if(CHECK_SET(PORTD,pin_number)){
				read_value = HIGH;
			}else{
				read_value = LOW;
			}
			break;
		}
	}
	return read_value;

}
/*
 * Description :
 * Setup the direction of the required port all pins input/output.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_setupPort(uint8 port_number,GPIO_PortType direction){
	/*
		 * Check if the input number is greater than NUM_OF_PORTS value.
		 * In this case the input is not valid port number
		 */
	if(port_number >= MAX_PORT_NUM){
		/* Do nothing */
	}else{
		switch(port_number){

		case PORTA_ID:
			DDRA = direction;
			break;
		case PORTB_ID:
			DDRB = direction;
			break;
		case PORTC_ID:
			DDRC = direction;
			break;
		case PORTD_ID:
			DDRD = direction;
			break;

		}

	}
}
/*
 * Description :
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_writePort(uint8 port_number,uint8 value){
	/*
		 * Check if the input number is greater than NUM_OF_PORTS value.
		 * In this case the input is not valid port number
		 */
	if(port_number >= MAX_PORT_NUM){
		/* Do nothing */
	}else{
		/* Write the port value as required */
		switch(port_number){

		case PORTA_ID:
			PORTA = value;
			break;
		case PORTB_ID:
			PORTB = value;
			break;
		case PORTC_ID:
			PORTC = value;
			break;
		case PORTD_ID:
			PORTD = value;
			break;

		}
	}
}
/*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 */
uint8 GPIO_readPort(uint8 port_number){
	uint8 read_value = LOW;
	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if(port_number >= MAX_PORT_NUM){
		/* Do nothing */
	}else{
		/* Read the port value as required */
		switch(port_number){

		case PORTA_ID:
			read_value = PINA;
			break;
		case PORTB_ID:
			read_value = PINB;
			break;
		case PORTC_ID:
			read_value = PINC;
			break;
		case PORTD_ID:
			read_value = PIND;
			break;

		}

	}
	return read_value;
}
