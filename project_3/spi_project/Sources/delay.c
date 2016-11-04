/*
 * delay.c
 *
 *  Created on: Oct 31, 2016
 *      Author: richa
 */
#include "delay.h"

void delay_us(int time)
{
	SIM->SCGC6|=0x02000000;						//Enable clock for TPM1
	SIM->SOPT2 |= 0x01000000;					//Use fll ouput for TPM0
	TPM1->SC = 0;								//Counter off
	TPM1->SC |= 0x05;							//Prescalar is 16
	TPM1->MOD = time;							//Maximum value the counter will count to
	TPM1->SC |= 0x08;							//start timer
	while(!(TPM1->SC & 0x80)){}
	TPM1->SC=0;
	TPM1->CNT = 0;
}
