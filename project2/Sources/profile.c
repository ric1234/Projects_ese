/*
 * profile.c
 *
 *  Created on: Oct 9, 2016
 *      Author: richa
 */
#include "MKL25Z4.h"
#include "delay.h"
#include "gpio.h"
#include "main.h"		//for the value of count

void profile_timer_init(void)
{
	COUNT=0;
	SIM->SCGC6|=0x02000000;			//Enable clock for TPM1
	SIM->SOPT2 |= 0x01000000;		//Use fll ouput for TPM0
	TPM1->SC = 0;
	TPM1->SC = 0x01;				//Prescalar is 2
	TPM1->MOD = 0xFFFF;				//Maximum value the counter will count to
	TPM1->CONTROLS[0].CnSC =0x04;		//Mode is Input capture on rising edge
	TPM1->CONTROLS[0].CnSC|=0x80;		////CHF is cleared by writing a 1 to the CHF bit
	TPM1->SC |= 0x08;				//Start the timer
}
void timer_check(void)
{
	while (!(TPM1->SC & 0x80)) {}
		TPM1->SC |= 0x80;			//reset the value of the TOF flag
		COUNT++;
		if(COUNT==1000)
		{RED_TOGGLE;
		COUNT=0;}
//	else
//		{
//		RED_OFF;
//		GREEN_TOGGLE;
//		}
}
