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
#include <avr/io.h>
#include "ldr/ldr.h"
#include "lcd/lcd.h"
#include <avr/interrupt.h>

#define BIT(x) (1 << (x))

void init_timer() {
	TIMSK |= (1 << 7); //Sets interrupt for timer 2
	TCCR2 |= 0b00001101; //set CTC mode
	OCR2 = TIMER_TRIGGER_VAL; //Sets compare value for timer event
}

void init_interrupt_0() {
	DDRD = 0x00;
	
	EICRA |= 0x0B; // Rising edge
	EIMSK |= 0x01; // Turning int_0 on
}

ISR(INT0_vect) {
	start_timer();
}

/*
 * Timer interrupt
 * After TIMER_TRIGGER_VAL reached check state of LDR
 */
ISR(TIMER2_COMP_vect) {
	if (OCR2 == TIMER_TRIGGER_VAL) {
		OCR2 = 0; // Reset Comparator
		switch(check_state()){
			case 1:
				lcd_write_string("Welcome customer!");
				stop_timer();
				break;
		}
	} 
	else {
		OCR2 = TIMER_TRIGGER_VAL; // Reset Comparator
	}
}

void test_code() {
	
	char text[16];
	
	ADCSRA |= (1 << ADSC);				// Start conversion
	//while(ADCSRA & (1 << ADSC));		// Wait till conversion completed
	
	if(ldr_getlux(ADCH) < 6200) {
	repeat_write("IN RANGE");
	}
	else {
	repeat_write("OUT OF RANGE");
	}
	sprintf(text, "Value is: %d", ldr_getlux(ADCH));
	repeat_write(text);
}

int main(void) {
	
	sei(); // Turn on interrupts
	
	init_interrupt_0();
	init_timer();
	
	init_ldr();
	
	init_lcd();
   
   //start_music();
   
   while(1) {
	   
   }
   
   return 0;
}
