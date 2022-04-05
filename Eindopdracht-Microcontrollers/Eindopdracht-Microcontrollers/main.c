/*
 * main.c
 *
 * Created: 4/4/2022 12:46:59 PM
 *  Author: doguk
 */ 

#define F_CPU 8e6

#include <xc.h>
#include <stdio.h>
#include <util/delay.h>
#include "ldr/ldr.h"
#include "lcd/lcd.h"
#include <avr/interrupt.h>

#define BIT(x) (1 << (x))


void init_interrupt_0() {
	DDRD = 0x00;
	
	EICRA |= 0x0B; // Rising edge
	EIMSK |= 0x01; // Turning int_0 on
}

ISR(INT0_vect) {
	start_timer();
}

int main(void) {
	
	sei(); // Turn on interrupts
	
	init_interrupt_0();
	
	init_ldr();
	
	init_lcd();
   
   
   while(1)
   {
	     
	   //while(ADCSRA & (1 << ADSC)); //Wait til completion

		//if(ldr_getlux(ADCH) < 6200) {
			//repeat_write("IN RANGE");
		//}
		//else {
			//repeat_write("OUT OF RANGE");
		//}
		//sprintf(text, "Value is: %d", ldr_getlux(ADCH));
		//repeat_write(text);
   }
   
   return 0;
}