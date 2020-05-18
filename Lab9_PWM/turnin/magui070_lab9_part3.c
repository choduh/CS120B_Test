/*	Author: magui070
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #9  Exercise #3
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




static double C4 = 261.63;
static double D4 = 293.66;
static double E4 = 329.63;
static double F4 = 349.23;
static double G4 = 392.00;
static double A4 = 440.00;
static double B4 = 493.88;
//static double C5 = 523.25;


// e g a g a a a d c b a b b d e a g f f e f g f g
enum Song{wait, hold, a, b, c, d, e, f, g}button_state;

char notes[24] = {e, g, a, g, a, a, a, d, c, b, a, b, b, d, e, a, g, f, f, e, f, g, f, g};

int ticks[24] = {40, 40, 40,15,20,20,20,15,20,15,20,15,15,15,15,15,15, 15, 15, 15, 15 ,15, 15,10};
static unsigned int counter = 0;
static unsigned char i;

//unsigned char b1 = 0x00;
void Song(){


	unsigned char b1 = ~PINA & 0x01;
	//unsigned char upScale = ~PINA & 0x02;
	//unsigned char downScale = ~PINA & 0x04;

	switch(button_state){
		case wait:
			if(b1){
				button_state = notes[counter];
			}
			else{
				button_state = wait;
			}
			break;
		case hold:
			if(i>= ticks[counter]){
				counter++;
				i = 0;
				button_state = notes[counter];
			}
			else{
				i++;
				button_state = hold;
			}
			break;
		case a:
			button_state = hold;
			break;
		case b:
			button_state = hold;
			break;
		case c:
			button_state = hold;
			break;
		case d:
			button_state = hold;
			break;
		case e:
			button_state = hold;
			break;
		case f:
			button_state = hold;
			break;
		case g:
			button_state = hold;
			break;
		default:
			button_state = wait;
			break;
	
	}
	
	switch(button_state){
		
		case wait:
			counter = 0;
			i = 0;
			set_PWM(0);
			break;
		case hold:
			break;
		case a:
			set_PWM(A4);
		 	break;
		case b:
			set_PWM(B4);
			break;
		case c:
			set_PWM(C4);
			break;
		case d:
			set_PWM(D4);
			break;
		case e:
			set_PWM(E4);
			break;
		case f:
			set_PWM(F4);
			break;
		case g:
			set_PWM(G4);
			break;
		default:
			set_PWM(0);
			break;
	}
			
}

int main(void) {
    /* Insert DDR and PORT initializations */
	
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
	
    TimerSet(10);
    TimerOn();
    PWM_on();
    
    /* Insert your solution below */
    while (1) {

	//b1 = ~PINA & 0x07;
	Song();
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}
