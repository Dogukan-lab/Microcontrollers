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

/*
 * This method switches the state of the program
 * When a person is detected it will print a msg to the LCD
 * When interrupt for button is pressed,
 * Laser will go back to normal functionality
 */
//void switch_state(ldr_state *state) {
	//*state = TRIGGERED;
	//return *state;
//}
