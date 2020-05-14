/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned short x;
unsigned char tempB;
unsigned char tempD;

void ADC_init(){

	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

void tick(){


	tempB = 0x00;
	if(x >= 512)
		tempB = 0x80;
	if(x >= 448)
		tempB = 0x40;
	if(x >= 384)
		tempB = 0x20;
	if(x >= 320)
		tempB = 0x10;
	if(x >= 256)
		tempB = 0x08;
	if(x >= 192)
		tempB = 0x04;
	if(x >= 128)
		tempB = 0x02;
	if(x > 0)
		tempB = 0x01;
	PORTB = tempB;
	
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB =0x00;
	//DDRD = 0xFF; PORTD = 0x00;


	//unsigned short x = 0x38;

	ADC_init();


    /* Insert your solution below */
    while (1) {

	x = ADC;
	tick();
	
    }
    return 0;
}
