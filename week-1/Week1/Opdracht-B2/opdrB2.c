/*
 * Created: 4/3/2022 5:17:35 PM
 *  Author: doguk
 */ 

#define F_CPU 8e6
#include <xc.h>
#include <util/delay.h>

int main(void)
{
	DDRD = 0xFF; //Geheugen openzetten voor input
	while(1)
	{
		PORTD = 0x80; // 8e bit van links
		_delay_ms(250);
		PORTD = 0x40; // 4e bit van links
		_delay_ms(250);
	}
}
