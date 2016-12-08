/*
 * uart.c
 *
 *  Created on: 27-Oct-2016
 *      Author: Richard Noronha and Omkar Purandare
 */
#include "main.h"

/*****Function to initialize the UART0******/
void uart0_init(void)
{
	SIM->SCGC4 |= 0x0400;		//Enable clock for UART0
	SIM->SOPT2 |= 0x04000000;	//Use FLL output for UART0
	UART0->C2=0;				//UART0 off to change configurations


}
/******Function to transmit data on the uart*******/
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
/*****Function to receive data on the UART*********/
void uart0_rx(void)
{
	UART0->BDH = 0x00;			//Higher bit of Baud
	UART0->BDL = 0x17;			//Lower bit of baud
	UART0->C4 = 0x0F;			//OSR = 16;
	UART0->C1 = 0x00;			//8 bit data
	UART0->C2 |= 0x04;			//Start the uart enable receive
	UART0->C2 |= 0x20;			//Enable the receive interrupt
	NVIC->ICER[0]=(0x00001000);	//enable INT12 ie uart0 interrupt
	SIM->SCGC5 |=0X0200;		//Clock for port A
	PORTA->PCR[1] |= 0x0200;	//make PTA1 UART0 receiver pin
}

/*********Function to receive data on the UART with interrupts*********/
void uart0_rx_int_based(void)
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


/******IRQ handler for receive interrupt*******/
void UART0_IRQHandler(void)
{
	extern uint8_t superuser;
	char key_input;
	key_input = UART0->D;
		if(key_input=='o')
		{
			superuser=1;
		}
}


/*******Function to print data of any length on the terminal********/
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


/*******Function to print data of given length on the terminal******/
void print_string(char *ptr_str, uint32_t len)
{
	int i;
	for(i=0;i<len;i++)
		{send_data(*ptr_str++);
		}
}


