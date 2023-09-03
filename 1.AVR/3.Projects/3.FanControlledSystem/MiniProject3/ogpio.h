/*
 * ogpio.h
 *
 *  Created on: Oct 5, 2022
 *      Author: Dell
 */

#ifndef OGPIO_H_
#define OGPIO_H_

#include "std_define_types.h"

/*******************************************************************************
 *                               Define                                        *
 *******************************************************************************/

#define PORTA_ID	0
#define PORTB_ID	1
#define PORTC_ID	2
#define PORTD_ID	3


#define MAX_PIN_NUM		8
#define MAX_PORT_NUM	4


#define PIN0	0
#define PIN1	1
#define PIN2	2
#define PIN3	3
#define PIN4	4
#define PIN5	5
#define PIN6	6
#define PIN7	7

/*******************************************************************************
 *                               Typedef                                       *
 *******************************************************************************/

typedef enum{
	PIN_INPUT,PIN_OUTPUT
}GPIO_PinType;

typedef enum{
	PORT_INPUT,PORT_OUTPUT=0xFF
}GPIO_PortType;

/*******************************************************************************
 *                               Prototypes                                    *
 *******************************************************************************/
/*
 * Description :
 * Setup the direction of the required pin input/output.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
void GPIO_setupPin(uint8 port_number,uint8 pin_number,GPIO_PinType direction);
/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
void GPIO_writePin(uint8 port_number,uint8 pin_number,uint8 value);
/*
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */
uint8 GPIO_readPin(uint8 port_number,uint8 pin_number);
/*
 * Description :
 * Setup the direction of the required port all pins input/output.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_setupPort(uint8 port_number,GPIO_PortType direction);
/*
 * Description :
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_writePort(uint8 port_number,uint8 value);
/*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 */
uint8 GPIO_readPort(uint8 port_number);

#endif /* OGPIO_H_ */
