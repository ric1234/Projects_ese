/*
 * data.c
 *
 *  Created on: Oct 7, 2016
 *      Author: richa
 */
#include "MKL25Z4.h"
#include "delay.h"
#include "gpio.h"

void send_data(void)
{
	while(!(UART0->S1 & 0x80))	{}
	UART0->D = 'R';
	while(!(UART0->S1 & 0x80)) 	{}
	UART0->D = 'I';
	while(!(UART0->S1 & 0x80)) 	{}
	UART0->D = 'C';
	while(!(UART0->S1 & 0x80)) 	{}
	UART0->D = ' ';
	while(!(UART0->S1 & 0x80)) 	{}
	delayMs(10);
}

void receive_data(void)
{	char c;
	while(!(UART0->S1 & 0x20))	{}
	c = UART0->D;
	 if(c=='a')
			{
				BLUE_ON;
				GREEN_OFF;
				RED_OFF;
			}
			else if(c=='b')
			{
				GREEN_ON;
				BLUE_OFF;
				RED_OFF;
			}
			else if(c=='c')
			{
				RED_ON;
				BLUE_OFF;
				GREEN_OFF;
			}
	while(!(UART0->S1 & 0x20))	{}
}
