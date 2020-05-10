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

enum States{START, wait, increment, decrement, reset}lcd_state;

unsigned char b1;
unsigned char b2;
unsigned char number;

void numTick(){

	b1 = (~PINA & 0x01);
	b2 = (~PINA & 0x02);
	

	switch(lcd_state){

		case START:
			lcd_state = wait;
			break;
		case wait:
			if(b1 && !b2){
				lcd_state = increment;
			}
			else if(!b1 && b2){
				lcd_state = decrement;
			}
			else if(b1 && b2){
				lcd_state = reset;
			}
			else{
				lcd_state = wait;
			}
			break;
		case increment:
			if(b1 & !b2){

				lcd_state = increment;
			}
			else if(b1 && b2){
				lcd_state = reset;
			}
			else{
				lcd_state = wait;
			}
			break;
		case reset:
			lcd_state = (b1 && b2) ? reset : wait;
			break;
		default:
			lcd_state = START;
			break;
	}
	switch(lcd_state){
		case wait:
			break;
		case increment:
			if(number < 9){
				number++;
			}
			break;
		case decrement:
			if(number > 0){
				number--;
			}
			break;
		case reset:
			number = 0;
			break;
		default:
			lcd_state = START;
			break;


	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
     DDRA = 0x00; PORTA = 0xFF;
     DDRC = 0xFF; PORTC = 0x00;
     DDRD = 0xFF; PORTD = 0x00;


    TimerSet(100);
    TimerOn();

    LCD_init();

    LCD_ClearScreen();

    lcd_state = START;
    number = 0x00;
   

    /* Insert your solution below */
    while (1) {
	
	
	LCD_Cursor(1);	
	numTick();
	LCD_WriteData(number + '0');	
	while(!TimerFlag){};
	
	TimerFlag = 0;
		
    }
    
}
