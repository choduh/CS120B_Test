/*	Author: magui070
 *  Partner(s) Name: 
 *	Lab Section:23
 *	Assignment: Lab #2  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

	unsigned char tempA = 0x00;
	unsigned char cntavail = 0x00;	
    /* Insert your solution below */
    while (1) {

	tempA = PINA;
	//spaces 0000 there are 4 spaces available
	if(tempA == 0x00){ 
		cntavail = 0x04;
	}
	//spaces of hex that 3 are 0 and 1 available
	if(tempA == 0x01 || tempA == 0x02 || tempA == 0x04 || tempA == 0x08){
		cntavail = 0x03;
	}
	//spaces of hex that have two  1's and 2 0s
	if(tempA == 0x03 || tempA == 0x05 || tempA == 0x06 || tempA == 0x09 || tempA == 0x0A ||
	 tempA == 0x0C){															   				cntavail = 0x02;
	}	 											   				
	//spaces of hex that have 3 1s and 1 0 0 meaning free space
	if(tempA == 0x07 || tempA ==  0x0B || tempA == 0x0D || tempA == 0x0E){				   									cntavail = 0x01;
	}
	//no spaces available all hex are 1s
	if(tempA == 0x0F){				   														cntavail = 0x00;
	}
	  PORTC = cntavail;											   						     }
	 return 0;
}
