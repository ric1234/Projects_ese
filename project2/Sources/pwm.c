/*
 * pwm.c
 *
 *  Created on: Oct 8, 2016
 *      Author: richa
 */
#include "MKL25Z4.h"

void pwm_init(void)
{
	SIM->SCGC6|=0x01000000;		//Enable clock for TPM0
	SIM->SOPT2 |= 0x01000000;	//Use fll ouput for TPM0

	SIM->SCGC5 |= 0X1000;		//Clock for port D
	PORTD->PCR[1] |= 0x0400;	//make PTA2 UART0 transmitter pin

	TPM0->SC = 0;
	TPM0->SC = 0x01;
	TPM0->MOD = 0xFFFF;

	//TPM0->CONF |= 0x80;			//LPTPM should run in Debug mode too

//	TPM0->CONTROLS[1].CnSC|=0x22;			//MSn =2 for edge pwm and edge select is high at 2...check edge select if necessary
//	TPM0->CONTROLS[1].CnV = 0x000F;		//Setting counter value to full.
//
//	TPM0->SC |= 0x08;			//Set CPWMs to up counter and PREscalar is 1:1 default, cmod is 01
//

	TPM0->CONTROLS[1].CnSC =0x28;
	TPM0->CONTROLS[1].CnSC|=0x80;
	TPM0->CONTROLS[1].CnV |= 0xFFFF;
	TPM0->SC |= 0x08;
}

