/*
 * rgb_pwm_init.c
 *
 *  Created on: Oct 8, 2016
 *      Author: richa
 */
#include "gpio.h"
#include "MKL25Z4.h"
#include "main.h"
void rgb_pwm_init(void)
{
		BRIGHTNESS=0x8000;
		SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK|SIM_SCGC5_PORTD_MASK;	// Turn on clock to PortB and PortD module

		PORTB->PCR[18] |= 0x0300;								// Set the PTB18 pin multiplexer to PWM  mode
		GPIOB_PSOR |= RED_SHIFT;								// Set the initial output state to high
		GPIOB_PDDR |= RED_SHIFT;								// Set the pins direction to output */

		PORTB->PCR[19] |= 0x0300;								// Set the PTB19 pin multiplexer to PWM mode */
		GPIOB_PSOR |= GREEN_SHIFT;								// Set the initial output state to high */
		GPIOB_PDDR |= GREEN_SHIFT;								// Set the pins direction to output */

		PORTD->PCR[1] |= 0x0400;								// Set the PTD1 pin multiplexer to PWM mode */
		GPIOD_PSOR = BLUE_SHIFT;								// Set the initial output state to high */
		GPIOD_PDDR |= BLUE_SHIFT;								// Set the pins direction to output */
}

void rgb_pwm_control(char color)
{

	if(color=='q')						//Red
		{SIM->SCGC6|=0x04000000;		//Enable clock for TPM2
		SIM->SOPT2 |= 0x01000000;		//Use fll ouput for TPM
		TPM2->SC = 0;
		TPM2->SC = 0x01;				//Prescalar is 2
		TPM2->MOD = 0xFFFF;				//Maximum value the counter will count to is 65535
		TPM2->CONTROLS[0].CnSC =0x28;	//Mode is Edge aligned pwm and high true pulses
		TPM2->CONTROLS[0].CnSC|=0x80;	//CHF is cleared by writing a 1 to the CHF bit
		TPM2->CONTROLS[0].CnV |= BRIGHTNESS;		//Default value of brightness is 0x8000;
		TPM2->SC |= 0x08;				//LPTPM starts counting.
		}

		else if(color == 'w')
		{SIM->SCGC6|=0x04000000;		//Enable clock for TPM2
		SIM->SOPT2 |= 0x01000000;	//Use fll ouput for TPM
		TPM2->SC = 0;
		TPM2->SC = 0x01;
		TPM2->MOD = 0xFFFF;
		TPM2->CONTROLS[1].CnSC =0x28;
		TPM2->CONTROLS[1].CnSC|=0x80;
		TPM2->CONTROLS[1].CnV |= BRIGHTNESS;
		TPM2->SC |= 0x08;
		}
		else if(color == 'e')
		{SIM->SCGC6|=0x01000000;		//Enable clock for TPM0
		SIM->SOPT2 |= 0x01000000;	//Use fll ouput for TPM0
		TPM0->SC = 0;
		TPM0->SC = 0x01;
		TPM0->MOD = 0xFFFF;
		TPM0->CONTROLS[1].CnSC =0x28;
		TPM0->CONTROLS[1].CnSC|=0x80;
		TPM0->CONTROLS[1].CnV |= BRIGHTNESS;
		TPM0->SC |= 0x08;
		}
	//case(YELLOW):		//Red+green

	//case(VIOLET):			//Red+blue

	//case(SKY):				//Green+Blue

	//case(WHITE):				//aLL

	//case(Eight):

}

