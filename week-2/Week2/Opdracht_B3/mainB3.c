/*
 * main.c
 * In deze opdracht wordt de 7-segment display gebruikt om nummers op te tellen
 * De communicatie om het op te tellen wordt via een interrupt gedaan
 * Created: 2/9/2022 1:12:30 PM
 *  Author: doguk
 */ 

#include <xc.h>
#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int digit = 0;

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

const unsigned char Numbers [16] = {
	// dPgfe dcba
	0x3F, // 0
	0x06, // 1
	0x5B, // 2
	0x4F, // 3
	0x66, // 4
	0x6D, // 5
	0x7D, // 6
	0x07, // 7
	0x7F, // 8
	0x6F, // 9
	0b01110111, //10
	0b01111100, //11
	0b00111001, //12
	0b01011110, //13
	0b01111001, //14
	0b01110001 //15
};

void segmentDisplay (int digit){

	switch(digit){
		case 0:
		PORTE = Numbers[digit];
		break;
		
		case 1:
		PORTE = Numbers[digit];
		break;
		
		case 2:
		PORTE = Numbers[digit];
		break;
		
		case 3:
		PORTE = Numbers[digit];
		break;
		
		case 4:
		PORTE = Numbers[digit];
		break;
		
		case 5:
		PORTE = Numbers[digit];
		break;
		
		case 6:
		PORTE = Numbers[digit];
		break;
		
		case 7:
		PORTE = Numbers[digit];
		break;
		
		case 8:
		PORTE = Numbers[digit];
		break;
		
		case 9:
		PORTE = Numbers[digit];
		break;
		
		case 10:
		PORTE = Numbers[digit];
		break;
		
		case 11:
		PORTE = Numbers[digit];
		break;
		
		case 12:
		PORTE = Numbers[digit];
		break;
		
		case 13:
		PORTE = Numbers[digit];
		break;
		
		case 14:
		PORTE = Numbers[digit];
		break;
		
		case 15:
		PORTE = Numbers[digit];
		break;
		
	}
}

ISR( INT0_vect ) {	
	wait(1000);
	if(digit > 15){
		 //digit = 0; 
		 PORTE = Numbers[14];
		 return;
	}
	segmentDisplay(digit); 
	digit++;
}


int main() {
	DDRD = 0xF0; //Maak geheugen vrij voor input van buttons
	DDRE = 0xFF; //Maak geheugen vrij voor output van pins
	
	EICRA |= 0x0B; //Rising edge voor het ISR
	EIMSK |= 0x03; //Interrupt op portd 1 & 2 openzetten
	sei();
	
	while(1){
	}
	
}