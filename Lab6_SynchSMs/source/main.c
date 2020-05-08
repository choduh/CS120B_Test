/*	Author: magui070
 *  Partner(s) Name: 
 *	Lab Section:23
 *	Assignment: Lab #6  Exercise #1
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

enum LED{B0, B1, B2} led_state;



void Tick(){

	unsigned char tempC;
	switch(led_state){
		case B0:
			led_state = B1;
			tempC = 0x01;
			break;
		case B1:
			led_state = B2;
			tempC = 0x02;
			break;
		case B2:
			led_state = B0;
			tempC = 0x04;
			break;
		
		default:
			led_state = B0;
			tempC = 0x01;
			break;
		}
	PORTC = tempC;
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    TimerSet(1000);
    TimerOn();
    //unsigned char tmpB = 0x00;
    //unsigned char button = 0x00;
   
    led_state = B0;
    /* Insert your solution below */
    while (1) {
	//tmpB = ~tmpB;
	//PORTB = tmpB;
	Tick();
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 0;
}
