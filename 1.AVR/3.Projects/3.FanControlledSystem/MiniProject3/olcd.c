/*
 * olcd.c
 *
 *  Created on: Oct 7, 2022
 *      Author: Dell
 */

#include "olcd.h"
#include "ogpio.h"
#include <util/delay.h>
#include "ocommon_macros.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description :
 * Initialize the LCD:
 * 1. Setup the LCD pins directions by use the GPIO driver.
 * 2. Setup the LCD Data Mode 8-bits.
 */
void LCD_initial(){

	GPIO_setupPin(RS_PIN_SETUP,RS_PIN,PIN_OUTPUT);
	GPIO_setupPin(ENABLE_SETUP,ENABLE_PIN,PIN_OUTPUT);
	_delay_ms(20);

#if (LCD_BIT_MODE == 4)

	GPIO_setupPin(LCD_DATA_PATH,LCD_DB4_PIN,PIN_OUTPUT);
	GPIO_setupPin(LCD_DATA_PATH,LCD_DB5_PIN,PIN_OUTPUT);
	GPIO_setupPin(LCD_DATA_PATH,LCD_DB6_PIN,PIN_OUTPUT);
	GPIO_setupPin(LCD_DATA_PATH,LCD_DB7_PIN,PIN_OUTPUT);

	LCD_send(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_send(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);

	LCD_send(LCD_TWO_LINES_FOUR_BITS_MODE);

#elif (LCD_BIT_MODE == 8)

	GPIO_setupPort(LCD_DATA_PATH,PORT_OUTPUT);

	LCD_send(LCD_TWO_LINES_EIGHT_BITS_MODE);

#endif

	LCD_send(LCD_CURSOR_OFF);
	LCD_send(LCD_CLEAR_COMMAND);
}
/*
 * Description :
 * Send the required command to the screen
 */
void LCD_send(uint8 command){

	GPIO_writePin(RS_PIN_SETUP,RS_PIN,LOW);
	_delay_ms(1); /* delay for processing Tas = 50ns */
	GPIO_writePin(ENABLE_SETUP,ENABLE_PIN,HIGH);
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

#if(LCD_BIT_MODE == 4)

	GPIO_writePin(LCD_DATA_PATH,LCD_DB4_PIN,GET_BIT(command,4));
	GPIO_writePin(LCD_DATA_PATH,LCD_DB5_PIN,GET_BIT(command,5));
	GPIO_writePin(LCD_DATA_PATH,LCD_DB6_PIN,GET_BIT(command,6));
	GPIO_writePin(LCD_DATA_PATH,LCD_DB7_PIN,GET_BIT(command,7));

	_delay_ms(1);
	GPIO_writePin(ENABLE_SETUP,ENABLE_PIN,LOW);
	_delay_ms(1);
	GPIO_writePin(ENABLE_SETUP,ENABLE_PIN,HIGH);
	_delay_ms(1);

	GPIO_writePin(LCD_DATA_PATH,LCD_DB4_PIN,GET_BIT(command,0));
	GPIO_writePin(LCD_DATA_PATH,LCD_DB5_PIN,GET_BIT(command,1));
	GPIO_writePin(LCD_DATA_PATH,LCD_DB6_PIN,GET_BIT(command,2));
	GPIO_writePin(LCD_DATA_PATH,LCD_DB7_PIN,GET_BIT(command,3));

	_delay_ms(1);
	GPIO_writePin(ENABLE_SETUP,ENABLE_PIN,LOW);
	_delay_ms(1);

#elif(LCD_BIT_MODE == 8)

	GPIO_writePort(LCD_DATA_PATH,command);
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(ENABLE_SETUP,ENABLE_PIN,LOW);
	_delay_ms(1); /* delay for processing Th = 13ns */

#endif
}
/*
 * Description :
 * Display the required character on the screen
 */
void LCD_displayCharacter(uint8 character){

	GPIO_writePin(RS_PIN_SETUP,RS_PIN,HIGH);
	_delay_ms(1); /* delay for processing Tas = 50ns */
	GPIO_writePin(ENABLE_SETUP,ENABLE_PIN,HIGH);
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

#if(LCD_BIT_MODE == 4)

	GPIO_writePin(LCD_DATA_PATH,LCD_DB4_PIN,GET_BIT(character,4));
	GPIO_writePin(LCD_DATA_PATH,LCD_DB5_PIN,GET_BIT(character,5));
	GPIO_writePin(LCD_DATA_PATH,LCD_DB6_PIN,GET_BIT(character,6));
	GPIO_writePin(LCD_DATA_PATH,LCD_DB7_PIN,GET_BIT(character,7));

	_delay_ms(1);
	GPIO_writePin(ENABLE_SETUP,ENABLE_PIN,LOW);
	_delay_ms(1);
	GPIO_writePin(ENABLE_SETUP,ENABLE_PIN,HIGH);
	_delay_ms(1);

	GPIO_writePin(LCD_DATA_PATH,LCD_DB4_PIN,GET_BIT(character,0));
	GPIO_writePin(LCD_DATA_PATH,LCD_DB5_PIN,GET_BIT(character,1));
	GPIO_writePin(LCD_DATA_PATH,LCD_DB6_PIN,GET_BIT(character,2));
	GPIO_writePin(LCD_DATA_PATH,LCD_DB7_PIN,GET_BIT(character,3));

	_delay_ms(1);
	GPIO_writePin(ENABLE_SETUP,ENABLE_PIN,LOW);
	_delay_ms(1);

#elif(LCD_BIT_MODE == 8)

	GPIO_writePort(LCD_DATA_PATH,character);
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(ENABLE_SETUP,ENABLE_PIN,LOW);
	_delay_ms(1); /* delay for processing Th = 13ns */

#endif
}
/*
 * Description :
 * Display the required string on the screen
 */
void LCD_displayString(const char*string){
	/*While loop for displaying every element of the string*/
	while((*string) != '\0'){
		LCD_displayCharacter(*string);
		string++;
	}
}
/*
 * Description :
 * Move the cursor to a specified row and column index on the screen
 */
void LCD_move(uint8 row,uint8 column){
	/*A reserved variable for the cursor location*/
	uint8 lcd_memory_address;
	/*Switch case for having 4 rows LCD*/
	switch(row){
	case 0:
		lcd_memory_address = column;
		break;
	case 1:
		lcd_memory_address = column + 0x40;
		break;
	case 2:
		lcd_memory_address = column + 0x10;
		break;
	case 3:
		lcd_memory_address = column + 0x50;
		break;
	}
	/*Setting the reserved variable as address to the cursorS*/
	LCD_send(lcd_memory_address|LCD_SET_CURSOR_LOCATION);

}
/*
 * Description :
 * Display the required string in a specified row and column index on the screen
 */
void LCD_stringRowColumn(uint8 row,uint8 column,const char *string){

	LCD_move(row,column);
	LCD_displayString(string);

}
/*
 * Description :
 * Display the required decimal value on the screen
 */
void LCD_integer2String(int data){

	char temp[16];
	itoa(data,temp,10);
	LCD_displayString(temp);/*displaying the converted integer using diplayString*/

}
/*
 * Description :
 * Send the clear screen command
 */
void LCD_clear(){

	LCD_send(LCD_CLEAR_COMMAND);/*Clearing the LCD*/

}
