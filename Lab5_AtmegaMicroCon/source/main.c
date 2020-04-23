/*	Author: magui070
 *  Partner(s) Name: 
 *	Lab Section:023
 *	Assignment: Lab #5  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum button{START, init, seq1,seq2, wait}state;

unsigned char B1;


void LED_ON(){
	B1 = ~PINA & 0x01;
	
	

	switch (state){

		case START:
			PORTC = 0x00;
			state = seq1;
			break;
		case init:
			if(B1 == 0x01){
				state = seq1;
			}
			else if(B1 == 0x02){
				state = seq2;
			}
			else{
				state = init;	
			}
			break;
		case seq1:
			state = wait;	
			break;
		case seq2:
			state = init;
			break;
		case wait:
			if(B1 == 0x01){
				state = wait;
			}
			else if(B1 == 0x02){

				state = wait;
			}
			else if(B1 == 0x00){
				state = init;
			}			

			break;
		default:
			break;
		
	}
	switch(state){
		case START:
			break;
		case init:
			break;
		case seq1:
			if(PORTC == 0x00){
				PORTC = (PORTC << 1);
			}
			else{
				PORTC = 0x01;
			}
			if(PORTC == 0x04){
				PORTC = 0x38;
			}
			break;
		case seq2:
			
			break;
		case wait:
			break;
		default:
			break;
			
	}
	

}

int main(void) {
    /* Insert DDR and PORT initializations */
	
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */

   
    state = START;
 
  
    while (1) {
	LED_ON();	
    }
    return 1;
}
