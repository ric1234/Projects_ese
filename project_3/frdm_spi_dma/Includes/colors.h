/*
 * colors.h
 *
 *  Created on: Oct 11, 2016
  *    	Author: Richard Noronha and Omkar Purandare
 *  University:University of Colorado Boulder
 *      Course: ECEN Fall 2016
 */

#ifndef SOURCES_COLORS_H_
#define SOURCES_COLORS_H_


void red(void);
void green(void);
void blue(void);
void red_brightness(uint32_t BRIGHTNESS);
void green_brightness(uint32_t BRIGHTNESS);
void blue_brightness(uint32_t BRIGHTNESS);
void red_off(void);
void green_off(void);
void blue_off(void);
extern int BRIGHTNESS;

#endif /* SOURCES_COLORS_H_ */
