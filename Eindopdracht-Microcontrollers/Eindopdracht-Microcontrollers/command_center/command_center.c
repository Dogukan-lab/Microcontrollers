/*
 * command_center.c
 *
 * Created: 4/5/2022 5:42:34 PM
 *  Author: doguk
 */ 
#define F_CPU 8e6

#include <xc.h>
#include <stdio.h>
#include <util/delay.h>

#include "command_center.h"
#include "../buzzer/notes.h"
#include "../ldr/ldr.h"
#include "../lcd/lcd.h"


PROGRAM_STATE state;

void program_init() {
	init_lcd();	
	check_program_state(LASER_DETECTION_ON);
}

/*
 * This method switches the state of the program
 * When a person is detected it will print a msg to the LCD
 * When interrupt for button is pressed,
 * Laser will go back to normal functionality
 */
void set_program_state(PROGRAM_STATE state) {
	switch(state) {
		case STARTUP:
			program_init();
			// Enable LCD and set state to laser_on
			break;
		case LASER_DETECTION_ON:
			lcd_clear();
			_delay_ms(10);
			init_ldr();
			break;
		case LASER_DETECTION_OFF:
			// Disable timer 2
			stop_timer();
			check_program_state(BUZZER_ON);
			break;
		case BUZZER_ON:
			welcome_customer();
			// Enable melody
			break;
		case BUZZER_OFF:
			// Disable melody
			break;
	}
}

void welcome_customer() {
	//State van laser triggered
	//LCD write "Welcome ...."
	//Buzzer melodie aanroepen
	lcd_clear();
	lcd_write_string("Welcome customer");
	start_music();
}

