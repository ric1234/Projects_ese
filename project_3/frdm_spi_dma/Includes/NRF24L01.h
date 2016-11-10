/*
 * NRF24L01.c
 *
 *  Created on: Oct 27, 2016
 *      Author: Richard Noronha and Omkar Purandare
 *      Description: This file contains all the functions related to the NRF24L01+ module
 */

#ifndef INCLUDES_NRF24L01_H_
#define INCLUDES_NRF24L01_H_

#include "spi.h"
#include "delay.h"

//SPI command defines
#define nrf24l01_R_REGISTER		0x00
#define nrf24l01_W_REGISTER		0x20
#define nrf24l01_R_RX_PAYLOAD	0x61
#define nrf24l01_W_TX_PAYLOAD	0xA0
#define nrf24l01_FLUSH_TX		0xE1
#define nrf24l01_FLUSH_RX		0xE2
#define nrf24l01_REUSE_TX_PL	0xE3
//Extra features
#define nrf24l01_ACTIVATE		0x50
#define nrf24l01_R_RX_PL_WID	0x60
#define nrf24l01_W_ACK_PAYLOAD	0xA8
#define nrf24l01_WR__TX_PAYLOAD_NOACK	0xB0
#define nrf24l01_NOP			0xFF

/*Register map*/
#define nrf24l01_CONFIG			0x00
#define nrf24l01_EN_AA			0x01
#define nrf24l01_EN_RXADDR		0x02
#define nrf24l01_SETUP_AW		0x03
#define nrf24l01_SETUP_RETR		0x04
#define nrf24l01_RF_CH			0x05
#define nrf24l01_RF_SETUP		0x06
#define nrf24l01_STATUS			0x07
#define nrf24l01_OBSERVE_TX		0x08
#define nrf24l01_CD				0x09
#define nrf24l01_RX_ADDR_P0		0x0A
#define nrf24l01_RX_ADDR_P1		0x0B
#define nrf24l01_RX_ADDR_P2		0x0C
#define nrf24l01_RX_ADDR_P3		0x0D
#define nrf24l01_RX_ADDR_P4		0x0E
#define nrf24l01_RX_ADDR_P5		0x0F
#define nrf24l01_TX_ADDR		0x10
#define nrf24l01_RX_PW_P0		0x11
#define nrf24l01_RX_PW_P1		0x12
#define nrf24l01_RX_PW_P2		0x13
#define nrf24l01_RX_PW_P3		0x14
#define nrf24l01_RX_PW_P4		0x15
#define nrf24l01_RX_PW_P5		0x16
#define nrf24l01_FIFO_STATUS	0x17
#define nrf24l01_DYNPD			0x1C

//CONFIG register bitwise definitions
#define nrf24l01_CONFIG_RESERVED	0x80
#define	nrf24l01_CONFIG_MASK_RX_DR	0x40
#define	nrf24l01_CONFIG_MASK_TX_DS	0x20
#define	nrf24l01_CONFIG_MASK_MAX_RT	0x10
#define	nrf24l01_CONFIG_EN_CRC		0x08
#define	nrf24l01_CONFIG_CRCO		0x04
#define	nrf24l01_CONFIG_PWR_UP		0x02
#define	nrf24l01_CONFIG_PRIM_RX		0x01

/****************************************************************************/
#define MAX_SIZE 10
typedef struct FRDM_Packet{
	uint8_t cmd;
	uint8_t data[MAX_SIZE];
	uint8_t length;
}FRDM_p, * FRDM_p_ptr;

/*****************************************************************************/


void nrf_cmd_send(FRDM_p * p);
void nrf_config_tx(void);
void nrf_config_tx_read(void);
void nrf_config_rx(void);
void nrf_status(void);
void nrf_tx_write(void);
void nrf_tx_read(void);
void nrf_rf_setup_write(void);
void nrf_rf_setup_read(void);
void nrf_fifo_status(void);
void nrf_tx_fifo(void);
void nrf_rx_fifo(void);

void nrf_rx_addr_p1(void);
void nrf_flush_tx(void);
void nrf_rd_addr_p0(void);

void nrf_config_rx_crc(void);
void nrf_dynpd(void);
void nrf_status_dr(void);
void nrf_channel(void);
void nrf_r_rx_payload(void);
void nrf_test(void);
void nrf_air_rx(void);
void disable_autoack(void);
void setup_address_witdh(void);
void setup_data_rate(void);
void setup_pipe_width_p0(void);




#endif /* INCLUDES_NRF24L01_H_ */
