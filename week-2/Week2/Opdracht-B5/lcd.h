/*
 * lcd.h
 *
 * Created: 2/16/2022 12:41:10 PM
 *  Author: doguk
 */ 

#ifndef LCD_H
#define LCD_H

#define LCD_E 	6  // RA6 UNI-6
#define LCD_RS	4  // RA4 UNI-6

void init_lcd();
void display_text(char *str);
void set_cursor(int position);
void lcd_write_string(const char *str);
void lcd_write_data(unsigned char byte);
void lcd_write_cmd(unsigned char byte);
void lcd_clear(void);
#endif