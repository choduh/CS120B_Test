/*	Author: magui070
 *  Partner(s) Name: 
 *	Lab Section:023
 *	Assignment: Lab #5  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
   


    unsigned char tank, level;
    
   
    /* Insert your solution below */
    while (1) {

	level = 0x00;
	tank = ~PINA & 0x0F;
	if(tank <= 4){
		level = 0x40;
	}
	else{
		level = 0x00;
	}
	if(tank == 0x01 || tank == 0x02){
		level = level | 0x20;
	}
	else if(tank == 3 || tank == 4){
		level = level | 0x30;
	}
	else if(tank == 5 || tank == 6){
		level = 0x38;
	}
	else if(tank >= 7 && tank <= 9){
		level = level | 0x3C;
	}
	else if(tank >= 10 && tank <= 12){
		level = level |	0x3E;
	}
	else if(tank >= 13 && tank <= 15){
		level = level | 0x3F;
	}
	
	PORTC = level;

	
   }	
	
    return 1;
}
