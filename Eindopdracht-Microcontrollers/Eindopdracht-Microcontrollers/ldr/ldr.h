/*
 * ldr.h
 * Created: 4/5/2022 3:15:52 PM
 *  Author: doguk
 */ 


#ifndef LDR_H_
#define LDR_H_

#include "C:\Users\doguk\Documents\GithubRepos\Microcontrollers\Eindopdracht-Microcontrollers\Eindopdracht-Microcontrollers\lcd\lcd.h"

#define LDR_A 9000
#define LDR_B 165
#define LDR_C -1.65

#define TIMER_TRIGGER_VAL 195 // Amount of ticks needed to trigger interrupt, used by comparator

#define LDR_LOW 6200 // Laser shines on LDR, big integer will be changed

typedef enum {TRIGGERED, ACTIVE} ldr_state;
	
void start_timer();
void stop_timer();

void init_ldr(void);
uint16_t ldr_getlux(long adcresistance); // Converts incoming value, represented as 16-bit int value

#endif /* LDR_H_ */