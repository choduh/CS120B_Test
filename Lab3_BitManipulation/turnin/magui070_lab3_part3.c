/*	Author: magui070
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #3  Exercise #3
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
   // DDRB = 0x00; PORTB = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;


    unsigned char tank;
   
   
    /* Insert your solution below */
    while (1) {


	  unsigned char key = PINA & 0x10;
	  unsigned char seat = PINA & 0x20;
	  unsigned char seatbelt = PINA & 0x40;
	
	   
	  
	  tank = 0x00;
	  tank = PINA & 0x0F;
	  if(tank <= 4){
		  PORTC = 0x40;
	  }
	  else{
		  PORTC =0x00;
	  }
	  
	  if(tank == 0x01 || tank == 0x02){
		  PORTC = PORTC | 0x20;
		  
	  }
	  else if(tank == 3 || tank == 4){
		  PORTC = PORTC | 0x30;
	  }
	  else if (tank == 5 || tank == 6){
		  
		  PORTC = PORTC | 0x38;
	  }
	  else if(tank >= 7 && tank <=9){
		  PORTC = PORTC | 0x3C;
		  
	  }
	  else if(tank >= 10 && tank <= 12){
		  PORTC = PORTC | 0x3E;
	  }
	  else if(tank >= 13 && tank <= 15){
		  PORTC = PORTC | 0x3F;
	  }
	 
	  if((key == 0x10) && (seat == 0x20) && (seatbelt == 0x00)){
		   
		   PORTC = PORTC | 0x80;
	  }
	  
    }
    return 0;
}
