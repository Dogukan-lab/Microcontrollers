/*
 * buzzer.c
 *
 * Created: 4/6/2022 12:50:05 PM
 *  Author: doguk
 */ 

/*
	Music demo.
	Microcontroller: ATmega16 or ATmega32
	Clock: 8 MHz
	External hardware: Piezzo buzzer/speaker connected to PD4/OCR1B (PDIP pin 18)
	Compiler: AVR GCC
	http://aquaticus.info/pwm-music
	$Revision: 142 $
*/

#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

// The output file from notegen.pl script
#include "notes.h"

/// Default volume, value assigned to OCR1B
#define DEFAULT_VOLUME 100

// Octave
melody octave = {c4, 8}, {d4, 8}, {e4, 8}, {f4, 8}, {g4, 8}, {a4, 8}, {h4, 8}, {c5, 8}, {MUSIC_END, 0};
	
// Star Wars
melody starwars = 
	{Ais2,8}, {Ais2,8},{ P,16}, {F3,8}, {F3,8}, {P,16}, {Dis3,16}, {P,16}, {D3,16}, {P,16}, {C3,16}, {P,16}, {Ais3,8},
	{Ais3,8}, {P,16}, {F3,8}, {P,16}, {Dis3,16}, {P,16}, {D3,16}, {P,16}, {C3,16}, {P,16}, {Ais3,8}, {Ais3,8}, {P,16},
	{F3,8}, {P,16}, {Dis3,16}, {P,16}, {D3,16}, {P,16}, {Dis3,16}, {P,16}, {C3,8}, {C3,8}, 
	{MUSIC_END, 0};

// Fur Elise
melody furelise = 
    {e4, 8}, {d4x, 8}, {e4, 8}, {d4x, 8}, {e4, 8}, {b3, 8}, {d4, 8}, {c4, 8}, {a3,8}, {p, 8},
    {c3, 8}, {e3, 8}, {a3, 8},  {b3, 4}, {p, 8}, {e3, 8}, {g3x, 8}, {b3, 8}, {c4, 4}, {p, 8}, {e3, 8},
    {e3, 8}, {d4x, 8}, {e4, 8}, {d4x, 8}, {e4, 8}, {b3, 8}, {d4, 8}, {c4, 8}, {a3, 8}, {p, 8}, {c3, 8},
    {e3, 8}, {a3, 8}, {b3, 4}, {p, 8}, {e3, 8}, {c4, 8}, {b3, 8}, {a3, 4},
    {MUSIC_END, 0};

// Beatles, Hey Jude
melody Jude = 
	{G2,8}, {E2,8}, {P,16}, {E2,16}, {E2,16}, {G2,16}, {A2,16}, {D2,8}, {P,16}, {D2,16}, {E2,16}, {F2,8}, 
	{C3,8}, {C3,16}, {C3,16}, {H2,16}, {G2,16}, {A2,16}, {G2,16}, {F2,16}, {E2,8}, {P,16}, {G2,16}, 
	{A2,16}, {A2,8}, {A2,16}, {D3,16}, {C3,16}, {H2,16}, {H2,16}, {C3,16}, {A2,16}, {G2,8}, {P,16}, 
	{C2,16}, {D2,16}, {E2,16}, {A2,16}, {A2,16}, {G2,8},
	{MUSIC_END, 0};

/**
	Initialize timer1
	PWM output on OCR1B
*/
void InitMusic()
{
	// Configure OC1B pin as output

	DDRB = 0xF0; //OC1B as output

	// timer1 configuration (for PWM) 

	TCCR1A |= 0b10100000; // Clear OC1A/OC1B on compare match
	TCCR1B |= 0b00010010; //mode 8, PWM, Phase and Frequency Correct (TOP value is ICR1)
						 //prescaler(8)
}

/*
 * Plays music.
 */
void PlayMusic( struct pMusicNotes /** Pointer to table containing music data */,
				uint8_t tempo /** paying tempo from 0 to 100. Higher value = slower playback*/ )
{
	int i;
	int j;
	uint16_t delay = tempo * 1000;

	while(*pMusicNotes)
	{
		if( p == *pMusicNotes.note[j] )
		{
			//pause, do not generate any sound
			OCR1B = 0;
		}
		else
		{
			//not a pause, generate tone
			OCR1B = DEFAULT_VOLUME;

			//set frequency
			ICR1H = (*pMusicNotes.note[j] >> 8);
			ICR1L = *pMusicNotes.note[j];
		}

		//wait duration
		for(i=0 ; i<32-*pMusicNotes.duration[j] ; i++)
		{
			_delay_loop_2(delay);
		}
		
		j++;
	}
	

	//turn off any sound
	OCR1B = 0;
}

void start_music()
{
	InitMusic();

	while(1)
	{	
		PlayMusic(octave, 40);
		_delay_ms(1000);
	}

}