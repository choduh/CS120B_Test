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

int main(void) {
    /* Insert DDR and PORT initializations */
     DDRA = 0x00; PORTA = 0xFF;
     DDRC = 0xFF; PORTC = 0x00;
     DDRD = 0xFF; PORTD = 0x00;

    unsigned char number = 0x00;

    TimerSet(10);
    TimerOn();

    LCD_init();

    LCD_WriteData('0');

    /* Insert your solution below */
    while (1) {
	if((~PINA & 0x01) && (~PINA & 0x02)){
		number = 0x00;
	}
	else if((~PINA & 0x01) && (number < 9)){
		number += 0x01;
	}
	else if((~PINA & 0x02) && (number >=1)){
		number -= 0x01;
	}
	
	while(!TimerFlag){};
	TimerFlag = 0;
	LCD_Cursor(1);
	LCD_WriteData('0' + number);	
    }
    
}
