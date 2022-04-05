#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "adc/adc.h"

#include "ldr/ldr.h"

#define UART_BAUD_RATE 2400
#include "uart/uart.h"

static uint16_t adc = 0;

int main(void) {
	char printbuff[100];
	long l;

	//init uart
	uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) );

	//init adc
	adc_setchannel(1);
	adc_init();

	//init interrupt
	sei();

	for (;;)
	{
		//print out results
		adc = adc_read(0);

		if(adc == 0)
			adc = 1;
		long adcres = adc_getresistence(adc, 3300);

		itoa(adc, printbuff, 10);
		uart_puts("ADC     "); uart_puts(printbuff); uart_puts("\r\n");

		l = adcres;
		ltoa(l, printbuff, 10);
		uart_puts("RES     "); uart_puts(printbuff); uart_puts("\r\n");

		l = ldr_getlux(adcres);
		ltoa(l, printbuff, 10);
		uart_puts("Lux     "); uart_puts(printbuff); uart_puts("\r\n");

		uart_puts("\r\n");

		_delay_ms(1500);
	}
	
	return 0;
}
