#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

// Goes 1 led backwards 
ISR( INT0_vect ) {
	
	if(PORTC > 0x01) PORTC >>= 1;
	else PORTC = 0x01;
	
	wait(500);
}

// Goes 1 led forward 
ISR( INT1_vect ) {
	
	if (PORTC < 0x80) PORTC <<= 1;
	else PORTC = 0x80;
		 
	wait(500);
}

// Setup to use the interrupts and leds
int main( void ) {
	DDRD = 0xF0;
	DDRC = 0xFF;
	PORTC = 0x01;

	EICRA |= 0x0B;	//INT1 falling edge, INT0 Rising edge	
	EIMSK |= 0x03;	//Enabling INT1 & INT0
	sei();			//Starts all interrupts	

	while (1) {
	}

	return 1;
}