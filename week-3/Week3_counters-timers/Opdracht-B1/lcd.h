/*
 * lcd.h
 *
 * Created: 3/23/2022 3:56:58 PM
 *  Author: doguk
 */ 


#ifndef LCD_H_
#define LCD_H_

	void lcd_strobe_lcd_e(void);
	void init_4bits_mode(void);
	void lcd_write_string(const char *str);
	void lcd_write_data(unsigned char byte);
	void lcd_write_cmd(unsigned char byte);
	void lcd_clear(void);
	void init_lcd_bruh();


#endif /* LCD_H_ */