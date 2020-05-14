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


void ADC_init(){

	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;PORTA = 0xFF;
	DDRB = 0xFF; PORTB =0x00;
	DDRD = 0xFF; PORTD = 0x00;


	//unsigned short x = 0x38;

	ADC_init();

    /* Insert your solution below */
    while (1) {

	if(ADC >= (100/2)){
		PORTB = 0xFF;
		PORTD = 0x00;
	}
	else{
		PORTB = 0x00;
		PORTD = 0x00;	
	}
	
    }
    return 0;
}
