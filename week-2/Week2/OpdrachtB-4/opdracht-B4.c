/*
 * main.c
 *
 * Created: 2/16/2022 12:17:57 PM
 *  Author: doguk
 */ 

#include <xc.h>
#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

typedef struct PATTERN_STRUCT {
	unsigned char data;
} PATTERN_STRUCT;

PATTERN_STRUCT pattern[] = {
	{0x40}, {0x20}, {0x01}, {0x02}, {0x40}, {0x10}, {0x08}, {0x04}
};

int main(void)
{
	DDRE = 0xFF;
	
	EICRA |= 0x0B;
	EIMSK = 0x03;
	sei();
	
	int count = 0; //Om door de array heen te lopen
	int arraySize = sizeof pattern / sizeof pattern[0];
	
    while(1)
    {
        if(count == arraySize) count = 0;
		
		PORTE = pattern[count].data;
		count++;
		
		wait(100);
    }
}