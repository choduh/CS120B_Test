/*	Author: magui070
 *  Partner(s) Name: 
 *	Lab Section:23
 *	Assignment: Lab #2  Exercise #4 Challenge
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
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0x00; PORTC = 0xFF;
	DDRD = 0xFF; PORTD = 0x00;

	unsigned char tempA = 0x00;
	unsigned char tempB = 0x00;
	unsigned char tempC = 0x00;
	unsigned char passWeight  = 0x00;
		
    /* Insert your solution below */
    while (1) {
	
	PORTD = 0x00;
	tempA = PINA;
	tempB = PINB;
	tempC = PINC;
	
	passWeight = tempA + tempB + tempC;
	PORTD = passWeight >> 2;
	PORTD = PORTD << 2;
	if(passWeight > 140){
		PORTD = PORTD | 0x01; //car exceeding 140kg is stored in tempD
	}
	if((tempA - tempB) > 80){
		PORTD = PORTD | 0x02; // difference of car A and C exceeding 80 stored in tempD
	}
	
	
    }
	
	
	return 0;
}
