/*
 * main.c
 *
 * Created: 4/3/2022 6:14:13 PM
 *  Author: doguk
 */ 

#include <xc.h>

typedef struct {
	unsigned char data;
} PATTERN_struct;

PATTERN_struct pattern[] = {
	{0x01}, {0x02}, {0x04}, {0x08}, {0x10}, {0x20}, {0x40}, {0x80}, {0x40}, {0x20}, {0x10},
	{0x08}, {0x04}, {0x02}, {0x01}
}

int main(void)
{
	DDRD = 0xFF;
	
	int index = 0;
	
	while(1) {
		
		if ((sizeof(pattern)/ sizeof(pattern[0])) == index)
		{
			index = 0;
		}
		
		PORTD = pattern[index].data;
		
		wait(250);
		
		index++;
	}
	
	return 1;
}
