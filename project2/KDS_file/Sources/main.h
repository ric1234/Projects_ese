/*
 * main.h
 *
 *  Created on: Oct 8, 2016
 *      Author: richa
 */

#ifndef SOURCES_MAIN_H_
#define SOURCES_MAIN_H_

#define FRDM
#ifdef BBB
#define print printf
#endif
#ifdef FRDM
#define print print_stringl
#endif
#include "MKL25Z4.h"
#include "uart.h"
#include "data.h"
#include "gpio.h"
#include "pwm.h"
#include "rgb_pwm_init.h"
#include "profile.h"
#include "circbuff.h"
#include "ftoa.h"
#include "log.h"

 int BRIGHTNESS;
int COUNT;
void processing();
int tests();


#endif /* SOURCES_MAIN_H_ */
