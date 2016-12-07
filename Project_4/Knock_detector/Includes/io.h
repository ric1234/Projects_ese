/*
 * io.h
 *
 *  Created on: 27-Oct-2016
 *      Author: omkar
 */

#ifndef INCLUDES_IO_H_
#define INCLUDES_IO_H_

void send_data(char character);
int receive_data(char* c);
void led_pwm(void);


char receive_data_char_uart1(void);
void send_data_uart1(char character);

void bluutooth_test();


#endif /* INCLUDES_IO_H_ */
