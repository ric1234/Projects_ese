/*
 * rgb_pwm_init.c
 *
 *  Created on: Oct 8, 2016
 *      Author: Richard Noronha and Omkar Purandare
 *  University:University of Colorado Boulder
 *      Course: ECEN Fall 2016
 */
/*Description: This file contains the functions for initializing the RGB led for PWM*/
#include "rgb_pwm_init.h"
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
