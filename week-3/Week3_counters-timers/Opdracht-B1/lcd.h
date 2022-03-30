/*
 * LCD.h
 *
 * Created: 16/02/2022 10:16:58
 *  Author: Twanv
 */ 

#ifndef LCD_H_
#define LCD_H_

	///*
	//* Sets the lcd display to the correct 4 pin mode. Also clears the display before starting
	//*/
	//void LCD_init();
	//
	///*
	//* Given a string pointer (char array) this method will
	//* print that text to the display of the LCD
	//*/
	//void LCD_display_text(char *str);
	//
	///*
	//* Given a position the method move the cursor to that position.
	//* 0 == first line
	//* 40 == second line
	//*/
	//void LCD_set_cursor(int position);
	
	void lcd_clear(void);
	void lcd_init_bruh();
	void lcd_write_string(char *str);
	


#endif /* LCD_H_ */