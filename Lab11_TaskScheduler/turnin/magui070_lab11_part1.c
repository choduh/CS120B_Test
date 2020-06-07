/*	Author: magui070
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #11  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "timer.h"
#include "keypad.h"
#include "scheduler.h"
#include "bit.h"
#include "simAVRHeader.h"
#endif



enum keySTATES {start} keypad_state;

int keypadTick(int keypad_state){

	unsigned char x = GetKeypadKey();
	switch(keypad_state){
		case start:
			keypad_state = start;
			break;
		default:
			keypad_state = start;
			break;
	}
	
	switch(x){
		case '\0':PORTA = 0x00; break;
		case '1': PORTA = 0x01; break;
		case '2': PORTA = 0x02; break;
		case '3': PORTA = 0x03; break;
		case 'A': PORTA = 0x0A; break;
		case '4': PORTA = 0x04; break;
		case '5': PORTA = 0x05; break;
		case '6': PORTA = 0x06; break;
		case 'B': PORTA = 0x0B; break;
		case '7': PORTA = 0x07; break;
		case '8': PORTA = 0x08; break;
		case '9': PORTA = 0x09; break;
		case 'C': PORTA = 0x0C; break;
		case '*': PORTA = 0x0E; break;
		case '0': PORTA = 0x00; break;
		case '#': PORTA = 0x0F; break;
		case 'D': PORTA = 0x0D; break;
		default: PORTA = 0x1B; break;
	}
	return keypad_state;
}

int main(void) {
    /* Insert DDR and PORT initializations */
	
	DDRA = 0xFF; PORTA = 0x00;
	DDRC = 0x00; PORTC = 0xFF;

	static task t1;
	task *tasks[] = {&t1};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	
	t1.state = start;
	t1.period = 50;
	t1.elapsedTime = t1.period;
	t1.TickFct = &keypadTick;

	TimerSet(50);
	TimerOn();
	
	unsigned short i;
	
	
    /* Insert your solution below */
    while (1) {


	for(i = 0; i<numTasks; i++){
		if(tasks[i]->elapsedTime == tasks[i]->period){
			tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
			tasks[i]->elapsedTime = 0;
		}
		tasks[i]->elapsedTime += 50;
	}
	
	keypadTick(start);
	while(!TimerFlag);
	TimerFlag = 0;
	
    }
    return 0;
}
