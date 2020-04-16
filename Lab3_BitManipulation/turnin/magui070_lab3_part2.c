/*	Author: magui070
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #3  Exercise #2
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
	if((tank == 0x01) || (tank == 0x02)){
		needle = needle | 0x60;
	}	
	else if((tank == 0x03) || (tank == 0x04)){
		needle = needle | 0x70;
	}
	else if((tank == 0x05) || (tank == 0x06)){
		needle = needle | 0x38;
	}
	else if((tank == 0x07) || (tank == 0x08) || (tank == 0x09)){
		needle = needle |0x3C;
	}
	else if((tank == 0x0A) || (tank == 0x0B) || (tank == 0x0C)){
		needle = needle | 0x3E;
	}
	else if((tank == 0x0D) || (tank == 0x0E) || (tank == 0x0F)){
		needle = needle | 0x3F;
	}
	PORTC = needle;


    }
    return 0;
}
