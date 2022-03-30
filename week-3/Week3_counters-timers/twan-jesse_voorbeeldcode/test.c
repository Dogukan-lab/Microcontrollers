/*
 * main.c
 *
 * Created: 2/16/2022 10:09:58 AM
 *  Author: Twanv
 */ 
#define F_CPU 8e6

#include <xc.h>
#include <stdio.h>
#include "LCD.h"
#include <util/delay.h>

#define BIT(x) (1 << (x))

int main(void)
{
	DDRD &= ~BIT(7);		// PD7 op input: DDRD=xxxx xxx0
	TCCR2 = 0b00000111;		// counting via PD7, rising edge
	
	_delay_ms(1500);
	
	LCD_init();
	
	while(1) {
		LCD_set_cursor(0);
		
		int value = TCNT2;
		char text[16];

		sprintf(text, "Clicks: %d", value);
		
		LCD_display_text(text);
		
		_delay_ms(500);
	}
	
	
	
}