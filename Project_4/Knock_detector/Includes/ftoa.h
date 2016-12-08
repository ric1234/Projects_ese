/*
 * ftoa.h
 *
 *  Created on: 27-Oct-2016
 *      Author: omkar
 */

#ifndef INCLUDES_FTOA_H_
#define INCLUDES_FTOA_H_


void reverse(char *str, int len);
int intToStr(int x, char str[], int d);
void ftoa(float n, char *res, int afterpoint);
int power(int a, int n);
unsigned char hex_to_ascii(unsigned char hex_value, unsigned char * out);
uint16_t my_itoa(char * str, int data);



#endif /* INCLUDES_FTOA_H_ */
