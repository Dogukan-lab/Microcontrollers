/*
 * ldr.c
 *
 * Created: 4/5/2022 3:13:58 PM
 *  Author: doguk
 */ 

#define F_CPU 8e6

#include <xc.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "ldr.h"
#include "../command_center/command_center.h"
#include "../lcd/lcd.h"

#define BIT(x) (1 << (x))

/*
 * Converts ADCH value to a calculated resistance
 * returns calculated resistance 
 */
uint16_t ldr_getlux(long adcresistance) {
	double a = adcresistance/(double)LDR_B;
	return (uint16_t) ((double)LDR_A*(pow((double)a, (double)LDR_C)));
}

/*
 * Initializes ADC on port F
 * For now it is on free running,
 * this will be changed in the future
 */
static void adcInit() {
	ADMUX = 0b11100001;
	ADCSRA = 0b11100110;
}

/*
 * This method gets the value after conversion
 * This method returns a 16-bit integer 
 */
uint16_t get_ldr_value() {
	 ADCSRA |= (1 << ADSC);				// Start conversion
	 //while(ADCSRA & (1 << ADSC));		// Wait till conversion completed
	return ldr_getlux(ADCH);			// Calculate value, send it to check_state();
}

int check_state() {
	uint16_t ldr_value = get_ldr_value();
	if (ldr_value > LDR_LOW) {
		return 1;
	}
	return 0;	
}

/*
 * Timer interrupt
 * After TIMER_TRIGGER_VAL reached check state of LDR
 */
ISR(TIMER2_COMP_vect) {
	if (OCR2 == TIMER_TRIGGER_VAL) {
		OCR2 = 0; // Reset Comparator
		
		if(check_state()) {
			check_program_state(LASER_DETECTION_OFF);
		}
	} 
	else {
		OCR2 = TIMER_TRIGGER_VAL; // Reset Comparator
	}
}

/*
 * Initializes all components for LDR reading
 */ 
void init_ldr(void) {
	DDRA = 0xFF;
	DDRF = 0x00;
	
	TIMSK |= (1 << 7); //Sets interrupt for timer 2
	TCCR2 |= 0b00001101; //set CTC mode
	OCR2 = TIMER_TRIGGER_VAL; //Sets compare value for timer event
	
	adcInit();
	_delay_ms(100);
}

/*
 * Starts timer up again
 * Used when stop_timer has been called,
 * And timer is needed again for laser detection
 */
void start_timer() {
	TCCR2 |= 0b00001101; //set CTC mode
	OCR2 = TIMER_TRIGGER_VAL; //Sets compare value for timer event
	lcd_clear();
}

/*
 * Stops the timer
 * When a person has been detected
 */
void stop_timer() {
	TCCR2 = 0x00;
}