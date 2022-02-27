/*
 * lcd.h
 *
 * Created: 2/16/2022 12:41:10 PM
 *  Author: doguk
 */ 

#ifndef LCD_H
#define LCD_H
void init();
void display_text(char *str);
void set_cursor(int position);
#endif