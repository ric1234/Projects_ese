/*
 * rtc.h
 *
 *  Created on: Dec 6, 2016
 *      Author: richa
 */

#ifndef INCLUDES_RTC_H_
#define INCLUDES_RTC_H_

#include "MKL25Z4.h"
#include "ftoa.h"


void Clock_Config_rtc (void);
void rtc_init();
void rtc_start();
void print_rtc();


#endif /* INCLUDES_RTC_H_ */
