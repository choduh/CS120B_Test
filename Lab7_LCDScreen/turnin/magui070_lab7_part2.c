/*	Author:magui070
 *  Partner(s) Name: 
 *	Lab Section:23
 *	Assignment: Lab #7  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "io.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "timer.h"
#endif

unsigned char button;
enum States{B0, wait1, B1, wait2, B2, wait3} led_state;


unsigned char tempA = 0x00;
unsigned char tempB = 0x00;
unsigned char score = 0x00;

void Tick(){

	button = (~PINA & 0x01);
	switch(led_state){
		case B0:
			if(button){
				led_state = wait1;
				if(score > 0){
					score = score -1;
				}
			}
			else{
				led_state = B1;	
			}
			break;
		case wait1:
			if(button){
				led_state = B0;
			}
			else{
				led_state = wait1;
			}
			break;
		case B1:
			if(button){
				led_state = wait2;
				if(score < 9){
					score = score + 1;
				}
			}
			else {
				led_state = B2;
			}
			break;
		case wait2:
			if(button){
				led_state = B1;
			}
			else{
				
				led_state = wait2;
			}
			break;
		case B2:
			if(button){
				led_state = wait3;
				if(score > 0){
					score = score -1;
				}
	
			}
			else{
				led_state = B0;
			}
			break;
		case wait3:
			if(button){
				led_state = B2;
			}
			else{
				led_state = wait3;
			}
			break;
		default:
			led_state = B0;
			break;

	}
	switch(led_state){

	
		case B0:
			tempB = 0x01;
			break;
		case wait1:
			tempB = 0x01;
			break;
		case B1:
			tempB = 0x02;
			break;
		case wait2:
			tempB = 0x02;
			break;
		case B2:
			tempB = 0x04;
			break;
		case wait3:
			tempB = 0x04;
			break;
	}
			

			
}




int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;
    DDRD = 0xFF; PORTD = 0x00;
    TimerSet(500);
    TimerOn();

    
   
    led_state = B0;
    LCD_init();

    LCD_ClearScreen();
    score = 0x05;
    /* Insert your solution below */
    while (1) {
	
	LCD_Cursor(1);
	
	if(score == 9){
		LCD_DisplayString(1, "Winner!");
	}
	else{
		LCD_ClearScreen();
		LCD_WriteData(score + '0');
		if(score == 0){
			LCD_DisplayString(1, "Loser..");
		}
	}

	Tick();
	while(!TimerFlag){};
	TimerFlag = 0;
	PORTB = tempB;
    }
    return 0;
}
