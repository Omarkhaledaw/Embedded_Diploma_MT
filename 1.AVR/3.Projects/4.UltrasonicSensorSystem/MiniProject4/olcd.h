/*
 * olcd.h
 *
 *  Created on: Oct 7, 2022
 *      Author: Dell
 */

#ifndef OLCD_H_
#define OLCD_H_

#include "std_define_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define LCD_BIT_MODE	8

#if ((LCD_BIT_MODE != 4) && (LCD_BIT_MODE != 8))

#error "Incorrect bit mode"

#endif

#define LCD_DATA_PATH	PORTA_ID

#define RS_PIN_SETUP	PORTB_ID
#define ENABLE_SETUP	PORTB_ID

#define RS_PIN			PIN0
#define ENABLE_PIN		PIN2

#if (LCD_BIT_MODE == 4)

#define LCD_DB4_PIN					PIN3
#define LCD_DB5_PIN					PIN4
#define LCD_DB6_PIN					PIN5
#define LCD_DB7_PIN					PIN6

#endif

/* LCD Commands */
#define LCD_CLEAR_COMMAND                    0x01
#define LCD_GO_TO_HOME                       0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE        0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE         0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#define LCD_CURSOR_OFF                       0x0C
#define LCD_CURSOR_ON                        0x0E
#define LCD_SET_CURSOR_LOCATION              0x80
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * Initialize the LCD:
 * 1. Setup the LCD pins directions by use the GPIO driver.
 * 2. Setup the LCD Data Mode 8-bits.
 */
void LCD_initial();
/*
 * Description :
 * Send the required command to the screen
 */
void LCD_send(uint8 command);
/*
 * Description :
 * Display the required character on the screen
 */
void LCD_displayCharacter(uint8 character);
/*
 * Description :
 * Display the required string on the screen
 */
void LCD_displayString(const char*string);
/*
 * Description :
 * Move the cursor to a specified row and column index on the screen
 */
void LCD_move(uint8 row,uint8 column);
/*
 * Description :
 * Display the required string in a specified row and column index on the screen
 */
void LCD_stringRowColumn(uint8 row,uint8 column,const char*string);
/*
 * Description :
 * Display the required decimal value on the screen
 */
void LCD_integer2String(int data);
/*
 * Description :
 * Send the clear screen command
 */
void LCD_clear();

#endif /* OLCD_H_ */
