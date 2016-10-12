/*
 * uart.h
 *
 *  Created on: Oct 7, 2016
 *      Author: Richard and Omkar
 *  University:University of Colorado Boulder
 *      Course: ECEN Fall 2016*/

#ifndef SOURCES_UART_H_
#define SOURCES_UART_H_

#include "MKL25Z4.h"
#include "colors.h"

void uart0_init(void);
void uart0_tx(void);
void uart0_rx(void);
void print_string(char *ptr_str, uint32_t len);
void print_stringl(char *ptr);

#endif /* SOURCES_UART_H_ */
