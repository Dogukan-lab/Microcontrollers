
#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"


void lcd_strobe_lcd_e(void) {
	PORTA |= (1<<LCD_E);	// E high
	_delay_ms(1);			// nodig
	PORTA &= ~(1<<LCD_E);  	// E low
	_delay_ms(1);			// nodig?
}

void init_ram() {
	DDRD = 0xFF;
	DDRA = 0xFF;
	PORTC = 0x00;
	PORTA = 0x00;
}

void init_4bits_mode() {
	PORTC = 0x20;	// Function set first 4 bit modifier
	lcd_strobe_lcd_e();
	
	PORTC = 0x20;   // Function set second 4 bit modifier, now switching LCD to 4-bit operation mode
	lcd_strobe_lcd_e();
	PORTC = 0x80;
	lcd_strobe_lcd_e();
	
	PORTC = 0x00;   // Display on/off control
	lcd_strobe_lcd_e();
	PORTC = 0xF0;
	lcd_strobe_lcd_e();
	
	PORTC = 0x00;   // Entry mode set
	lcd_strobe_lcd_e();
	PORTC = 0x60;
}

/*
* Sends the data from a string or int to the LCD
* Does it in two nibbles
* First nibble is 1st 4 bits, second nibble 2nd 4 bits
*/
void lcd_write_data(unsigned char byte) {
	//First nibble
	PORTC = byte;
	PORTA |= (1<<LCD_RS);
	lcd_strobe_lcd_e();
	
	//Second nibble
	PORTC = (byte << 4);
	PORTA |= (1<<LCD_RS);
	lcd_strobe_lcd_e();
}

/*
* Writes commands to the LCD screen eg. [lcd_clear()]
* Also does this in two nibbles
*/
void lcd_write_cmd(unsigned char byte) {
	// First nibble
	PORTC = byte;
	PORTA &= ~(1<<LCD_RS);
	lcd_strobe_lcd_e();

	// Second nibble
	PORTC = (byte<<4);
	PORTA &= ~(1<<LCD_RS);
	lcd_strobe_lcd_e();
}

/*
* Clears LCD screen
*/
void lcd_clear() {
	lcd_write_cmd(0x01);
	_delay_ms(5);
	lcd_write_cmd(0x80);
}

/*
* Initializes the LCD screen, and already clears it for use.
*/
void init_lcd() {
	init_ram();
	_delay_ms(10);
	init_4bits_mode();
	_delay_ms(10);
	lcd_clear();
}

/*
* Writes a string through the [lcd_write_data()] method
*/
void lcd_write_string (const char *str) {
	for (; *str; str++)
	{
		lcd_write_data(*str);
	}
}

/*
* Function to be used to set the cursor of the LCD to a certain position
*/
void set_cursor(int position){
	lcd_write_cmd(0x07);
	_delay_ms(10);
	lcd_write_cmd(0x80);
}

/*
* Where the magic happens
*/
int main (void) {
	//Setup space for commands
	DDRC = 0xFF;
	PORTC = 0xFF;
	init_lcd();
	lcd_write_string("Hallo");
	
	while(1){
		//Do nothing in here, not necessary
	
	}
	
	return 1;
}