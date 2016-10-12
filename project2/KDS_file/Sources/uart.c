/*************************************************************************************
 * uart.c
 *
 *  Created on: Oct 7, 2016
 *      Author: Richard and Omkar
 *  University:University of Colorado Boulder
 *      Course: ECEN Fall 2016
 ****************************************************************************************
 /*Description:
  * This function includes the uart initialization functions and the uart transmit and recieve functions
  * The functions for printing datat to the serial terminal are called here
  ***************************************************************************************/
#include "uart.h"
/*Function to initialize the UART0*/
void uart0_init(void)
{
	SIM->SCGC4 |= 0x0400;		//Enable clock for UART0
	SIM->SOPT2 |= 0x04000000;	//Use FLL output for UART0
	UART0->C2=0;				//UART0 off to change configurations

}
/*Function to transmit data on the uart*/
void uart0_tx(void)
{
	UART0->BDH = 0x00;			//Higher bit of Baud
	UART0->BDL = 0x17;			//Lower bit of baud
	UART0->C4 = 0x0F;			//OSR = 16;
	UART0->C1 = 0x00;			//8 bit data
	UART0->C2 |= 0x08;			//Start the uart enable transmit
	SIM->SCGC5 |=0X0200;		//Clock for port A
	PORTA->PCR[2] |= 0x0200;	//make PTA2 UART0 transmitter pin
}
/*Function to receive data on the UART*/
void uart0_rx(void)
{
	UART0->BDH = 0x00;			//Higher bit of Baud
	UART0->BDL = 0x17;			//Lower bit of baud
	UART0->C4 = 0x0F;			//OSR = 16;
	UART0->C1 = 0x00;			//8 bit data
	UART0->C2 |= 0x04;			//Start the uart enable receive
	UART0->C2 |= 0x20;			//Enable the receive interrupt
	NVIC->ISER[0]=0x00001000;	//enable INT12 ie uart0 interrupt
	SIM->SCGC5 |=0X0200;		//Clock for port A
	PORTA->PCR[1] |= 0x0200;	//make PTA1 UART0 receiver pin
}
/*Function to print data of any lenght on the terminal*/
void print_stringl(char *ptr)
{
 int len=0;
while(*ptr!='\0')
  {
  len++;
  ptr++;
  }
ptr=ptr-len;
print_string(ptr,len);
}
/*Function to print data of given length on the terminal*/
void print_string(char *ptr_str, uint32_t len)
{
	int i;
	for(i=0;i<len;i++)
		{send_data(*ptr_str++);
		}
}
/*UART0 Interrupt Handler*/
void UART0_IRQHandler(void)
{
	char led_value;
	led_value = UART0->D;

/***********************Color selection**************************************************************/
	if(led_value=='q')						//Red
		{
		color='q';
		red();
		}

	else if(led_value == 'w')				//Green
		{
		color='w';
		green();
		}
	else if(led_value == 'e')			//Blue
		{
		color='e';
		blue();
		}
	else if(led_value == 'r')			//Yellow
		{
		color='r';
		red();
		green();
		}
	else if(led_value == 't')			//Purple
		{
		color='t';
		red();
		blue();
		}
	else if(led_value == 'y')			//Sky Blue
		{
		color='y';
		blue();
		green();
		}
	else if(led_value == 'u')		//White
		{
		color='u';
		red();
		green();
		blue();
		}
	else if(led_value == 'i')		//All off
		{
		red_off();
		green_off();
		blue_off();
		BRIGHTNESS=0x8000;
		}
/**************************************************************************************/
/*********Brightness control**********************************************************/
	else if(led_value=='o')								//Increase the brightness
		{
		if(BRIGHTNESS > (0x1000))
		{
		BRIGHTNESS = (BRIGHTNESS - 0x1000);
		}
		if(color=='q')
		{
		while(!(TPM2->CONTROLS[0].CnSC & 0x80))	{}		//Red
		TPM2->CONTROLS[0].CnSC |= 0x80;
		TPM2->CONTROLS[0].CnV = BRIGHTNESS ;
		}
		else if(color=='w')
		{
		while(!(TPM2->CONTROLS[0].CnSC & 0x80))	{}		//Green
		TPM2->CONTROLS[1].CnSC |= 0x80;
		TPM2->CONTROLS[1].CnV = BRIGHTNESS ;
		}
		else if(color=='e')
		{
		while(!(TPM2->CONTROLS[0].CnSC & 0x80))	{}		//Blue
		TPM0->CONTROLS[1].CnSC |= 0x80;
		TPM0->CONTROLS[1].CnV = BRIGHTNESS;
		}
	}
	else if(led_value=='p')								//Decrease the brightness
		{
		if(BRIGHTNESS < (0xF000))
			{
			BRIGHTNESS = (BRIGHTNESS + 0x1000);
			}
		if(color=='q')
			{
			red_brightness();
			}
		else if(color=='w')
			{
			green_brightness();
			}
		else if(color=='e')
			{
			blue_brightness();
			}
		}
/**************************************************************************************************/
/***********Turn off Red Green or Blue individually***********************************************/
	else if(led_value=='a')
		{
		red_off();
		BRIGHTNESS=0x8000;
		}
	else if(led_value=='s')
		{
		green_off();
		BRIGHTNESS=0x8000;
		}
	else if(led_value=='d'){
		blue_off();
		BRIGHTNESS=0x8000;
		}
/*****************************************************************************************************/
/*****************************************************************************************************/
/*Receive data in the form of string and print it*****************************************************/
	else if(led_value=='z')
		{
//		print("hello\n\r");
//		blue();
//		char temp[]="what",* w;
//		w=&temp;
//		print(w);
//		int l;
//		l= receive_data(w);
//		print(w);
//		blue_off();
		circBuff();
		}

}

