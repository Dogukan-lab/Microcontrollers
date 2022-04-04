/*
ADC Library 0x03

copyright (c) Davide Gironi, 2012

Released under GPLv3.
Please refer to LICENSE file for licensing information.
*/


#ifndef ADC_H
#define ADC_H

//setup values
#define ADC_REF 0 //adc reference voltage (see adc_init function for reference)
#define ADC_PRESCALER 4 //adc prescaler (2, 4, 8, 16, 32, 64, 128)
#define ADC_JUSTIFY 'R' //adc justify ('L' or 'R')
#define ADC_TRIGGERON 0 //adc trigger (1 on - 0 off)
#define ADC_REFV 5 //reference voltage
#define ADC_REFRES 1024 //reference resolution used for conversions

/*
 * convert an adc value to a voltage value
 */
#define adc_getvoltage(adcread,adcvref) (double)((double)adcread*adcvref/ADC_REFRES)

//functions
extern void adc_setchannel(uint8_t channel);
extern uint16_t adc_read(uint8_t channel);
extern void adc_init();
extern long adc_getresistence(uint16_t adcread, uint16_t adcbalanceresistor);
extern unsigned int adc_emafilter(unsigned int newvalue, unsigned int value);

#endif
