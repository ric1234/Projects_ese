/*
 * rgb_pwm_init.h
 *
 *  Created on: 03-Nov-2016
 *      Author: omkar
 */

#ifndef INCLUDES_RGB_PWM_INIT_H_
#define INCLUDES_RGB_PWM_INIT_H_

void rgb_pwm_init(void);
#define RED				(18)
#define RED_SHIFT		(1 << 18)
#define GREEN			(19)
#define GREEN_SHIFT		(1 << 19)
#define BLUE			(1)
#define BLUE_SHIFT		(1 << 1)


#endif /* INCLUDES_RGB_PWM_INIT_H_ */
