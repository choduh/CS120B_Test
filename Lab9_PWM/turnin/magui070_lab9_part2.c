/*	Author: magui070
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #9  Exercise #2
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


enum Song{start, C_4, D_4, E_4, F_4, G_4, A_4, B_4, C_5}button_state;

static double C4 = 261.63;
static double D4 = 293.66;
static double E4 = 329.63;
static double F4 = 349.23;
static double G4 = 392.00;
static double A4 = 440.00;
static double B4 = 493.88;
static double C5 = 523.25;

unsigned char b1 = 0x00;
void Song(){


	//unsigned char b1 = 0x00;
	//unsigned char upScale = ~PINA & 0x02;
	//unsigned char downScale = ~PINA & 0x04;

	switch(button_state){
		case start:
			if(b1 == 0x01){
				button_state = C_4;
			}
			else {
				button_state = start;
			}
			break;
		case C_4:
			if(b1 == 0x02){
				button_state = D_4;
			}
			else if(b1 == 0x01){
				button_state = start;
			}
			else{
				button_state = C_4;
			}
			break;
		case D_4:
			if(b1 == 0x02){
				button_state = E_4;
			}
			else if(b1 == 0x04){
				button_state = C_4;
			}
			else if(b1 == 0x01){
				button_state = start;
			}
			else{
				button_state = D_4;
			}
			break;
		case E_4:
			if(b1 == 0x02){
				button_state = F_4;
			}
			else if(b1 == 0x04){
				button_state = D_4;
			}
			else if(b1 == 0x01){
				button_state = start;
			}
			else{
				button_state = E_4;
			}
			break;

		case F_4:
			if(b1 == 0x02){
				button_state = G_4;
			}
			else if(b1 == 0x04){
				button_state = E_4;
			}
			else if(b1 == 0x01){
				button_state = start;
			}
			else{
				button_state = F_4;
			}
			break;
		case G_4:
			if(b1 == 0x02){
				button_state = A_4;
			}
			else if(b1 == 0x04){
				button_state = F_4;
			}
			else if(b1 == 0x01){
				button_state = start;
			}
			else{
				button_state = G_4;
			}
			break;

		case A_4:
			if(b1 == 0x02){
				button_state = B_4;
			}
			else if(b1 == 0x04){
				button_state = G_4;
			}
			else if(b1 == 0x01){
				button_state = start;
			}
			else{
				button_state = A_4;
			}
			break;
		case B_4:
			if(b1 == 0x02){
				button_state = C_5;
			}
			else if(b1 == 0x04){
				button_state = A_4;
			}
			else if(b1 == 0x01){
				button_state = start;
			}
			else{
				button_state = B_4;
			}
			break;
		case C_5:
			if(b1 == 0x04){
				button_state = B_4;
			}
			else if(b1 == 0x01){
				button_state = start;
			}
			else{
				button_state = C_5;
			}	
			break;
		default:
			button_state = start;
			break;
	}
	
	switch(button_state){
		
		case start:
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
		case F_4:
			set_PWM(F4);
			break;
		case G_4:
			set_PWM(G4);
			break;
		case A_4:
			set_PWM(A4);
			break;
		case B_4:
			set_PWM(B4);
			break;
		case C_5:
			set_PWM(C5);
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
	
    TimerSet(500);
    TimerOn();
    PWM_on();
    button_state = start;
    /* Insert your solution below */
    while (1) {

	b1 = ~PINA & 0x07;
	Song();
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}
