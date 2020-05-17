/*	Author: magui070
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #9  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


void set_PWM(double frequency){


	static double current_frequency;
	if(frequency != current_frequency){
		if(!frequency) {TCCR3B &= 0x08;}
		else{TCCR3B |= 0x03;}

		if(frequency < 0.954){OCR3A = 0xFFFF;}
		else if(frequency > 31250){OCR3A = 0x0000;}
		else{OCR3A = (short) (8000000 / (128 * frequency)) -1;}

		TCNT3 = 0;
		current_frequency = frequency;
	}
}

void PWM_on(){

	TCCR3A = (1 << COM3A0);
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
	set_PWM(0);
}

void PWM_off(){

	TCCR3A = 0x00;
	TCCR3B = 0x00;
}


enum Song{start, wait, C_4, D_4, E_4}button_state;

unsigned char b = 0x00;
static double C4 = 261.63;
static double D4 = 293.66;
static double E4 = 329.63;


void Song(){

	switch(button_state){
		case start:
			button_state = wait;
			break;
		case wait:
			if(b == 0x01){
				button_state = C_4;
			}
			else if(b == 0x02){
				button_state = D_4;
			}
			else if(b == 0x04){
				button_state = E_4;
			}
			else{
				button_state = wait;
			}
			break;
		case C_4:
			if(b == 0x01){
				button_state = C_4;
			}
			else{
				button_state = wait;
			}
			break;
		case D_4:
			if(b == 0x02){
				button_state = D_4;
			}
			else{
				button_state = wait;
			}
			break;
		case E_4:
			if(b == 0x04){
				button_state = E_4;
			}
			else{
				button_state = wait;
			}
			break;
		default:
			break;
	}
	
	switch(button_state){
		case start:
			break;
		case wait:
			set_PWM(0);
			break;
		case C_4:
			set_PWM(C4);
			break;
		case D_4:
			set_PWM(D4);
			break;
		case E_4:
			set_PWM(E4);
			break;
	}
			
}

int main(void) {
    /* Insert DDR and PORT initializations */
	
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
	

    PWM_on();
    button_state = start;
    /* Insert your solution below */
    while (1) {


	b = ~PINA & 0x07;
	Song();
    }
    return 1;
}
