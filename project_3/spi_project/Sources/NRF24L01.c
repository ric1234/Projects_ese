/*
 * NRF24L01.c
 *
 *  Created on: Oct 27, 2016
 *      Author: richa
 */
#include "NRF24L01.h"

void nrf_cmd_send(FRDM_p * p)
{
	char c;
	int i;
	uint8_t * ptr = (uint8_t *) p;
	CSN_OFF;
	for(i=0; i<((sizeof(FRDM_p))-sizeof(p->length)-(MAX_SIZE-p->length)); i++)
	{
		c=spi_tx(ptr);
		//print_stringl(&c);
		ptr++;
	}
	CSN_ON;
}

void nrf_config_tx(void)
{
	FRDM_p p;
	p.cmd=nrf24l01_CONFIG;						//should be a parameter
	p.data[0]=nrf24l01_CONFIG_PWR_UP;			//generalize this also
	p.length=1;							//how to make it more generic...might be taken as a parameter
	nrf_cmd_send(&p);
}

void nrf_config_rx(void)
{
	FRDM_p p;
	p.cmd=nrf24l01_CONFIG;						//should be a parameter
	p.data[0]=nrf24l01_CONFIG_PWR_UP;			//generalize this also
	p.data[1]=nrf24l01_CONFIG_PRIM_RX;
	p.length=2;							//how to make it more generic...might be taken as a parameter
	nrf_cmd_send(&p);
	//CE_ON; //to enable sensing on the antenna
}

void nrf_status(void)
{
	FRDM_p p;
	p.cmd=nrf24l01_STATUS;
	p.data[0]=0xFF;			//data should come on the miso line
}

void nrf_tx_read(void)
{
	FRDM_p p;
	p.cmd=nrf24l01_R_REGISTER | nrf24l01_TX_ADDR;
	p.data[0]=0xFF;
	p.data[1]=0xFF;
	p.length=2;
	nrf_cmd_send(&p);
}

void nrf_rx_fifo(void)
{
	//Check for RX_DR interrupt
	//involves use of CE
	//CE_ON;		//Enables the reciever from antenna
	//CE_OFF;		//Disable the receiver
	FRDM_p p;
		p.cmd=nrf24l01_R_RX_PAYLOAD;
		//Number of dummy bytes is same as payload width of the pipe used
		p.data[0]=0xFF;
		p.data[1]=0xFF;
		p.data[2]=0xFF;
		p.length=3;
		nrf_cmd_send(&p);
		//clear RX_DR interrupt
		//CE_ON;		//continue monitoring for pacets
}

void nrf_tx_fifo(void)
{
	//Be in TX mode
	//Check for RX_DR interrupt
	//involves use of CE
	CE_OFF;		//Enable the transmitter
	FRDM_p p;
		p.cmd=nrf24l01_W_TX_PAYLOAD;
		//The number of payload bytes you send MUST match the payload length of the receiver you
		//are sending the payload to.
		p.data[0]=0x11;				//Max fifo is 3 levels deep
		p.data[1]=0xAA;
		p.data[2]=0x33;
		p.length=3;
		nrf_cmd_send(&p);
		//Send the data on the TX wirelessly
		//CE_ON;		//continue monitoring for pacets
		//delay_us(10);
		//CE_OFF;

		/*If you had auto-ack enabled on this pipe, the TX_DS flag will only be set if the packet actually
gets through. If the maximum amount of retries is hit, then the MAX_RT interrupt will
become active. At this point, you should clear the interrupts and continue based on
which interrupt was asserted.*/

}

void nrf_flush_tx(void)
{
	FRDM_p p;
			p.cmd=nrf24l01_FLUSH_TX;
			p.length=0;
			nrf_cmd_send(&p);
}

void nrf_fifo_status(void)
{
	FRDM_p p;
			p.cmd=nrf24l01_R_REGISTER | nrf24l01_FIFO_STATUS;
			p.data[0]=0xFF;
			p.length=1;
			nrf_cmd_send(&p);
}

void nrf_rd_addr_p0(void)
{
	FRDM_p p;
			p.cmd=nrf24l01_R_REGISTER | nrf24l01_RX_ADDR_P0;
			p.data[0]=0xFF;
			p.data[1]=0xFF;
			p.data[2]=0xFF;
			p.data[3]=0xFF;
			p.data[4]=0xFF;
			p.length=5;
			nrf_cmd_send(&p);
}
