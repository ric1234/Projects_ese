/*
 * uart.h
 *
 *  Created on: Oct 7, 2016
 *      Author: richa
 */

#ifndef SOURCES_UART_H_
#define SOURCES_UART_H_

void uart0_init(void);
void uart0_tx(void);
void uart0_rx(void);
void print_string(char *ptr_str, uint32_t len);
void print_stringl(char *ptr);


#endif /* SOURCES_UART_H_ */
