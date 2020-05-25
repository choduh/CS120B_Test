/*	Author: magui070
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #10  Exercise #4
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

enum SMone{led1, led2, led3}ThreeLEDsSM;
enum SMtwo{blink1, blink2}BlinkingLEDSM;
enum SMthree{combine1, combine2}CombineLEDsSM;

//enum SMFreq{start, wait, on, high, low, inc, dec}SpeakerState;

unsigned char ledThree = 0x00;
unsigned char ledBlink = 0x00;

unsigned short frequency = 0x02;

unsigned short freqCount = 0x00;

//unsigned char button = 0x00;



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

enum Speaker{sInit, on, off, sWait}button_state;

unsigned short outSpeaker = 0x00;
unsigned short speakerCount = 0x00;

void toggle(){
	
	//unsigned char play = ~PINA & 0x01;

	switch(button_state){
		
		case sInit:
			button_state = sWait;
			speakerCount = 0;
			break;
		case on:
			if(((~PINA & 0x04) == 0x04) && (speakerCount < frequency)){
				button_state = on;
				++speakerCount;
			}
			else if((~PINA & 0x04) == 0x04){
				button_state = off;
				speakerCount = 0;
			}
			else{
				button_state = sWait;
			}
			break;
		case off:
			if(((~PINA & 0x04) == 0x04) && (speakerCount < frequency)){
				button_state = off;
				++speakerCount;
			}
			else if((~PINA & 0x04) == 0x04){
				button_state = on;
				speakerCount = 0;
			}
			else{
				button_state = sWait;
			}
			break;
		case sWait:
			if((~PINA & 0x04) == 0x04){
				button_state = on;
			}
			else{
				button_state = sWait;
			}
			break;
		default:
			break;
	}


	switch(button_state){
		case sInit:
			break;
		case on:
			outSpeaker = 0x40;
			break;
		case off:
			outSpeaker = 0;
			break;
		case sWait:
			outSpeaker = 0x00;
			speakerCount = 0;
			break;
		default:
			break;
	}

}


enum SMFreq{init,inc, dec, wait}freqState;





void freq(){
	
	//unsigned char up = ~PINA & 0x02;
	//unsigned char down = ~PINA & 0x03;
		
	switch(freqState){
	
		case init:
			freqState = wait;
			break;
		case wait:
			if(((~PINA & 0x01) == 0x01) && frequency < 7 && freqCount > 1000){
			freqState = inc;
			freqCount = 0;
			}
			else if(((~PINA & 0x02) == 0x02) && frequency > 0 && freqCount > 1000){
			freqState = dec;
			freqCount++;
			}
		case inc:
			freqState = wait;
			break;
		case dec:
			freqState = wait;
			break;
		default:
			break;
	

	}

	switch(freqState){
		case init:
			break;
		case wait:
			break;
		case inc:
			frequency++;
			break;
		case dec:
			frequency--;
			break;
		default:
			break;
			

	}
}




void combineLEDs(){
	

	switch(CombineLEDsSM){
		case combine1:
			CombineLEDsSM = combine2;
			break;
		case combine2:
			break;
		default:
			CombineLEDsSM = combine1;
			break;
	}
	switch(CombineLEDsSM){
		case combine1:
			break;
		case combine2:
			PORTB = ledThree | ledBlink | outSpeaker;
			break;
		default:
			break;
	}
	
}

int main(void) {
    /* Insert DDR and PORT initializations */

	
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

	unsigned long ledPeriod = 1000;
	unsigned long blinkPeriod = 1000;

	const unsigned long timer = 2;

	//unsigned long speakerPeriod = 2;
	speakerCount = 0;

	TimerOn();
	TimerSet(2);
	


    /* Insert your solution below */
    while (1) {

	
	if(ledPeriod >= 300){
		threeLEDs();
		ledPeriod = 0;
	}
	if(blinkPeriod >= 1000){
		blinkingLEDs();
		blinkPeriod = 0;
	}

	/*if(speakerPeriod >= 2){
		toggle();
		speakerPeriod = 0;
	}*/
	
	freq();
	toggle();
	combineLEDs();


	while(!TimerFlag){};
	TimerFlag = 0;

	ledPeriod += timer;
	blinkPeriod += timer;
	//speakerPeriod += timer;
    }
    return 0;
}
