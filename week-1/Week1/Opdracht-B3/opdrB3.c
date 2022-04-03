/*
 * main.c
 *
 * Created: 4/3/2022 5:22:54 PM
 *  Author: doguk
 */ 

#define F_CPU 8e6
#include <xc.h>

int main(void)
{
	DDRD = 0xFF; //Geheugen openzetten voor input
	
	while(1)
	{
		if (PINC & 0x01) // Check of knop ingedrukt is
		{
			PORTD = 0x80; // Zet led aan
		}
		else
		{
			PORTD = 0x00; // Zet led uit
		}
	}
}
