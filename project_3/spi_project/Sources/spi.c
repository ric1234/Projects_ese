/*
 * spi.c
 *
 *  Created on: Oct 25, 2016
 *      Author: richa
 */

#include "spi.h"


void spi_init(void)
{
	SIM->SCGC4 |= 0x00400000;			//Turn on clock for SPI0
	SPI0_C1 = 0;
}

void spi_master(void)
{
	SIM->SCGC5 = 0x00000800;			//Clock port C

	//CE ON by default
	PORTC_PCR8 = PORT_PCR_MUX(1);								/* Set the PTB8 pin multiplexer to GPIO mode */
	GPIOC_PCOR |= CE_SHIFT;									/* Set the initial output state to low */
	GPIOC_PDDR |= CE_SHIFT;									/* Set the pins direction to output */

	//CSN is HIGH by default
	PORTC_PCR9 = PORT_PCR_MUX(1);								/* Set the PTB9 pin multiplexer to GPIO mode */
	GPIOC_PSOR |= CSN_SHIFT;									/* Set the initial output state to high */
	GPIOC_PDDR |= CSN_SHIFT;									/* Set the pins direction to output */

	//for IRQ from the Spi device
	PORTC_PCR10 = PORT_PCR_MUX(1);								/* Set the PTB10 pin multiplexer to GPIO mode */
	GPIOC_PDDR |= CE_IRQ_SHIFT;									/* Set the pins direction to input */

	/*************************************************************/
	PORTC->PCR[4]=0x0000200;			//CS mode
	PORTC->PCR[5]=0X0000200;			//CK
	PORTC->PCR[6]=0x0000200;			//MOSI
	PORTC->PCR[7]=0x0000200;			//MISO

	SPI0_C1 |= 0x12;				//SSOE=1, MSb first
	SPI0_C2 |= 0x10;					//MODFEN=1		SS is automatic output
	SPI0_BR |= 0x60;					//Baud rate is selected

	//SPE =1 ie Put spi on
	SPI0_C1 |= 0x40;					//Startb the spi

}

unsigned char spi_tx(uint8_t * data)
{
	volatile char dummy;
	while(!(SPI0->S & 0x20)){}		//Wait for buffer to be empty
	SPI0->D = *data;

	while(!(SPI0->S & 0x80)){}		//Wait for transmission to be complete
	dummy=SPI0->D;

	return dummy;
}
