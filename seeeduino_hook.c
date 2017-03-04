/*
 * seeeduino_hook.c
 *
 * Code for Seeeduino V4.2, waits for input pin B2 to go high
 * servo sweeps 180 degrees, then on another button
 * press it sweeps back - for use in locking mechanism
 * for hook in D4 design project.
 * (using timer0)
 *
 *  Created on: 4 Mar 2017
 *      Author: brendanelmes
 */
#include <avr/io.h>
#include <util/delay.h>

void init_pwm(void);

int main(void)
{
        uint8_t duty;       //initialize variable to hold duty cycle value
	init_pwm();

	for(;;)
		{
        while((PIND & _BV(PD6))==0);            //wait for pin D6 to go high
	for (duty = 6; duty < 27; duty += 1)  //increase duty cycle from 4.6% to 9.7%
		{
	      OCR0A = duty;					//change value of duty cycle
	      _delay_ms(20);				//delay to allow servo to update position
		}
        while((PIND & _BV(PD6))==0);            //wait for pin D6 to go high
	for (duty = 27; duty >= 6; duty -= 1)  //decrease duty cycle from 9.7% to 4.6%
		{
			OCR0A = duty;				//change value of duty cycle
			_delay_ms(20);				//delay to allow servo to update position
		}
		}
}

void init_pwm(void)			//function which sets up the pwm mode, freq and i/o pins.
{
	OCR0A = 6;
        DDRD |= _BV(PD6); 			//Set Pin D6 as output
        DDRD &= ~_BV(PD2);			//Set Pin D2 as input
	TCCR0A = _BV(COM0A1) | _BV(WGM00) | _BV(WGM01);	//Set non-inverting PWM mode,
                                                        //set fast PWM with top value = 0xFF (Not OCRA)
	TCCR0B = _BV(CS02) | _BV(CS00);		//Set Clock select to give prescaler 1024
}
