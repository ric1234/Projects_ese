/*
 * rtc.h
 *
 *  Created on: Dec 6, 2016
 *      Author: richa
 */

#ifndef INCLUDES_RTC_H_
#define INCLUDES_RTC_H_

#include "MKL25Z4.h"


void Clock_Configuration (void);
void rtc_init();
unsigned char hex_to_ascii(unsigned char hex_value, unsigned char * out);
void rtc_start();


#endif /* INCLUDES_RTC_H_ */
