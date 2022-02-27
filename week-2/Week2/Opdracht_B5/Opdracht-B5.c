/*
 * main.c
 *
 * Created: 2/16/2022 12:34:52 PM
 *  Author: doguk
 */ 

#include <xc.h>
#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"

#define LCD_E 	6  // RA6 UNI-6
#define LCD_RS	4  // RA4 UNI-6

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}



int main(void)
{
    while(1)
    {
        //TODO:: Please write your application code 
    }
}

void init(){
	
}

void display_text(char *str){
	
}

void set_cursor(int position){
	
}