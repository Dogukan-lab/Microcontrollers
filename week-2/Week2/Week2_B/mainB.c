#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int ledIndex = 0;

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

ISR( INT0_vect ) {
	if(PORTC > PINC0)
	PORTC = PORTC << 1;
	wait(1000);
}

ISR( INT1_vect ) {
	if(PORTC < PINC7)
	PORTC = PORTC >> 1;
	wait(100);
}

int main( void ) {
	DDRD = 0xF0;
	DDRC = 0xFF;
	PORTC = 0x01;

	EICRA |= 0x0B;		
	EIMSK |= 0x03;
	sei();				

	while (1) {
	}

	return 1;
}