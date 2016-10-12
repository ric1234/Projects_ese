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
	int overflow;
	overflow=0;
	SIM->SCGC6|=0x02000000;			//Enable clock for TPM1
	SIM->SOPT2 |= 0x01000000;		//Use fll ouput for TPM0
	TPM1->SC = 0;					//Counter off
	TPM1->SC |= 0x84;				//Prescalar is 32
	TPM1->MOD = 0xFFFF;				//Maximum value the counter will count to
	//TPM1->CONTROLS[0].CnSC =0x04;		//Mode is Input capture on rising edge
	//TPM1->CONTROLS[0].CnSC|=0x80;		//CHF is cleared by writing a 1 to the CHF bit
}
void timer_check(void)
{
	while (!(TPM1->SC & 0x80)) {}
		TPM1->SC |= 0x80;			//reset the value of the TOF flag

//	else
//		{
//		RED_OFF;
//		GREEN_TOGGLE;
//		}
}
void timer_on(void)
{
	TPM1->SC |= 0x08;				//Start the timer
}

void timer_off(void)
{
	TPM1->SC=0;						//Stop the timer
}
void timer_reset(void)
{
	TPM1->CNT = 0;					//Set counter value to 0
}
float timer_calculate(void)
{
	float timer_cycles, run_time;
	float time_of_function;
	timer_cycles=(float)(TPM1->CNT);				//Counter current value is converted to float to use in ftoa
	run_time=((float)(0.763)) * timer_cycles;				//  (20971520/16)^-1=0.763;    timer_cycles*1.53=run_time in microseconds
	return run_time;
}

void timer_print(void)
{
	float profile_time;
	char transfer[20];
	char *b=transfer;
	uint32_t len=0;

	profile_time=timer_calculate();
	ftoa(profile_time, transfer, 2);
	while(*b!='\0')
	  {
	  len++;
	  b++;
	  }
		print("\r\nThe time for the function to run is:");
		print_string(transfer, len);
		print("micro seconds");
}
