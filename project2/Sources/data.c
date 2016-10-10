/*
 * data.c
 *
 *  Created on: Oct 7, 2016
 *      Author: richa
 */
#include "MKL25Z4.h"
#include "delay.h"
#include "gpio.h"
#include "rgb_pwm_init.h"
#include "main.h"

void send_data(char character)
{
	UART0->D = (uint8_t)character;
	while(!(UART0->S1 & 0x80))	{}
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

	rgb_pwm_control(led_value);

 if(led_value=='o')
	{
	BRIGHTNESS = (BRIGHTNESS + 0x1000);

	while(!(TPM2->CONTROLS[0].CnSC & 0x80))	{}
	TPM2->CONTROLS[0].CnSC |= 0x80;
	TPM2->CONTROLS[0].CnV = BRIGHTNESS ;
	}
 else if(led_value=='p')
 	{
 	BRIGHTNESS=(BRIGHTNESS-0x1000);
 	while(!(TPM2->CONTROLS[0].CnSC & 0x80))	{}
 	TPM2->CONTROLS[0].CnSC |= 0x80;
 	TPM2->CONTROLS[0].CnV = BRIGHTNESS ;
 	}

	else if(led_value=='a'){
		TPM2->SC = 0;}

	else if(led_value=='s'){
		TPM2->SC = 0;}

	else if(led_value=='d'){
		TPM0->SC = 0;}
}
