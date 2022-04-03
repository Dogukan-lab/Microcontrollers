
#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"

/*
* Where the magic happens
*/
int main (void) {
	//Setup space for commands
	init_lcd();
	
	while(1){
		//Do nothing in here, not necessary
		repeat_write("TEST");
		repeat_write("PRANKED");
	}
	
	return 1;
}