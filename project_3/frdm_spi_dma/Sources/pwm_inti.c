/*
 * pwm_inti.c
 *
 *  Created on: 03-Nov-2016
 *      Author: omkar
 */

#include"main.h"
void rgb_pwm_init(void)
{
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
