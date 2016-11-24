/*
 * profile.h
 *
 *  Created on: 27-Oct-2016
 *      Author: omkar
 */

#ifndef INCLUDES_PROFILE_H_
#define INCLUDES_PROFILE_H_

#include "MKL25Z4.h"

void profile_timer_init(void);
void timer_check(void);
void timer_on(void);
void timer_off(void);
float timer_calculate(void);
void timer_print(void);
void timer_reset(void);




#endif /* INCLUDES_PROFILE_H_ */
