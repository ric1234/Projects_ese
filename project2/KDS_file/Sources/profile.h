/*
 * profile.h
 *
 *  Created on: Oct 9, 2016
 *       *      Author: Richard Noronha and Omkar Purandare
 *  University:University of Colorado Boulder
 *      Course: ECEN Fall 2016
 */

#ifndef SOURCES_PROFILE_H_
#define SOURCES_PROFILE_H_

#include "MKL25Z4.h"
#include "gpio.h"
#include "ftoa.h"
#include "main.h"

void profile_timer_init(void);
void timer_check(void);
void timer_on(void);
void timer_off(void);
float timer_calculate(void);
void timer_print(void);
void timer_reset(void);

#endif /* SOURCES_PROFILE_H_ */
