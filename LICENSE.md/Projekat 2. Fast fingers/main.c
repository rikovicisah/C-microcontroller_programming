/*
 * Fast_fingers.c
 *
 * Created: 19.04.2018. 19:59:05
 * Author : kingfWindows
 */ 

#include <avr/io.h>
#include <util/delay.h>

void proces_pritisnut(int btn_pressed);
void proces_pusten(int btn_released);
void restart();

int sigurnost_pritisnut[2]; // da ne bi doslo do "odbijana" tj. 01010100101
int sigurnost_pusten[2];
int led_broj[2];
int pritisnut[2]; // 0 - A, 1 - B

int main(void)
{
    /* Replace with your application code */
	
	//D - igrac A
	DDRD = 0b01111111;
	//B - igrac B
	DDRB = 0b01111111;	
	DDRC = 0b00000011;
	
	PORTB |= 1 << PINB7;
	PORTD |= 1 << PIND7;
	PORTC |= 0 << PINC0;
	PORTC |= 0 << PINC1;
	
    while (1) 
    {
		//Igrac A
		if(bit_is_clear(PIND, 7)) proces_pritisnut(0);
		else proces_pusten(0);
		//Igrac B
		if (bit_is_clear(PINB, 7)) proces_pritisnut(1);
		else proces_pusten(1);
    }
}

void proces_pritisnut(int btn_pressed){
	sigurnost_pritisnut[btn_pressed]++;
	if(sigurnost_pritisnut[btn_pressed] > 500){
		if(pritisnut[btn_pressed] == 0){
			pritisnut[btn_pressed] = 1;
			if(btn_pressed == 0) PORTD |= 1 << led_broj[btn_pressed];
			else PORTB |= 1 << led_broj[btn_pressed];
			led_broj[btn_pressed]++;
			if(led_broj[btn_pressed] >= 7){
				for (int i=0; i<10; i++)
				{
					PORTC = (btn_pressed == 0) ? PORTC ^ (1 << PINC1) : PORTC ^ (1 << PINC0);
					//PORTC ^= 1 << PINC0;
					_delay_ms(300);
				}
				restart();
			}
		}
		sigurnost_pritisnut[btn_pressed] = 0;
	}
}

void proces_pusten(int btn_released){
	sigurnost_pusten[btn_released]++;
	if(sigurnost_pusten[btn_released] > 500){
		pritisnut[btn_released] = 0;
		sigurnost_pusten[btn_released] = 0;
	}
}

void restart(){
	PORTB = 0b10000000;
	PORTD = 0b10000000;
	
	for(int i = 0; i < 2; i++)
		led_broj[i] = 0;
}