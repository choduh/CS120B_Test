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

enum button{init, increase, decrease, reset, wait1, wait2, wait}state;

unsigned char B1;
unsigned char B2;
unsigned char tempC;


void LED_ON(){
	B1 = ~PINA & 0x01;
	B2 = ~PINA & 0x02;
	//unsigned char tempC = 0x07;

	switch (state){

		case init:
			if(B1){
				state = wait1;
			}
			else if(B2){
				state = wait2;
			}
			else{
				state = init;
			}
			
			break;
		case increase:
			state = init;
			break;
		case wait1:
			if(B1 && B2)
			{
				state = reset;	
			}
			else if(B1){
				if(B1){
					while(!TimerFlag && B1){
					state = increase;
				};
				}
				else{
					state = wait1;
					TimerOn();
				}
			}
			else{
				state = increase;	
			}
			break;

		case decrease:
			state = init;
			break;
		case wait2:
			if(B1 && B2){
				state = reset;
			}
			else if(B2){
				if(B2){
					while(!TimerFlag && B2){
						state = decrease;
					};
				}
				else{
				 	state = wait2;
					TimerOn();
				}
			
			}
			else{
				state = decrease;
			}
			break;
		case reset:
			if(B1 || B2){
				state = reset;
			}
			else{
				state = init;
			}
			break;
		default:
			state = init;
			break;
	}
	switch(state){
		case init:
			break;
		case increase:
			if(tempC < 9){
				tempC += 0x01;
			}
			TimerFlag = 0;
			break;
		case decrease:
			if(tempC >= 0x01){

				tempC -= 0x01;
			}
			TimerFlag = 0;
			break;
		case reset:
			tempC = 0x00;
			break;
	}
	

}

int main(void) {
    /* Insert DDR and PORT initializations */
	
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */

    TimerSet(100);
    TimerOn();
    state = init;
    tempC = 0x07;
    //unsigned char tempC = 0x07;
    while (1) {
	LED_ON();
	PORTC = tempC;	
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}

