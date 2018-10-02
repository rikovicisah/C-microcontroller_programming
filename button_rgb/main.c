/*
 * button_RGB.c
 *
 * Created: 2.10.2018 14:15:51
 * Author : Irhad
 */ 

#include <avr/io.h>
#include <util/delay.h>

 
#define F_CPU 1000000UL
#define BIT_IS_SET(byte, bit) (byte & (1 << bit))
#define BIT_IS_CLEAR(byte, bit) (!(byte & (1 << bit)))

typedef enum{false, true} bool;

bool previousState = false;

char num;

void setup();
void loop();
void ledON(char);

int main(void)
{
    setup();
	loop();
}

void setup(){
	DDRD |= 0xE;
	DDRD &= ~(0x1); // Button Input
}

void loop(){
	PORTD |= (1 << PIND0);
	while(1){
		if(!(PIND & 0x1)){
			previousState = true;
			_delay_ms(20);
			if((!(PIND & 0x1)) & previousState){
							num++;
							ledON(num);
							_delay_ms(500);
			}
		}
	}
}

void ledON(char broj){
	PORTD &= ~(0xE);
	switch(broj%3){
		case 0: PORTD ^= 0x2;
		break;
		case 1: PORTD ^= 0x4;
		break;
		case 2: PORTD ^= 0x8;
		break;
	}
}