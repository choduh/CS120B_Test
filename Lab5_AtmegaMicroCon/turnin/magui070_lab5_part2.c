/*	Author: magui070
 *  Partner(s) Name: 
 *	Lab Section:023
 *	Assignment: Lab #5  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum button{init, increase, decrease, reset, wait1, wait2}state;

unsigned char B1;
unsigned char B2;
unsigned char tempC;


void LED_ON(){
	B1 = ~PINA & 0x01;
	B2 = ~PINA & 0x02;
	//unsigned char tempC = 0x07;

	switch (state){

		case init:
			if(!B1 && !B2){
				state = init;
			}
			else if(B1 && !B2){
				state = increase;
			}
			else if(!B1 && B2){
				state = decrease;
			}
			else{
				state = reset;
			}
			
			break;
		case increase:
			if(B1 && B2){
				state = reset;
			}
			else{
				state = wait2;
			}
			break;
		case decrease:
			if(B1 && B2)
			{
				state = reset;	
			}
			else{
				state = wait2;
			}
			break;

		case reset:
			if(!B1 && !B2){
				state = init;
			}
			else if(B1 && !B2){
				state = decrease;	
			}
			else if(B1 && B2){
				state = reset;
			}
			break;


		case wait1:
			if(B1 && B2){
				state = reset;
			}
			else if(B1 && !B2){
				state = increase;
			}
			else if(!B1 && B2){
				state = decrease;
			}	
			else{
				state = wait1;
			}	
			break;
		case wait2:
			if(!B1 && !B2){
				state = wait1;
			}	
			else if(B1 && B2){
				state = reset;
			}	
			else{
				state = wait2;
			}
			break;
		
	}
	switch(state){
		case init:
			break;
		case increase:
			if(tempC < 9){
				tempC += 0x01;
			}
			break;
		case decrease:
			if(tempC > 0){

				tempC -= 0x01;
			}
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

   
    state = init;
    tempC = 0x00;
    //unsigned char tempC = 0x07;
    while (1) {
	LED_ON();
	PORTC = tempC;	
    }
    return 1;
}
