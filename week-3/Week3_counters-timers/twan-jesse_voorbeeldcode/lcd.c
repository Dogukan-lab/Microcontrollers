/*
 * lcd.c
 *
 * Created: 3/23/2022 3:45:06 PM
 *  Author: doguk
 */ 
#define F_CPU 8e6

// Including all the needed functions
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "LCD.h"


// Defining the ports the display is on
#define LCD_E 	6  // RA6 UNI-6
#define LCD_RS	4  // RA4 UNI-6

// Locks in a set position by setting E high and low
void lcd_strobe_lcd_e(void) {
	PORTA |= (1<<LCD_E);	// set E high
	_delay_ms(1);			// Small delay to process
	PORTA &= ~(1<<LCD_E);  	// set E low
	_delay_ms(1);			// small delay to process
}

void LCD_toggle_E(void) {
	PORTA |= 0x01000000;
	_delay_ms(1);			
	PORTA &= 0x10111111;  
	_delay_ms(1);		
}


/*
 * Sets the lcd display to the correct 4 pin mode.
 */
void init_4bits_mode(void) {
	// PORTC output mode and all low (also E and RS pin)
	DDRA = 0xFF;
	PORTC = 0x00;
	PORTA = 0x00;
	//PORTA = 0xFF;

	// Step 2 (table 12)
	PORTC = 0x20;	// function set
	lcd_strobe_lcd_e();

	// Step 3 (table 12)
	PORTC = 0x20;   // function set
	lcd_strobe_lcd_e();
	PORTC = 0x80;
	lcd_strobe_lcd_e();

	// Step 4 (table 12)
	PORTC = 0x00;   // Display on/off control
	lcd_strobe_lcd_e();
	PORTC = 0xF0;
	lcd_strobe_lcd_e();

	// Step 4 (table 12)
	PORTC = 0x00;   // Entry mode set
	lcd_strobe_lcd_e();
	PORTC = 0x60;
	lcd_strobe_lcd_e();
}

// Writes a command to the LCD display
// This by setting RS high
void lcd_write_char(unsigned char byte) {
	// First nibble.
	PORTC = byte;
	PORTA |= (1<<LCD_RS);
	lcd_strobe_lcd_e();

	// Second nibble
	PORTC = (byte<<4);
	PORTA |= (1<<LCD_RS);
	lcd_strobe_lcd_e();
}


// Writes a command to the LCD display
// This by setting RS low
void lcd_write_command(unsigned char byte) {
	// First nibble.
	PORTC = byte;
	PORTA &= ~(1<<LCD_RS);
	lcd_strobe_lcd_e();

	// Second nibble
	PORTC = (byte<<4);
	PORTA &= ~(1<<LCD_RS);
	lcd_strobe_lcd_e();
}

void lcd_clear() {
	lcd_write_command (0x01); // 0x01 clear the entire display
	_delay_ms(2);			  // small delay
	lcd_write_command (0x80); // 0x80 moves the cursor to the start
}

/*
* Sets the LCD display to the correct 4 pin mode. Also clears the display before starting
*/
void LCD_init() 
{
		// Setting DDRC to output, these are used in writing data to the LCD
		DDRC = 0xFF;			
		PORTC = 0xFF;
		
		// Setting the LCD to use the 4 bit mode
		init_4bits_mode();
		
		// Wait a bit to complete the init
		_delay_ms(10);
		
		// Clearing the LCD
		lcd_clear();
}

/*
* Given a string pointer (char array) this method will
* print that text to the display of the LCD
*/
void LCD_display_text(char *str)
{
	// Going until the value in the string pointer is 0
	while (*str) {
		// Moving the string pointer by one up
		lcd_write_char(*str++);
	}
}

/*
* Given a position the method move the cursor to that position.
* 0 == first line
* 40 == second line
*/
void LCD_set_cursor(int position)
{
	// Bit 8 should be 1 to change cursor
	char command = (position | (1<<7));
	lcd_write_command(command);
}