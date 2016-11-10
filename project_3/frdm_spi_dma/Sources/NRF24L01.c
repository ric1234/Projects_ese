/*
 * NRF24L01.c
 *
 *  Created on: Oct 27, 2016
 *      Author: Richard Noronha and Omkar Purandare
 *      Description: This file contains all the functions related to the NRF24L01+ module
 */
#include "NRF24L01.h"

//This function is the link betweeen the NRF module and the SPI interface
void nrf_cmd_send(FRDM_p * p)
{
	char c;
	int i;
	uint8_t * ptr = (uint8_t *) p;
	CSN_OFF;									//Chip select is off to enable the NRF module
	//Send only the bytes that have data. This is found by controlling the for loop
	for(i=0; i<((sizeof(FRDM_p))-sizeof(p->length)-(MAX_SIZE-p->length)); i++)
	{
		c=spi_tx(ptr);
		ptr++;
	}
	CSN_ON;										//Chip select is off to disable NRF module after writing to it
}
/***********************************************************************************************/
//This function is used to configure the NRF module as a transmitter
void nrf_config_tx(void)
{
	FRDM_p p;
	p.cmd = nrf24l01_W_REGISTER | nrf24l01_CONFIG;					//Write to config register
	p.data[0]=nrf24l01_CONFIG_PWR_UP;								//The data to be written is sent here
	p.length=1;														//This is the length of the data
	nrf_cmd_send(&p);
}

//This function is used read the config register
void nrf_config_read(void)
{
	FRDM_p p;
	p.cmd = nrf24l01_R_REGISTER | nrf24l01_CONFIG;						//Read from the config register
	p.data[0]=0xFF;														//dummy byte while the MISO writes the data out
	p.length=1;
	nrf_cmd_send(&p);
}

//This function is used to configure the read register
void nrf_config_rx(void)
{
	FRDM_p p;
	p.cmd=nrf24l01_W_REGISTER | nrf24l01_CONFIG;						//Write to config register
	p.data[0]=nrf24l01_CONFIG_PWR_UP | nrf24l01_CONFIG_PRIM_RX;			//Data to be written.
	p.length=1;
	nrf_cmd_send(&p);
	CE_OFF; //to enable sensing on the antenna
}

//This is the function to check the status of the NRF
void nrf_status(void)
{
	FRDM_p p;
	p.cmd=nrf24l01_NOP;													//NOP is written to get only status on MISO
	p.length=0;
	nrf_cmd_send(&p);
}

//This function to to write an address to the Transmitter
void nrf_tx_write(void)
{
	FRDM_p p;
	p.cmd=nrf24l01_W_REGISTER | nrf24l01_TX_ADDR;					//Write to tx register
	p.data[0]=0x35;													//Random addresses
	p.data[1]=0xAA;
	p.length=2;
	nrf_cmd_send(&p);
}

//This function is to read what is written in the transmitter address register
void nrf_tx_read(void)
{
	FRDM_p p;
	p.cmd=nrf24l01_R_REGISTER | nrf24l01_TX_ADDR;
	p.data[0]=0xFF;
	p.data[1]=0xFF;
	p.length=2;
	nrf_cmd_send(&p);
}

//This function to setup the RF module
void nrf_rf_setup_write(void)
{
	FRDM_p p;
	p.cmd=nrf24l01_W_REGISTER | nrf24l01_RF_SETUP;
	p.data[0]=0x0D;													//RF Power in -6dbm mode
	p.length=1;
	nrf_cmd_send(&p);
}

//This function is to read the rf status register
void nrf_rf_setup_read(void)
{
	FRDM_p p;
	p.cmd=nrf24l01_R_REGISTER | nrf24l01_RF_SETUP;
	p.data[0]=0xFF;
	p.length=1;
	nrf_cmd_send(&p);
}

//This function reads the fifo status
void nrf_fifo_status(void)
{
	FRDM_p p;
	p.cmd=nrf24l01_R_REGISTER | nrf24l01_FIFO_STATUS;
	p.data[0]=0xFF;
	p.length=1;
	nrf_cmd_send(&p);
}

//This function writes the payload onto the transmitter
void nrf_tx_fifo(void)
{
	CE_OFF;						//Enable the transmitter
	FRDM_p p;
	p.cmd=nrf24l01_W_TX_PAYLOAD;
	p.data[0]=0x11;				//Max fifo is 3 levels deep
	p.data[1]=0xAA;
	p.data[2]=0x33;
	p.length=3;
	nrf_cmd_send(&p);

	//CE_ON;
	//delay_us(10);
	//CE_OFF;
}

//This function reads the payload received
void nrf_rx_fifo(void)
{
	FRDM_p p;
	p.cmd=nrf24l01_R_RX_PAYLOAD;
	//Number of dummy bytes is same as payload width of the pipe used
	p.data[0]=0xFF;
	p.data[1]=0xFF;
	p.data[2]=0xFF;
	p.length=3;
	nrf_cmd_send(&p);
}

//This function flushes out the transmit fifo
void nrf_flush_tx(void)
{
	FRDM_p p;
	p.cmd=nrf24l01_FLUSH_TX;
	p.length=0;
	nrf_cmd_send(&p);
}

//This function flushes out the receive fifo
void nrf_flush_rx(void)
{
	FRDM_p p;
	p.cmd=nrf24l01_FLUSH_RX;
	p.length=0;
	nrf_cmd_send(&p);
}

//This funciton reads the address of the pipe0
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
//Configure the receiver to set the CRC0
void nrf_config_rx_crc(void)
{
	FRDM_p p;
	p.cmd=nrf24l01_W_REGISTER | nrf24l01_CONFIG;
	p.data[0]=nrf24l01_CONFIG_EN_CRC | nrf24l01_CONFIG_CRCO | nrf24l01_CONFIG_PWR_UP | nrf24l01_CONFIG_PRIM_RX;
	p.length=1;
	nrf_cmd_send(&p);
}

//setup the Dynamic payload
void nrf_dynpd(void)
{
	FRDM_p p;
	p.cmd=nrf24l01_W_REGISTER | nrf24l01_DYNPD;
	p.data[0]=0x00;
	p.length=1;
	nrf_cmd_send(&p);
}

//Write to the status
void nrf_status_dr(void)
{
	FRDM_p p;
	p.cmd=nrf24l01_W_REGISTER | nrf24l01_STATUS;
	p.data[0]=0x7E;			//Rx_dr tx_ds max_rt all set
	p.length=1;
	nrf_cmd_send(&p);
}

//This sets the radio channels as 76
void nrf_channel(void)
{
	FRDM_p p;
	p.cmd=nrf24l01_W_REGISTER | nrf24l01_RF_CH;
	p.data[0]=0x4C;								//set the rf channel as 76
	p.length=1;
	nrf_cmd_send(&p);
}

//This reads the rx payload
void nrf_r_rx_payload(void)
{
	FRDM_p p;
	p.cmd=nrf24l01_R_RX_PAYLOAD;
	p.data[0]=0xFF;
	p.length=1;
	nrf_cmd_send(&p);
}


//This function turns off the auto ack to make comapatible with the other nrf
void disable_autoack(void)
{
	FRDM_p p;
	p.cmd=nrf24l01_W_REGISTER | nrf24l01_EN_AA;
	p.data[0]=0x00;
	p.length=1;
	nrf_cmd_send(&p);
}

//This fucntion is to setup the address width
void setup_address_witdh(void)
{
	FRDM_p p;
	p.cmd=nrf24l01_W_REGISTER | nrf24l01_SETUP_AW;
	p.data[0]=0x03;									//addres width is 5 bytes
	p.length=1;
	nrf_cmd_send(&p);
}

//This funciton is to set the data rate
void setup_data_rate(void)
{
	FRDM_p p;
	p.cmd=nrf24l01_W_REGISTER | nrf24l01_RF_SETUP;
	p.data[0]=0x07;													//data rate is 1 mbps
	p.length=1;
	nrf_cmd_send(&p);
}

//This sets the pipe width
void setup_pipe_width_p0(void)
{
	FRDM_p p;
	p.cmd=nrf24l01_W_REGISTER | nrf24l01_RX_PW_P0;
	p.data[0]=0x01;												//width is 1 byte
	p.length=1;
	nrf_cmd_send(&p);
}

/********************************************************************************************/
//This is the setrup to configure the NRF module in the receive mode
void nrf_air_rx(void)
{
	CE_OFF; 											//to disable sensing on the antenna
	CSN_ON;
	nrf_config_rx_crc();								//prim_rx,pwrup,crc0=2 bytes,ea_rr
	disable_autoack();
	//address width is 5bytes
	setup_address_witdh();
	//set channel(76): write reg RF_CH with 76=0x4C
	nrf_channel();
	//Set data rate at 1Mbps
	setup_data_rate();
	//Power level
	//Payload width=1byte
	setup_pipe_width_p0();
	//write_register DYNPD, 0
	//nrf_dynpd();
	//write_register Status : rx_dr, txds, Max_rt=1
	//nrf_status_dr();
	//flush_rx();
	nrf_flush_rx();
	//flush_tx();
	nrf_flush_tx();

	CE_ON;
	delay_us(130);

	//read payload:
	//nrf_r_rx_payload();
	//to check read fifo_status & rx_empty

}

/**********************************************************************************************/
//This is the function to test the basic functionality of the nrf
void nrf_test(void)
{
	nrf_config_rx();
	nrf_config_read();
	nrf_status();
	nrf_tx_write();
	nrf_tx_read();
	nrf_rf_setup_write();
	nrf_rf_setup_read();

	nrf_flush_tx();
	nrf_fifo_status();
	nrf_config_tx();
	nrf_tx_fifo();
	nrf_fifo_status();
	delay_us(250);
}
