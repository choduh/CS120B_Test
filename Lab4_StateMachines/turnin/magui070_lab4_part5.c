/*	Author: magui070
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #4  Exercise #4
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum lock_state{start, locked, unlocked, doorlock, correct, incorrect }state;

unsigned char isCorrect(unsigned char pos){

	unsigned char butSeq[3] = {0x01, 0x02, 0x01};
	if(butSeq[pos -1] == PINA){
		return 0x01;	
	}
	return 0x00;
}

unsigned char Unlock(unsigned char lockbuttons, unsigned char pos){


	lockbuttons = PINA & 0x87;
	
	switch(state){

		case start:
			state = locked;
			break;
		case unlocked:
			if(lockbuttons == 0x04){
	

				state = doorlock;
			}
			else if(lockbuttons == 0x80){
				state = locked;
			}
			else{
				state = locked;
			}
			break;
		case locked:
			if((lockbuttons == 0x04 && pos !=3) || (lockbuttons == 0x02 && pos !=3) 
			    || (lockbuttons == 0x01 && pos !=30)){
				state = locked;
			}
			else if(isCorrect(pos) && pos == 3){
				state = correct;
			}
			break;
		case doorlock:
			if(lockbuttons == 0x80){
				state = locked;
			}
			else if(lockbuttons == 0x02){
				state = locked;
			}
			else{		
				unlocked;
			}

		case correct:
			if(lockbuttons == 0x00){
				state = unlocked;
			}
			else{
				unlocked;
			}
			break;
		case incorrect:
			if(lockbuttons == 0x04){
				state = locked;	
			}
			else{
				state = unlocked;
			}
			break;

		default:
			state = locked;
			break;
	}
	switch(state){
		case unlocked:
			PORTB = 0x01;
			pos = 0;
			break;
		default:
			PORTB = 0x00;
			break;
	
	}

}

int main(void) {
    /* Insert DDR and PORT initializations */
	
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */

   
    unsigned char lockbuttons = 0x00;
    unsigned char pos = 0x00;
   
    while (1) {
	Unlock(lockbuttons, pos);
	pos++;	
    }
   
}
