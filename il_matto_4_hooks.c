/*
 * 4Hooks.c
 *
 *  Created on: 4 Mar 2017
 *      Author: brendanelmes
 */
#include <avr/io.h>
#include <util/delay.h>

void init_pwm(void);

int main(void)
{
	uint8_t duty;		//initialize variable to hold duty cycle
	init_pwm();
	for(;;)
		{
///////////////////////////
	while((PINB & _BV(PB2))==0);
	for (duty = 6; duty < 27; duty += 1)  //increase duty cycle from 4.6% to 9.7%
		{
	      OCR0A = duty;					//change value of duty cycle
	      _delay_ms(20);				//delay to allow servo to update position
		}
	duty = 27;
	while((PINB & _BV(PB2))==0);
	for (duty = 27; duty >= 6; duty -= 1)  //decrease duty cycle from 9.7% to 4.6%
		{
			OCR0A = duty;				//change value of duty cycle
			_delay_ms(20);				//delay to allow servo to update position
		}
		duty = 6;
//////////////////////////
	while((PINB & _BV(PB1))==0);
	for (duty = 6; duty < 27; duty += 1)  //increase duty cycle from 4.6% to 9.7%
		{
	      OCR0B = duty;					//change value of duty cycle
	      _delay_ms(20);				//delay to allow servo to update position
		}
	duty = 27;
	while((PINB & _BV(PB1))==0);
	for (duty = 27; duty >= 6; duty -= 1)  //decrease duty cycle from 9.7% to 4.6%
		{
			OCR0B = duty;				//change value of duty cycle
			_delay_ms(20);				//delay to allow servo to update position
		}
	duty = 6;
/////////////////////////////
	while((PIND & _BV(PD4))==0);
	for (duty = 6; duty < 27; duty += 1)  //increase duty cycle from 4.6% to 9.7%
		{
	      OCR2A = duty;					//change value of duty cycle
	      _delay_ms(20);				//delay to allow servo to update position
		}
	duty = 27;
	while((PIND & _BV(PD4))==0);
	for (duty = 27; duty >= 6; duty -= 1)  //decrease duty cycle from 9.7% to 4.6%
		{
			OCR2A = duty;				//change value of duty cycle
			_delay_ms(20);				//delay to allow servo to update position
		}
	duty = 6;
/////////////////////////////
	while((PIND & _BV(PD5))==0);
	for (duty = 6; duty < 27; duty += 1)  //increase duty cycle from 4.6% to 9.7%
		{
	      OCR2B = duty;					//change value of duty cycle
	      _delay_ms(20);				//delay to allow servo to update position
		}
	duty = 27;
	while((PIND & _BV(PD5))==0);
	for (duty = 27; duty >= 6; duty -= 1)  //decrease duty cycle from 9.7% to 4.6%
		{
			OCR2B = duty;				//change value of duty cycle
			_delay_ms(20);				//delay to allow servo to update position
		}
	duty = 6;
/////////////////////////////
	}
}

//function which sets the pwm mode, frequency and pins
void init_pwm(void)
{
	//set initial value for OCRs
	OCR0A = 6;
	OCR0B = 6;
	OCR2A = 6;
	OCR2B = 6;

	//set output pins for OCRs
	DDRB |= _BV(PB3);
	DDRB |= _BV(PB4);
	DDRD |= _BV(PD6);
	DDRD |= _BV(PD7);

	//set input pins for incoming instructions
	DDRB &= ~_BV(PB1);
	DDRB &= ~_BV(PB2);
	DDRD &= ~_BV(PD5);
	DDRD &= ~_BV(PD4);

	//set non-inverting mode fast PWM with top value 0xFF (not OCR)
	TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM00) | _BV(WGM01);
	TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM20) | _BV(WGM21);
	//select clock to give prescaler 1024, giving a frequency of 61Hz
	TCCR0B = _BV(CS02) | _BV(CS00);
	TCCR2B = _BV(CS22) | _BV(CS21) | _BV(CS20);
}
