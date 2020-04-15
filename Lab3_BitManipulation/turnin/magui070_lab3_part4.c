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
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;


    unsigned char topNIB = 0x00;
    unsigned char botNIB  = 0x00;
   
   
    /* Insert your solution below */
    while (1) {
	
	topNIB = PINA & 0xF0;
	botNIB = PINA & 0x0F;
	PORTB = topNIB >> 4;
	PORTC = botNIB << 4;
	

    }
    return 0;
}
