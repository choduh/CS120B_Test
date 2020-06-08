/*	Author: magui070
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #11  Exercise #3
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

#include "io.h"
#include "io.c"
#include "simAVRHeader.h"
#endif



int main(void) {
    /* Insert DDR and PORT initializations */
	
	DDRA = 0xF0; PORTA = 0x0F;
	//DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;

	
	TimerSet(10);
	TimerOn();
	LCD_init();
	
	LCD_WriteData('0');
	
	
	unsigned char x;
	
	
    /* Insert your solution below */
    while (1) {
	unsigned char keyOut = 0x00;
	
	x = GetKeypadKey();

	switch(x){
		case '\0':keyOut = 0x1F; break;
		case '1': keyOut = 0x01; break;
		case '2': keyOut = 0x02; break;
		case '3': keyOut = 0x03; break;
		case 'A': keyOut = 0x0A; break;
		case '4': keyOut = 0x04; break;
		case '5': keyOut = 0x05; break;
		case '6': keyOut = 0x06; break;
		case 'B': keyOut = 0x0B; break;
		case '7': keyOut = 0x07; break;
		case '8': keyOut = 0x08; break;
		case '9': keyOut = 0x09; break;
		case 'C': keyOut = 0x0C; break;
		case '*': keyOut = 0x0E; break;
		case '0': keyOut = 0x00; break;
		case '#': keyOut = 0x0F; break;
		case 'D': keyOut = 0x0D; break;
		//default: keyOut = keyOut; break;
		
	}
	
	while(!TimerFlag){};
	TimerFlag = 0;

	if(keyOut == 0x01 || keyOut == 0x02 || keyOut == 0x03 || keyOut == 0x04
		|| keyOut == 0x05 || keyOut == 0x06 || keyOut == 0x07 ||
		keyOut == 0x08 || keyOut == 0x09 || keyOut == 0x00){
			LCD_Cursor(1);
			LCD_WriteData('0' + keyOut);
		}
	else if(keyOut == 0x0A){
		LCD_Cursor(1);
		LCD_WriteData('A');
	}

	else if(keyOut == 0x0B){
		LCD_Cursor(1);
		LCD_WriteData('B');
	}	


	else if(keyOut == 0x0C){
		LCD_Cursor(1);
		LCD_WriteData('C');
	}
	else if(keyOut == 0x0D){
		LCD_Cursor(1);
		LCD_WriteData('D');
	}
	
	else if(keyOut == 0x0E){
		LCD_Cursor(1);
		LCD_WriteData('*');
	}
	
	else if(keyOut == 0x0F){
		LCD_Cursor(1);
		LCD_WriteData('#');
	}
	
	else if(keyOut == 0x1F){
		LCD_Cursor(1);
		
	}
	else{
		LCD_Cursor(1);
	}
    }
    return 0;
}
