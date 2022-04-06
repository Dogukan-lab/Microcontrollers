/*
 * command_center.h
 *
 * Created: 4/5/2022 5:42:47 PM
 *  Author: doguk
 */ 


#ifndef COMMAND_CENTER_H_
#define COMMAND_CENTER_H_

typedef enum {
	STARTUP,				// Startup of program
	LASER_DETECTION_ON,		// Turn on laser detection
	LASER_DETECTION_OFF,	// Turn off laser detection
	BUZZER_ON,				// Turn buzzer on
	BUZZER_OFF,				// Turn buzzer off
	} PROGRAM_STATE;		// States of program

void check_program_state(PROGRAM_STATE state);
void welcome_customer();

#endif /* COMMAND_CENTER_H_ */