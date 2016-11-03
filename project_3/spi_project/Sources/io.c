/*
 * io.c
 *
 *  Created on: 27-Oct-2016
 *      Author: omkar
 */
/*Description: Contains functions which are used for sending characters of data across the uart*/
#include "main.h"

/*Sends data as single character*/
void send_data(char character)
{
	UART0->D = (uint8_t)character;						//Move the character to the Uart data buffer
	while(!(UART0->S1 & 0x80))	{}						//Wait for the transmit to take place
}

/*Receive data from the uart channel. Needs a destination to point to*/
int receive_data(char* c)
{
	int i,len;
	for(i=0;i<5;i++)									//Take in 5 characters
		{
			while(!(UART0->S1 & 0x20))	{}				//Wait for the characters to be input
			if(UART0->D==13)							//Break if Return key is pressed
					break;
			*c = UART0->D;
			c++;
			len;
		}
	return len;
}

/*Blocking function for UART*/
char receive_data_char(void)
{
	char c,*m;
	m=&c;
	while(!(UART0->S1 & 0x20))	{}
	c = UART0->D;
	print(m);
}




