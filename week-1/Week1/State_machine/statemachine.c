/*
 * main.c
 *
 * Created: 2/9/2022 1:19:27 PM
 *  Author: doguk
 */ 

#include <xc.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum Menu_states { START, END, START, STATE_1, STATE_2, STATE_3};


int main(void)
{
	int bruh = Menu_states.START;
	
	DDRD = 0xFF;
	
	
    while(1)
    {
		
		switch (bruh){
			case Menu_states.STATE_1:
				
			break;
			
			case Menu_states.STATE_2:
			
			break;
			
			case Menu_states.STATE_3:
			
			break;
			
			case Menu_states.END:
			
			break;
			
			default :
				bruh = Menu_states.START;
			break;
		}
		
        //TODO:: Please write your application code 
    }
}