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

void led_pwm(void)
{
	char led_value;
	while(!(UART0->S1 & 0x20))	{}
	led_value = UART0->D;

	if(led_value=='a'){
	while(!(TPM0->CONTROLS[1].CnSC & 0x80))	{}
	TPM0->CONTROLS[1].CnSC |= 0x80;
	TPM0->CONTROLS[1].CnV = 0xFF00 ;
	}

	else if(led_value=='s'){
		while(!(TPM0->CONTROLS[1].CnSC & 0x80))	{}
		TPM0->CONTROLS[1].CnSC |= 0x80;
		TPM0->CONTROLS[1].CnV = 0xDD00 ;
		}

	else if(led_value=='d'){
			while(!(TPM0->CONTROLS[1].CnSC & 0x80))	{}
			TPM0->CONTROLS[1].CnSC |= 0x80;
			TPM0->CONTROLS[1].CnV = 0xCC00 ;
			}

	else if(led_value=='f'){
			while(!(TPM0->CONTROLS[1].CnSC & 0x80))	{}
			TPM0->CONTROLS[1].CnSC |= 0x80;
			TPM0->CONTROLS[1].CnV = 0xAA00 ;
			}

	else if(led_value=='g'){
			while(!(TPM0->CONTROLS[1].CnSC & 0x80))	{}
			TPM0->CONTROLS[1].CnSC |= 0x80;
			TPM0->CONTROLS[1].CnV = 0x9900 ;
			}

	else if(led_value=='h'){
			while(!(TPM0->CONTROLS[1].CnSC & 0x80))	{}
			TPM0->CONTROLS[1].CnSC |= 0x80;
			TPM0->CONTROLS[1].CnV = 0x5500 ;
			}

	else if(led_value=='j'){
			while(!(TPM0->CONTROLS[1].CnSC & 0x80))	{}
			TPM0->CONTROLS[1].CnSC |= 0x80;
			TPM0->CONTROLS[1].CnV = 0x3300 ;
			}

	else if(led_value=='k'){
			while(!(TPM0->CONTROLS[1].CnSC & 0x80))	{}
			TPM0->CONTROLS[1].CnSC |= 0x80;
			TPM0->CONTROLS[1].CnV = 0x00FF ;
			}
}
