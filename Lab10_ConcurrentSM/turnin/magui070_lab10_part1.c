/*	Author: magui070
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #10  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


enum SMone{led1, led2, led3}ThreeLEDsSM;
enum SMtwo{blink1, blink2}BlinkingLEDSM;
enum SMthree{combine1, combine2}CombineLEDsSM;

unsigned char ledThree = 0x00;
unsigned char ledBlink = 0x00;

void threeLEDs(){


	switch(ThreeLEDsSM){

		case led1:
			ThreeLEDsSM = led2;
			break;
		case led2:
			ThreeLEDsSM = led3;
			break;
		case led3:
			ThreeLEDsSM = led1;
			break;
		default:
			ThreeLEDsSM = led1;
			break;
	}

	switch(ThreeLEDsSM){
		
		case led1:
			ledThree = 0x01;
			break;
		case led2:
			ledThree = 0x02;
			break;
		case led3:
			ledThree = 0x04;
			break;
		
	}


}

void blinkingLEDs(){
	
	switch(BlinkingLEDSM){
		case blink1:
			BlinkingLEDSM = blink2;
			break;
		case blink2:
			BlinkingLEDSM = blink1;
			break;
		default:
			BlinkingLEDSM = blink1;
			break;	
	}

	switch(BlinkingLEDSM){
		
		case blink1:
			ledBlink = 0x08;
			break;
		case blink2:
			ledBlink = 0x00;
			break;
	}

}

void combineLEDs(){

	switch(CombineLEDsSM){
		case combine1:
			CombineLEDsSM = combine2;
			break;
		case combine2:
			CombineLEDsSM = combine1;
			break;
		default:
			CombineLEDsSM = combine1;
			break;
	}

	switch(CombineLEDsSM){
		
		case combine1:
			PORTB = ledThree | ledBlink;
			break;
		case combine2:
			PORTB = ledThree | ledBlink;
			break;
	}
}


int main(void) {
    /* Insert DDR and PORT initializations */

	
	//DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

	TimerOn();
	TimerSet(1000);

    /* Insert your solution below */
    while (1) {
	threeLEDs();
	blinkingLEDs();
	combineLEDs();
	while(!TimerFlag){};
	TimerFlag = 0;
    }
    return 1;
}
