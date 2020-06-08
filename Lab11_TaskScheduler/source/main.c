/*	Author: magui070
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #11  Exercise #4
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "timer.h"
#include "keypad.h"
#include "scheduler.h"
#include "bit.h"
#include "io.h"
#include "io.c"
#include "simAVRHeader.h"
#endif

enum STATES{start, out}lcd_state;

unsigned char c;
unsigned char x;

void lcdTick(){

	switch(lcd_state){
		case start:
			lcd_state = out;
			break;
		case out:
			x = GetKeypadKey();
			if(x!= '\0'){
				LCD_WriteData(x);
				if(c == 17){
					c = 1;
				}	
				LCD_Cursor(c);
				++c;
			}
			lcd_state = out;
			break;
	}	
}

int main(void) {
    /* Insert DDR and PORT initializations */
	
	DDRA = 0xF0; PORTA = 0x0F;
	//DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;

	TimerOn();
	TimerSet(500);
	
	LCD_init();
	LCD_DisplayString(1, "Yamero!!!");

	lcd_state = start;
	c = 1;
	LCD_Cursor(c);

	
	
	
	
    /* Insert your solution below */
    while (1) {


	while(!TimerFlag){};
	TimerFlag = 0;
	lcdTick();
	
    }
    return 0;
}
