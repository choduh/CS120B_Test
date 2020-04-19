/*	Author: magui070
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #4  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum button{init, increase, decrease, wait}state;

void LED_ON(){
	unsigned char B1 = (PINA & 0x01);
	unsigned char B2 = ((PINA & 0x02) >> 1);
	unsigned char tempC = 0x07;

	switch (state){

		case init:
			if(!B1 && !B2){
				state = wait;
			}
			else if(B1 && !B2){
				state = increase;
			}
			else if(!B1 && B2){
				state = decrease;
			}
			else{
				state = init;
			}
			
			break;
		case increase:
			if(!B1 && !B2){
				state = init;
			}
			else if(B1 && B2){
				state = 0x00;
			}
			else{
				state = init;
			}
			break;
		case decrease:
			if(!B1 && !B2)
			{
				state = init;	
			}
			else if(B1 && B2)
			{
				state = 0x00;	
			}
			else{
				state = init;
			}
			break;

		case wait:
			if(B1 && B2){

				state = 0x00;
			}
			else if(B1 && !B2){

				state = increase;
			}
			else if(!B1 && B2){
				state = decrease;
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
			tempC = init;
			break;
		case increase:
			if(tempC < 9){
				tempC = tempC +1;
			}
			break;
		case decrease:
			if(tempC > 0){

				tempC = tempC -1;
			}
			break;
		case wait:
			tempC = 0x00;
			break;
		
		default:
			tempC = 0X00;
			break;
	}
	PORTC =	tempC;

}

int main(void) {
    /* Insert DDR and PORT initializations */
	
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x07;
    /* Insert your solution below */

   
    state = init;
    //unsigned char tempC = 0x07;
    while (1) {
	LED_ON();	
    }
    return 1;
}
