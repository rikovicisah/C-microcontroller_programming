/*
 * Fast Fingers.c
 *
 * Created: 22.5.2018 22:56:47
 * Author : Irhad
 */ 

#ifndef F_CPU
#define F_CPU 1000000UL
#endif

typedef enum{false, true} boolean;

#include <avr/io.h>
#include <util/delay.h>

//LED Igrac A PINC
#define LEDAW_PIN PINC5
#define LEDA3_PIN PINC4
#define LEDA2_PIN PINC3
#define LEDA1_PIN PINC2

//Led Igrac B PIND
#define LEDBW_PIN PIND4
#define LEDB3_PIN PIND5
#define LEDB2_PIN PIND6
#define LEDB1_PIN PIND7

//PIN B
//Button Igrac A
#define BTNA PINB0

//Button Igrac B
#define BTNB PINB1

//#define bit_is_clear(byte, bit) (!(byte & (1 << bit)))

int LED_broj[2]; // 0 = A, 1 = B
boolean unos = true;

int i = 2; // Pocetna pozicija LED-a A igraca
int j = 7; // Pocetna pozicija LED-a B igraca

void proces_pritisnut(int b);
void restart(int b);


int main(void)
{
	DDRC = 0x60; 
	DDRD = 0x240; 
	DDRB = ~(0x3);
	
	PORTC &= (0x0);
	PORTD &= (0x0);
	PORTB |= (0x3);
	
    /* Replace with your application code */
    while (1) 
    {
		//Igrac A
		if(unos){
			if(bit_is_clear(PINB, BTNA)) {
				_delay_ms(20);
				if(bit_is_clear(PINB, BTNA))
					proces_pritisnut(0);
			}
		
			//Igrac B
			if (bit_is_clear(PINB, BTNB)) {
				_delay_ms(20);
				if(bit_is_clear(PINB, BTNA))
					proces_pritisnut(1);
			}
		}else ;
    }
}

void proces_pritisnut(int b){
	LED_broj[b]++;
	if(LED_broj[b] >= 4){
		unos = false;
		restart(b);
	}else{
		switch(b){
			case 0:
				PORTC |= (1 << i++);
				break;
			default:
				PORTC |= (1 << j--);
				break;
		}
	}
	
}

void restart(int b){
	for(int d = 0; d < 10; d++){
		_delay_ms(200);
		if(b)
			PORTD ^= (1 << LEDBW_PIN);
		else
			PORTC ^= (1 << LEDAW_PIN);
	}
	PORTC &= (0x0);
	PORTD &= (0x0);
	
	unos = true;
	
	i = 2;
	j = 7;
}


