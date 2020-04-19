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

enum lock_state{start, pound, Y, locked, unlocked, doorlock}state;



unsigned char Lock(unsigned char lockbuttons){

	lockbuttons = PINA & 0x87;
	
	switch(state){

		case start:
			state = locked;
			break;
		case pound:
			if(lockbuttons == 0x02){
				state = Y;
			}
			else{
				locked;
			}
			break;
		case Y:
			if(lockbuttons == 0x80){
				state = locked;
			}
			else if(lockbuttons == 0x01){
				state = unlocked;
			}
			else{
				Y;
			}
			break;
		case locked:
			if(lockbuttons == 0x04){
				state = pound;
			}
			else{
				locked;
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
		default:
			state = locked;
			break;
	}
	switch(state){
		case unlocked:
			PORTB = 0x01;
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
   
    while (1) {
	Lock(lockbuttons);	
    }
   
}
