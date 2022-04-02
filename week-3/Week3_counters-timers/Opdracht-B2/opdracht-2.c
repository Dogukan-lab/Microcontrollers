/*
 * main.c
 *
 * Created: 3/30/2022 10:37:31 AM
 *  Author: doguk
 */ 

#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BIT(x)			(1 << (x))

void init_timer2(void);

#define TIME_PRESCALER (1 << CS12) | (1 << CS11) | (1 << CS10) //Set timer2 prescaler to 1024
#define TIMER_HIGH_VAL 195 //25ms for 1024 prescale
#define TIMER_LOW_VAL 115 //15ms for 1024 prescale

ISR(TIMER2_COMP_vect) {
	//Check compare val
	if (OCR2 == TIMER_LOW_VAL) {
		OCR2 = TIMER_HIGH_VAL;
	}
	else {
		OCR2 = TIMER_LOW_VAL;
	}
		PORTD ^= BIT(3);
		
}

void init_timer2(void) {
	TIMSK |= (1 << 7); //Sets interrupt for timer 2
	TCCR2 |= 0b00001101; //set CTC mode
	OCR2 = TIMER_HIGH_VAL; //Sets compare value for timer event
	
	sei(); // Turns on all ISR's
}

int main (void) {
	DDRD |= BIT(3);
	
	init_timer2();
	
	while (1) { /*Keeps thingy alive */ }
	
	return 0;
}