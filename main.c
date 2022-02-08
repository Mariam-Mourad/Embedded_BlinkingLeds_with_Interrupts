/*
 * main.c
 *
 *  Created on: Aug 23, 2019
 *      Author: Mariam
 */
#include"std_types.h"
#include"Bit_calc.h"
#include"DIO_interface.h"
#include"DIO_regs.h"
#include"avr/io.h"
#include<avr/interrupt.h>
#include"Timer_regs.h"

#define PreLoadValue	192
#define FullOverFlows	3906
#define CTCvalue		5000
ISR(TIMER0_OVF_vect)
{
static u16 Local_counter=0;
Local_counter++;
if(Local_counter==(FullOverFlows+1))
{
	Local_counter=0;
	Timer_TCNT0=PreLoadValue;
	TogBit(PORTA,0);
}

}
ISR(TIMER0_COMP_vect)
{static u16 Local_counter2=0;
	Local_counter2++;
	if(Local_counter2==(CTCvalue))
	{
		Local_counter2=0;
		TogBit(PORTA,0);
	}
}
void main (void)
{/*disable force output bit*/
	ClrBit(Timer_TCCR0,7);
	/*choosing waveform -> CTC*/
	ClrBit(Timer_TCCR0,6);
	SetBit(Timer_TCCR0,3);
	/*disable OC pins*/
	ClrBit(Timer_TCCR0,5);
	ClrBit(Timer_TCCR0,4);
	/*prescaler (/8)*/

	ClrBit(Timer_TCCR0,2);
	SetBit(Timer_TCCR0,1);
	ClrBit(Timer_TCCR0,0);
	/***********************************/
	/*Enabling the timer interrupt*/
	SetBit(Timer_TIMSK,1);
	/*******************************/
	/*calculations
	 * ovf time=256 us
	 * freq time=1MHz
	 * tick time=1us
	 * ovf counts=1^6/256=3,906.25‬
	 * Preload Value=256-(.25*256)=‭192‬
	 */
	/*write 200 in the OCR0 reg*/
	Timer_OCR0=200;
/*global interrupt enabled*/
	SetBit(SREG,7);
	DDRA=0x01;

	while(1)
	{



	}
}

/*disable force output bit*/
	//ClrBit(Timer_TCCR0,7);
	/*choosing waveform -> normal*/
	//ClrBit(Timer_TCCR0,6);
	//ClrBit(Timer_TCCR0,3);
	/*disable OC pins*/
	//ClrBit(Timer_TCCR0,5);
	//ClrBit(Timer_TCCR0,4);
	/*prescaler (/8)*/

	//ClrBit(Timer_TCCR0,2);
	//SetBit(Timer_TCCR0,1);
	//ClrBit(Timer_TCCR0,0);
	/***********************************/
	/*Enabling the timer interrupt*/
	//SetBit(Timer_TIMSK,0);
	/*******************************/
	/*calculations
	 * ovf time=256 us
	 * freq time=1MHz
	 * tick time=1us
	 * ovf counts=1^6/256=3,906.25‬
	 * Preload Value=256-(.25*256)=‭192‬
	 */
	/*Preload value in a register*/
	//Timer_TCNT0=PreLoadValue;
/*global interrupt enabled*/
	//SetBit(SREG,7);
	//DDRA=0xFF;
	//PORTA=0x01;
