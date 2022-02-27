#define F_CPU 8e6
#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

typedef struct {
	unsigned char data;
	} PATTERN_struct;
	
PATTERN_struct pattern[] = {
	{0x01}, {0x02}, {0x04}, {0x08}, {0x10}, {0x20}, {0x40}, {0x80}, {0x40}, {0x20}, {0x10},
		{0x08}, {0x04}, {0x02}, {0x01}
}

void wait( int ms )
{
	for (int i=0; i < ms; i++){
		_delay_ms(1);
	}
}

int main(void)
{
	DDRD = 0xFF;
	
	int index = 0;
	
	while(1) {
		
		if (PINC & 0x01)
		{
			PORTD = 0x80;
			wait(250);
			PORTD = 0x00;
			wait(250);
		}
		else 
		{
			PORTD = 0x80;
			wait(1000);
			PORTD = 0x00;
			wait(1000);
		}
	}
	
	return 1;
}