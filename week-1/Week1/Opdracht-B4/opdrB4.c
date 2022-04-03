/*
 * main.c
 *
 * Created: 4/3/2022 5:38:49 PM
 *  Author: doguk
 */ 

#define F_CPU 8e6
#include <xc.h>
#include <util/delay.h>
#include <stdbool.h>

int main(void)
{
	DDRD = 0xFF;
	PORTD = 0x01;
	bool switcher = true;
	
	while(1)
	{
		if (switcher)
		{
			PORTD = PORTD << 1;
			if(PORTD & 0x80)
			{
				switcher = false;
			}
			_delay_ms(250);
		}
		else
		{
			PORTD = PORTD >> 1;
			if (PORTD & 0x01)
			{
				switcher = true;
			}
			_delay_ms(250);
		}
	}
}
