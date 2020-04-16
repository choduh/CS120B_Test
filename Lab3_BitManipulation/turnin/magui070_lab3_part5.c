/*	Author: magui070
 *  Partner(s) Name: 
 *	Lab Section: 023
 *	Assignment: Lab #3  Exercise #5
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
	

    DDRD = 0xFE; PORTD = 0x01;
    DDRD = 0x00; PORTD = 0xFF;
   


    unsigned char tempB = 0x00;
    unsigned char tempD  = 0x00;
    unsigned char weight;
    unsigned char out;
   
   
    /* Insert your solution below */
    while (1) {
	weight = 0x00;
	out = 0x00;
	tempB = PINB & 0x01;
	tempD = PIND & 0xFF;
	weight = weight + tempB;
	weight = (2*tempD) + weight;
	
	
	if(weight >= 70){
		out = 0x02;
	}
	else{
		out = 0x04;
	}
	PORTB = out;

    }
    return 0;
}
