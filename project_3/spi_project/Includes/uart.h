/*
 * uart.h
 *
 *  Created on: 27-Oct-2016
 *      Author: omkar
 */

#ifndef INCLUDES_UART_H_
#define INCLUDES_UART_H_

void uart0_init(void);
void uart0_tx(void);
void uart0_rx(void);
void print_string(char *ptr_str, uint32_t len);
void print_stringl(char *ptr);




#endif /* INCLUDES_UART_H_ */
