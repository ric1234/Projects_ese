/*
 * adc.h
 *
 *  Created on: 20-Nov-2016
 *      Author: omkar
 */

#ifndef INCLUDES_ADC_H_
#define INCLUDES_ADC_H_

 uint16_t adc_temperature(void);
 float temp_calc();
 float (*ptr_temp_calc)();
 float Temp_conv (float a);

#endif /* INCLUDES_ADC_H_ */
