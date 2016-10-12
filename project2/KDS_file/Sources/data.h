/*
 * data.h
 *
 * * Created on: Oct 7, 2016
 *     Author: Richard Noronha and Omkar Purandare
 *  University:University of Colorado Boulder
 *      Course: ECEN Fall 2016
 */

#ifndef SOURCES_DATA_H_
#define SOURCES_DATA_H_

#include "MKL25Z4.h"
#include "gpio.h"
#include "rgb_pwm_init.h"
#include "main.h"

void send_data(char character);
int receive_data(char* c);
void led_pwm(void);

extern char color;
#endif /* SOURCES_DATA_H_ */
