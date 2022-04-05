/*
ADC Library 0x03

copyright (c) Davide Gironi, 2012

Released under GPLv3.
Please refer to LICENSE file for licensing information.
*/


#include <avr/io.h>
#include <avr/interrupt.h>

#if defined (__AVR_ATtiny13A__)
#elif defined (__AVR_ATmega8__)
#elif defined (__AVR_ATmega168__) || defined (__AVR_ATmega168P__)
#elif defined (__AVR_ATmega328__) || defined (__AVR_ATmega328P__)
#else
	#error "no defintions available for this AVR"
#endif

#include "adc.h"

//complete this if trigger is on
//call adc_setchannel()
//call sei()
//ISR(ADC_vect) 
//{
//}

/*
 * set an adc channel
 */
void adc_setchannel(uint8_t channel)
{
	#if defined (__AVR_ATtiny13A__)
		ADMUX &= 0b11111100; //clean channel
		channel = channel & 0b00000011;
	#elif defined (__AVR_ATmega8__) || defined (__AVR_ATmega168__) || defined (__AVR_ATmega168P__) || defined (__AVR_ATmega328__) || defined (__AVR_ATmega328P__)
		ADMUX &= 0b11111000; //clean channel
		channel = channel & 0b00000111;
	#endif
	ADCSRA &= ~(1 << ADEN);
	ADMUX = channel; //set channel
	ADCSRA |= (1 << ADEN);
}

/*
 * read from adc channel
 */
uint16_t adc_read(uint8_t channel) 
{
	adc_setchannel(channel);
	ADCSRA |= (1 << ADSC); // Start conversion
	while( !(ADCSRA & (1<<ADIF)) ); // Wait for conversion to complete 
	uint16_t adc = ADC;
	ADCSRA |= (1 << ADIF); // Clear ADIF by writing one to it
	return(adc);
}

/*
 * init adc
 */
void adc_init() 
{
	// Set ADC reference
	#if defined (__AVR_ATtiny13A__)
		switch(_ADCREF_)
		{
			case 0:
				ADMUX |= (0 << REFS0); // VCC used as analog reference
				break;
			case 1:
				ADMUX |= (1 << REFS0); // Internal Voltage Reference
				break;
		}
	#elif defined (__AVR_ATmega8__) || defined (__AVR_ATmega168__) || defined (__AVR_ATmega168P__) || defined (__AVR_ATmega328__) || defined (__AVR_ATmega328P__)
		switch(ADC_REF)
		{
			case 0:
				ADMUX |= (0 << REFS1) | (0 << REFS0); // AREF, Internal Vref turned off
				break;
			case 1:
				ADMUX |= (0 << REFS1) | (1 << REFS0); // AVCC with external capacitor at AREF pin
				break;
			case 3:
				ADMUX |= (1 << REFS1) | (1 << REFS0); // Internal 2.56V Voltage Reference with external cap at AREF
				break;
		}
	#endif
	
	// Set ADC prescaler
	switch(ADC_PRESCALER)
	{
		case 2:
			ADCSRA |= (0 << ADPS2) | (0 << ADPS1) | (1 << ADPS0); // Prescaler 2
			break;
		case 4:
			ADCSRA |= (0 << ADPS2) | (1 << ADPS1) | (0 << ADPS0); // Prescaler 4
			break;
		case 8:
			ADCSRA |= (0 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Prescaler 8
			break;
		case 16:
			ADCSRA |= (1 << ADPS2) | (0 << ADPS1) | (0 << ADPS0); // Prescaler 16
			break;
		case 32:
			ADCSRA |= (1 << ADPS2) | (0 << ADPS1) | (1 << ADPS0); // Prescaler 32
			break;
		case 64:
			ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (0 << ADPS0); // Prescaler 64
			break;
		case 128:
			ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Prescaler 128
			break;
	}
	
	// Set ADC justify
	if(ADC_JUSTIFY == 'L')
		ADMUX |= (1 << ADLAR); // Left adjust ADC result to allow easy 8 bit reading
	else if(ADC_JUSTIFY == 'R')
		ADMUX |= (0 << ADLAR); // Right adjust
	
	// Set ADC trigger and mode
	if(ADC_TRIGGERON)
	{
		#if defined (__AVR_ATtiny13A__) || defined (__AVR_ATmega168__) || defined (__AVR_ATmega168P__) || defined (__AVR_ATmega328__) || defined (__AVR_ATmega328P__)
			ADCSRB |= (0 << ADTS2) | (0 << ADPS1) | (0 << ADPS0); // Free Running mode
			ADCSRA |= (1 << ADATE); // Enable ADC Interrupt
		#elif defined (__AVR_ATmega8__)
			ADCSRA |= (1 << ADFR); // Set ADC to Free-Running Mode
		#endif
		ADCSRA |= (1 << ADIE); // Enable ADC Interrupt 
	}
	
	// Enable ADC
	ADCSRA |= (1 << ADEN);

	if(ADC_TRIGGERON)
	{
		ADCSRA |= (1 << ADSC); // Start conversions
	}

}

/*
 * convert an adc value to a resistence value
 */
long adc_getresistence(uint16_t adcread, uint16_t adcbalanceresistor)
{
	if(adcread == 0)
		return -1;
	else
		return (long)((long)(ADC_REFRES*(long)adcbalanceresistor)/adcread-(long)adcbalanceresistor);
}

/*
 * exponential moving avarage filter
 *
 * "newvalue" new adc read value
 * "value" old adc filtered value
 * return a new filtered value
 *
 * References:
 *   Guillem Planissi: Measurement and filtering of temperatures with NTC
 */
#define ADC_EMAFILTERALPHA 30
unsigned int adc_emafilter(unsigned int newvalue, unsigned int value)
{
	//use exponential moving avarate Y=(1-alpha)*Y + alpha*Ynew, alpha between 1 and 0
	//in uM we use int math, so Y=(63-63alpha)*Y + 63alpha*Ynew  and  Y=Y/63 (Y=Y>>6)
	value = (64-ADC_EMAFILTERALPHA)*value+ADC_EMAFILTERALPHA*newvalue;
	value = (value>>6);
	return value;
}

