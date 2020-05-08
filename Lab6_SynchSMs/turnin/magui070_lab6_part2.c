/*	Author: magui070
 *  Partner(s) Name: 
 *	Lab Section:23
 *	Assignment: Lab #6  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <timer.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum LED{START, wait, reset, B0, B1, B2} led_state;

unsigned char nextS = 0x00;
void Tick(unsigned char tempA){


	switch(led_state){
		case START:
			led_state = B0;
			break;
		case B0:
			if(~(PINA & 0x01) == 0x01){
				led_state = wait;
			}
			else{
				led_state = B1;
				nextS = B2;	
			}
			break;
		case B1:
			if((~PINA & 0x01) ==0x01){
				led_state = wait;
			}
			else{
				led_state = nextS;
			}
			break;
		case B2:
			if((~PINA & 0x01) == 0x01){
				led_state = wait;
			}
			else{
				nextS = B0;
				led_state = B1;
			}
			break;
		case wait:
			if((~PINA & 0x01) == 0x01){
				led_state = reset;
			}
			else{
				led_state = wait;
			}
			break;
		case reset:
			if((PINA & 0x01) == 0x01){

				led_state = B0;
			}
			else{

				led_state = reset;
			}
			break;

		default:
			led_state = START;
			break;
	}
	switch(led_state){

		case START:
			break;
		case B0:
			PORTC = 0x01;
			break;
		case B1:
			PORTC = 0x02;
			break;
		case B2:
			PORTC = 0x04;
			break;
		case wait:
			break;
		case reset:
			break;
		default:
			PORTC = 0x01;
			break;
	}
			

			
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    TimerSet(150);
    TimerOn();
    unsigned char tempA = 0x00;
    //unsigned char button = 0x00;
   
    led_state = START;
    /* Insert your solution below */
    while (1) {
	tempA = ~(PINA & 0x01);
	
	Tick(tempA);
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 0;
}
