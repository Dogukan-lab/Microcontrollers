/*
 * main.c
 *
 * Created: 4/4/2022 12:46:59 PM
 *  Author: doguk
 */ 

#define F_CPU 8e6

#include <xc.h>
#include <stdio.h>
#include <util/delay.h>
#include "lcd.h"

#define LDR_A 9000
#define LDR_B 165
#define LDR_C -1.65
uint16_t ldr_getlux(long adcresistance) {
	double a = adcresistance/(double)LDR_B;
	return (uint16_t) ((double)LDR_A*(pow((double)a, (double)LDR_C)));
}

void adcInit() {
		
	ADMUX = 0b11100001;
	ADCSRA = 0b11100110;
}

int map(int x, int in_min, int in_max, int out_min, int out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int main(void) {
	
	DDRA = 0xFF;
	DDRF = 0x00;
	
	adcInit();
	_delay_ms(500);
	
	init_lcd();
	_delay_ms(500);
   
   while(1)
   {
	   char text[16];
	   
	   ADCSRA |= (1 << ADSC); //Start conversion
	   
	   //while(ADCSRA & (1 << ADSC)); //Wait til completion


		if(ldr_getlux(ADCH) < 5000) {
			repeat_write("IN RANGE");
		}
		else {
			repeat_write("OUT OF RANGE");
		}
//
		//sprintf(text, "Value is: %d", ldr_getlux(ADCH));
		//repeat_write(text);
   }
   
   return 0;
}