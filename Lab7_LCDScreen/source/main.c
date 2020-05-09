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
     DDRD = 0xFF; PORTD = 0x00;
     DDRC = 0xFF; PORTC = 0x00;



    LCD_init();

    LCD_DisplayString(1, "Hello World");

    /* Insert your solution below */
    while (1) {
	continue;
    }
    
}
