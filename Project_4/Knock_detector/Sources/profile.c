/*
 * profile.c
 *
 *  Created on: 27-Oct-2016
 *      Author: omkar
 */
/*Description: This file contains the file for the profiling for the FRDM board*/

#include "main.h"
/******Profiler timer initialization********/
void profile_timer_init(void)
{
	int overflow;
	overflow = 0;
	SIM->SCGC6|=0x02000000;						//Enable clock for TPM1
	SIM->SOPT2 |= 0x01000000;					//Use fll ouput for TPM0
	TPM1->SC = 0;								//Counter off
	TPM1->SC |= 0x84;							//Prescalar is 16
	TPM1->MOD = 0xFFFF;							//Maximum value the counter will count to
}

/*******Turn on the timer for profiling**********/
void timer_on(void)
{
	TPM1->SC |= 0x08;				//Start the timer
}

/*Turn off the timer*/
void timer_off(void)
{
	TPM1->SC=0;						//Stop the timer
}
/*Reset the timer*/
void timer_reset(void)
{
	TPM1->CNT = 0;					//Set counter value to 0
}

/****Calculation of the time taken********/
float timer_calculate(void)
{
	float timer_cycles, run_time;
	float time_of_function;
	timer_cycles=(float)(TPM1->CNT);						//Counter current value is converted to float to use in ftoa
	run_time=((float)(0.763)) * timer_cycles;				//  (20971520/16)^-1=0.763;    timer_cycles*0.763=run_time in microseconds
	return run_time;
}

/******Function to print the value of the timer**********/
void timer_print(void)
{
	float profile_time;
	char transfer[20];
	char *b=transfer;
	uint32_t len=0;
	profile_time=timer_calculate();							//Call the calcluation function
	ftoa(profile_time, transfer, 2);
	while(*b!='\0')
	  {
		  len++;
		  b++;
	  }
	print_string(transfer, len);
	print("micro seconds");
}




