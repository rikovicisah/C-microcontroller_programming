/*
 * Lampice paljenje LED.c
 *
 * Created: 22.5.2018 12:30:21
 * Author : Irhad
 */ 

#ifndef F_CPU					// if F_CPU was not defined in Project -> Properties
#define F_CPU 1000000UL			// define it now as 1 MHz unsigned long
#endif

#define bit_is_clear(byte, bit) (!(byte & (1 << bit)))

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

typedef enum { false, true } boolean;
boolean clicked = false;

int sigurno_pritisnut = 0;

void pressed();
void unpressed();

int main(void)
{
	//LED OUTPUT
	DDRB |= (1 << PINB0) | (1 << PINB1) | (1 << PINB2);
	
	//LED LOW
	PORTB &= ~((1 << PINB0) | (1 << PINB1) | (1 << PINB2));
	
	//BUTTON INPUT
	DDRC &= ~(1 << PINC5);
	
	//BUTTON HIGH
	PORTC |= (1 << PINC5);
	
    /* Replace with your application code */
    while (1) 
    {
		if(bit_is_clear(PINC,5)){
			_delay_ms(20);
			if(bit_is_clear(PINC,5)){
				clicked = !clicked;
			}
		}
		
		if(clicked){
			pressed();
			}else{
			unpressed();
		}
		
    }
}

void pressed(){
	_delay_ms(500);
	PORTB ^= (1 << PINB0);
	_delay_ms(500);
	PORTB ^= (1 << PINB1);
	_delay_ms(500);
	PORTB ^= (1 << PINB2);
	
}

void unpressed(){
	_delay_ms(500);
	PORTB ^= (1 << PINB0);
	_delay_ms(500);
	PORTB ^= (1 << PINB0);
	PORTB ^= (1 << PINB1);
	_delay_ms(500);
	PORTB ^= (1 << PINB1);
	PORTB ^= (1 << PINB2);
	_delay_ms(500);
	PORTB ^= (1 << PINB2);
}
