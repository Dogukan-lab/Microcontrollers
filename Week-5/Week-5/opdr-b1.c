/*
 * Project name		: Demo5_5 : spi - 7 segments display
 * Author			: Avans-TI, WvdE, JW
 * Revision History	: 20110228: - initial release;
 * Description		: This program sends data to 1 4-digit display with spi
 * Test configuration:
     MCU:             ATmega128
     Dev.Board:       BIGAVR6
     Oscillator:      External Clock @ 08.0000 MHz
     Ext. Modules:    Serial 7-seg display
     SW:              AVR-GCC
 * NOTES			: Turn ON switch 15, PB1/PB2/PB3 to MISO/MOSI/SCK
 * Edited by		: Sebastiaan Tromper and Dogukan Akyazi
*/

#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>

#define BIT(x)		( 1 << x )
#define DDR_SPI		DDRB					// spi Data direction register
#define PORT_SPI	PORTB					// spi Output register
#define SPI_SCK		1						// PB1: spi Pin System Clock
#define SPI_MOSI	2						// PB2: spi Pin MOSI
#define SPI_MISO	3						// PB3: spi Pin MISO
#define SPI_SS		0						// PB0: spi Pin Slave Select

// wait(): busy waiting for 'ms' millisecond
// used library: util/delay.h
void wait(int ms)
{
	for (int i=0; i<ms; i++)
		{
			_delay_ms(1);
		}
}

// Writes commands to 7 segment display with data after
// Starts and cleans itself up for communication reasons
void spi_write_word(unsigned char adress, unsigned char data) {
	spi_slaveSelect(SPI_SS);				// Select display chip
	spi_write(adress); 				// Set Register
	spi_write(data); 				// Set data to send
	spi_slaveDeSelect(SPI_SS);			// End communication
}

// Inits the spi MOSI communication
void spi_masterInit(void)
{
	DDR_SPI = 0xff;							// All pins output: MOSI, SCK, SS, SS_display as output
	DDR_SPI &= ~BIT(SPI_MISO);				// 	except: MISO input
	PORT_SPI |= BIT(SPI_SS);				// SS_ADC == 1: deselect slave
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR1);	// or: SPCR = 0b11010010;
											// Enable spi, MasterMode, Clock rate fck/64, bitrate=125kHz
											// Mode = 0: CPOL=0, CPPH=0;
}


// Write a byte from master to slave
void spi_write( unsigned char data )				
{
	SPDR = data;							// Load byte to Data register --> starts transmission
	while( !(SPSR & BIT(SPIF)) ); 			// Wait for transmission complete 
}

//// Write a byte from master to slave and read a byte from slave
//// nice to have; not used here
//char spi_writeRead( unsigned char data )
//{
	//SPDR = data;							// Load byte to Data register --> starts transmission
	//while( !(SPSR & BIT(SPIF)) ); 			// Wait for transmission complete 
	//data = SPDR;							// New received data (eventually, MISO) in SPDR
	//return data;							// Return received byte
//}


// Select device on pin number PORTB
void spi_slaveSelect(unsigned char chipNumber)
{
	PORTB &= ~BIT(chipNumber);
}

// De-select device on pin number PORTB
void spi_slaveDeSelect(unsigned char chipNumber)
{
	PORTB |= BIT(chipNumber);
}


// Initialize the driver chip (type MAX 7219)
void displayDriverInit() 
{
	spi_write_word(0x09, 0xFF);		// Sets current 7 seg to decode mode

	spi_write_word(0x0A, 0x04);		// Sets intensity for LED's
	
	spi_write_word(0x0B, 0x03);		// Sets scan limit

	spi_write_word(0x0C, 0x01);		// Sets shutdown register
}

// Set display on ('normal operation')
void displayOn() 
{
	spi_write_word(0x0C, 0x01);		// Turns display on
}

// Set display off ('shut down')
void displayOff() 
{
	spi_write_word(0x0C, 0x00);		// Shuts display down
}

int main()
{
	
	DDRB=0x01;					  	// Set PB0 pin as output for display select
	spi_masterInit();              	// Initialize spi module
	displayDriverInit();            // Initialize display chip

 	// clear display
	for (char i = 1; i <= 4; i++)
	{
		spi_write_word(i, 0);
	}    
	wait(1000);

	// write 4-digit data  
 	for (char i = 1; i <= 4; i++)
  	{
		spi_write_word(i, i);
		wait(1000);
  	}

  	return (1);
}