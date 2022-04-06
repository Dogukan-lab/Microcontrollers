/*
 * buzzer.c
 *
 * Created: 4/6/2022 12:50:05 PM
 *  Author: Sebastiaan
 */ 
#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>
#include "notes.h"

#define DEFAULT_VOLUME 100		// Default volume, value assigned to OCR1B 
#define OCTAVE_ARR_SIZE 9
#define MAX_WAIT_DURATION 32

// Octave
MELODY octave[] = {{c4, 2}, {d4, 2}, {e4, 2}, {f4, 2}, {g4, 2}, {a4, 2}, {h4, 2}, {c5, 2}, {c4, MUSIC_END}};
	

MELODY star_wars[] = 
	{{Ais2,8}, {Ais2,8},{ P,16}, {F3,8}, {F3,8}, {P,16}, {Dis3,16}, {P,16}, {D3,16}, {P,16}, {C3,16}, {P,16}, {Ais3,8},
	{Ais3,8}, {P,16}, {F3,8}, {P,16}, {Dis3,16}, {P,16}, {D3,16}, {P,16}, {C3,16}, {P,16}, {Ais3,8}, {Ais3,8}, {P,16},
	{F3,8}, {P,16}, {Dis3,16}, {P,16}, {D3,16}, {P,16}, {Dis3,16}, {P,16}, {C3,8}, {C3,8}, 
	{MUSIC_END, 0}};


MELODY fur_elise[] = 
    {{e4, 8}, {d4x, 8}, {e4, 8}, {d4x, 8}, {e4, 8}, {b3, 8}, {d4, 8}, {c4, 8}, {a3,8}, {p, 8},
    {c3, 8}, {e3, 8}, {a3, 8},  {b3, 4}, {p, 8}, {e3, 8}, {g3x, 8}, {b3, 8}, {c4, 4}, {p, 8}, {e3, 8},
    {e3, 8}, {d4x, 8}, {e4, 8}, {d4x, 8}, {e4, 8}, {b3, 8}, {d4, 8}, {c4, 8}, {a3, 8}, {p, 8}, {c3, 8},
    {e3, 8}, {a3, 8}, {b3, 4}, {p, 8}, {e3, 8}, {c4, 8}, {b3, 8}, {a3, 4},
    {MUSIC_END, 0}};


MELODY jude[] = 
	{{G2,8}, {E2,8}, {P,16}, {E2,16}, {E2,16}, {G2,16}, {A2,16}, {D2,8}, {P,16}, {D2,16}, {E2,16}, {F2,8}, 
	{C3,8}, {C3,16}, {C3,16}, {H2,16}, {G2,16}, {A2,16}, {G2,16}, {F2,16}, {E2,8}, {P,16}, {G2,16}, 
	{A2,16}, {A2,8}, {A2,16}, {D3,16}, {C3,16}, {H2,16}, {H2,16}, {C3,16}, {A2,16}, {G2,8}, {P,16}, 
	{C2,16}, {D2,16}, {E2,16}, {A2,16}, {A2,16}, {G2,8},
	{MUSIC_END, 0}};

/*
 * Initialize timer1
 * PWM output on OCR1B
 */
void init_music()
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
 * Struct array containing music data 
 * Playing tempo from 0 to 100. Higher value = slower playback 
 */
void play_music(MELODY music_notes[], uint8_t tempo ) {
	int index = 0;
	uint16_t delay = tempo * 1000;
	
	while(index < OCTAVE_ARR_SIZE)
	{
		if(p == music_notes[index].note)
		{
			//pause, do not generate any sound
			OCR1B = 0;
		}
		else
		{
			//not a pause, generate tone
			OCR1B = DEFAULT_VOLUME;

			//set frequency
			ICR1H = (music_notes[index].note >> 8);
			ICR1L = music_notes[index].note;
		}

		//wait duration
		for(int i = 0 ; i < MAX_WAIT_DURATION - music_notes[index].duration; i++)
		{
			_delay_loop_2(delay);
		}
		
		index++;
	}
	

	//turn off any sound
	OCR1B = 0;
}

void start_music()
{
	init_music();
	_delay_ms(10);
	
	play_music(octave, 80);
	_delay_ms(1000);	

}