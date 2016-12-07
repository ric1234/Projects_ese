/*
 * main.h
 *
 *  Created on: 27-Oct-2016
 *      Author: omkar
 */

#ifndef INCLUDES_MAIN_H_
#define INCLUDES_MAIN_H_
#define FRDM
#ifdef BBB
#define print printf
#endif
#ifdef FRDM
#define print print_stringl
#endif

#include <stdio.h>
#include "MKL25Z4.h"
#include "uart.h"
#include "io.h"
#include "profile.h"
#include "message.h"
#include"colors.h"
#include"rgb_pwm_init.h"
#include"ftoa.h"
#include"dma.h"
#include "adc.h"
#include "delay.h"
#include "accelerometer.h"
#include "i2c.h"
#include "rtc.h"

volatile int seconds_rtc, minutes_rtc;
volatile uint8_t interrupt_rtc;

void dma_initialization(void);





#endif /* INCLUDES_MAIN_H_ */
