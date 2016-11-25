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
#include "spi.h"
#include "delay.h"
#include "accelerometer.h"
#include "i2c.h"

void dma_initialization(void);





#endif /* INCLUDES_MAIN_H_ */
