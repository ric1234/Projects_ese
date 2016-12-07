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
#ifdef bluetooth
	UART1->D = (uint8_t)character;						//Move the character to the Uart data buffer
	while(!(UART1->S1 & 0x80))	{}						//Wait for the transmit to take place
#else

	UART0->D = (uint8_t)character;						//Move the character to the Uart data buffer
	while(!(UART0->S1 & 0x80))	{}						//Wait for the transmit to take place
#endif
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
	return c;
}

/*Sends data as single character*/
void send_data_uart1(char character)
{

	UART1->D = (uint8_t)character;						//Move the character to the Uart data buffer
	while(!(UART1->S1 & 0x80))	{}						//Wait for the transmit to take place

}

/*Blocking function for UART*/
char receive_data_char_uart1(void)
{
	char c,*m;
	m=&c;
	while(!(UART1->S1 & 0x20))	{}
	c = UART1->D;
	print(m);
	return c;
}

void bluutooth_test()
{
	/********************************************/
				/*uart1_init();
				uart1_tx();
				uart1_rx();*/

				/***********************************************/
				//Bluetooth part
				/*send_data_uart1('$');
				send_data_uart1('$');
				send_data_uart1('$');

				send_data('$');
				send_data('$');
				send_data('$');

				delay_us(500);

				send_data_uart1('D');

				inner=receive_data_char_uart1();
				outer=hex_to_ascii(inner,ptr);
				print_string(ptr,1);
				print_string(&outer,1);

				inner=receive_data_char_uart1();
				outer=hex_to_ascii(inner,ptr);
				print_string(ptr,1);
				print_string(&outer,1);

				inner=receive_data_char_uart1();
				outer=hex_to_ascii(inner,ptr);
				print_string(ptr,1);
				print_string(&outer,1);*/

}

