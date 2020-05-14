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

	unsigned char b_8 = 0x00;
	unsigned char d_2 = 0x00;
	unsigned short x = ADC;

	ADC_init();
    /* Insert your solution below */
    while (1) {
	x = ADC;
	b_8 = (char)x;
	d_2 = (char)(x >> 8);
	PORTB = b_8;
	PORTD = d_2;
    }
    return 0;
}
