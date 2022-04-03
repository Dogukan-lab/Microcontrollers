/*
 * Created: 4/3/2022 4:38:16 PM
 *  Author: doguk
 *
 */ 

#define F_CPU 8e6
#include <xc.h>
#include <util/delay.h>

// Toggle van bepaalde LEDS
int main(void)
{
	DDRD = 0xFF;	// Geheugen openzetten voor input
	
	while(1)
	{
		PORTD = 0xAA; // Zet bit 8 & 2 aan, dit aan beide kanten
		_delay_ms(1000);
		PORTD = 0x00; // Reset leds
		_delay_ms(1);
		PORTD = 0x55; // Zet bit 3 & 1 aan, dit aan beide kanten
		_delay_ms(1000);
		PORTD = 0x00; // Reset leds
		_delay_ms(1);
	}
}
