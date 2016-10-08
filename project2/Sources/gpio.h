/*
 * gpio.h
 *
 *  Created on: Oct 6, 2016
 *      Author: richa
 */

#ifndef SOURCES_GPIO_H_
#define SOURCES_GPIO_H_
#include "MKL25Z4.h"

#define PIN(x)			1 << x

#define RED				(18)
#define RED_SHIFT		(1 << 18)
#define GREEN			(19)
#define GREEN_SHIFT		(1 << 19)
#define BLUE			(1)
#define BLUE_SHIFT		(1 << 1)

#define RED_OFF			(GPIOB_PSOR = RED_SHIFT)
#define RED_ON			(GPIOB_PCOR = RED_SHIFT)
#define RED_TOGGLE		(GPIOB_PTOR = RED_SHIFT)

#define GREEN_OFF		(GPIOB_PSOR = GREEN_SHIFT)
#define GREEN_ON		(GPIOB_PCOR = GREEN_SHIFT)
#define GREEN_TOGGLE	(GPIOB_PTOR = GREEN_SHIFT)

#define BLUE_OFF		(GPIOD_PSOR = BLUE_SHIFT)
#define BLUE_ON			(GPIOD_PCOR = BLUE_SHIFT)
#define BLUE_TOGGLE		(GPIOD_PTOR = BLUE_SHIFT)
void rgb_init(void);
#endif /* SOURCES_GPIO_H_ */
