/*
 * main.h
 *
 * Created on: Sept 26, 2016
 *     Author: Richard Noronha and Omkar Purandare
 *  University:University of Colorado Boulder
 *      Course: ECEN Fall 2016
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
#include "rgb_pwm_init.h"
#include "profile.h"
#include "circbuff.h"
#include "ftoa.h"
#include "log.h"
#include "colors.h"

int BRIGHTNESS;
char color;
void processing();
int tests();


#endif /* SOURCES_MAIN_H_ */
