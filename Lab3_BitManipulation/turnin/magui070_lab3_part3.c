/*	Author: magui070
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #3  Exercise #3
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
   // DDRB = 0x00; PORTB = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;


    unsigned char tank = 0x00;
    unsigned char needle  = 0x00;
   
   
    /* Insert your solution below */
    while (1) {

	
	tank = PINA & 0x0F;
	if(tank > 12){
		needle = 0x3F;
	}
	else if ( tank > 9){
		needle = 0x3E;
	}
	else if(tank > 6){
		needle = 0x3C;
	}
	else if(tank > 4){
		needle = 0x34;
	}
	else if(tank > 2){
		needle = 0x70;
	}
	else if(tank >=0){
		needle = 0x60;
	}

	else{
		needle = 0x40;
	}
	if((tank & 0x30) == 0x30){
		needle = 0x80;
	}
	PORTC = needle;

    }
    return 0;
}
