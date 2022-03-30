/*
 * main.c
 *
 * Created: 2/23/2022 11:30:40 AM
 *  Author: doguk
 */ 

#include <xc.h>
#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include "lcd.h"

#define BIT(x) 1 << (x);

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

int main( void ) {
	// Init I/O
	DDRD &= ~BIT(7);		// PD7 op input: DDRD=xxxx xxx0
	TCCR2 = 0b00000111;		// counting via PD7, rising edge	// PORTD(7) output, PORTD(6:0) input
	
	_delay_ms(1500);
	init_4bits_mode();
	
	// Loop forever
	while (1) {
		lcd_clear();
		
		int value = TCNT2;
		char text[16];
		
		sprintf(text, "Clicks: %d", value);
		
		lcd_write_string((char *) value);
		_delay_ms(500);
	}

	return 0;
}	