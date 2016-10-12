/*
 * colors.c
 *
 *  Created on: Oct 11, 2016
 *    	Author: Richard Noronha and Omkar Purandare
 *  University:University of Colorado Boulder
 *      Course: ECEN Fall 2016
 */
 /*Desciption: These pins are used to initialize the Timers to use for the PWM colors*/
#include "colors.h"
void red(void)
{
		SIM->SCGC6|=0x04000000;					//Enable clock for TPM2
		SIM->SOPT2 |= 0x01000000;				//Use fll ouput for TPM
		TPM2->SC = 0;							//Turn off the Timer
		TPM2->SC = 0x01;						//Prescalar is 2
		TPM2->MOD = 0xFFFF;						//Maximum value the counter will count to is 65535
		TPM2->CONTROLS[0].CnSC =0x28;			//Mode is Edge aligned pwm and high true pulses
		TPM2->CONTROLS[0].CnSC|=0x80;			//CHF is cleared by writing a 1 to the CHF bit
		TPM2->CONTROLS[0].CnV |= BRIGHTNESS;	//Default value of brightness is 0x8000;
		TPM2->SC |= 0x08;						//LPTPM starts counting.

}

void green(void)
{
		SIM->SCGC6|=0x04000000;					//Enable clock for TPM2
		SIM->SOPT2 |= 0x01000000;				//Use fll ouput for TPM
		TPM2->SC = 0;							//Turn off the Timer
		TPM2->SC = 0x01;						//Prescalar is 2
		TPM2->MOD = 0xFFFF;						//Maximum value the counter will count to is 65535
		TPM2->CONTROLS[1].CnSC =0x28;			//Mode is Edge aligned pwm and high true pulses
		TPM2->CONTROLS[1].CnSC|=0x80;			//CHF is cleared by writing a 1 to the CHF bit
		TPM2->CONTROLS[1].CnV |= BRIGHTNESS;	//Default value of brightness is 0x8000;
		TPM2->SC |= 0x08;						//LPTPM starts counting.
}

void blue(void)
{
		SIM->SCGC6|=0x01000000;					//Enable clock for TPM0
		SIM->SOPT2 |= 0x01000000;				//Use fll ouput for TPM0
		TPM0->SC = 0;							//Turn off the Timer
		TPM0->SC = 0x01;						//Prescalar is 2
		TPM0->MOD = 0xFFFF;						//Maximum value the counter will count to is 65535
		TPM0->CONTROLS[1].CnSC =0x28;			//Mode is Edge aligned pwm and high true pulses
		TPM0->CONTROLS[1].CnSC|=0x80;			//CHF is cleared by writing a 1 to the CHF bit
		TPM0->CONTROLS[1].CnV |= BRIGHTNESS;	//Default value of brightness is 0x8000;
		TPM0->SC |= 0x08;						//LPTPM starts counting.

}

void red_brightness(void)
{
		while(!(TPM2->CONTROLS[0].CnSC & 0x80))	{}		//Red brightness control
		TPM2->CONTROLS[0].CnSC |= 0x80;
		TPM2->CONTROLS[0].CnV = BRIGHTNESS ;
}

void green_brightness(void)
{
		while(!(TPM2->CONTROLS[0].CnSC & 0x80))	{}		//Green brightness control
		TPM2->CONTROLS[1].CnSC |= 0x80;
		TPM2->CONTROLS[1].CnV = BRIGHTNESS ;
}

void blue_brightness(void)
{
		while(!(TPM2->CONTROLS[0].CnSC & 0x80))	{}		//Blue brightness control
		TPM0->CONTROLS[1].CnSC |= 0x80;
		TPM0->CONTROLS[1].CnV = BRIGHTNESS ;
}

void red_off(void)
{
	TPM2->CONTROLS[0].CnSC = 0;							//Turn off the channel
}

void green_off(void)
{
	TPM2->CONTROLS[1].CnSC = 0;							//Turn off the channel
}

void blue_off(void)
{
	TPM0->CONTROLS[1].CnSC = 0;							//Turn off the channel
}
