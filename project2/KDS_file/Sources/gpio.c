/*
 * gpio.c
 *
 *  Created on: Oct 6, 2016
*      Author: Richard Noronha and Omkar Purandare
 *  University:University of Colorado Boulder
 *      Course: ECEN Fall 2016
 */
/*Description: This fiile includes the function to initialize the LED [in in gpio mode.
 * This is mainly used for testing code
 */
#include "gpio.h"

void rgb_init(void)
{

	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK|SIM_SCGC5_PORTD_MASK;		/* Turn on clock to PortB and PortD module */

	PORTB_PCR18 = PORT_PCR_MUX(1);								/* Set the PTB18 pin multiplexer to GPIO mode */
	GPIOB_PSOR |= RED_SHIFT;									/* Set the initial output state to high */
	GPIOB_PDDR |= RED_SHIFT;									/* Set the pins direction to output */

	PORTB_PCR19 = PORT_PCR_MUX(1);								/* Set the PTB19 pin multiplexer to GPIO mode */
	GPIOB_PSOR |= GREEN_SHIFT;									/* Set the initial output state to high */
	GPIOB_PDDR |= GREEN_SHIFT;									/* Set the pins direction to output */

	PORTD_PCR1 = PORT_PCR_MUX(1);								/* Set the PTD1 pin multiplexer to GPIO mode */
	GPIOD_PSOR = BLUE_SHIFT;									/* Set the initial output state to high */
	GPIOD_PDDR |= BLUE_SHIFT;									/* Set the pins direction to output */

}



