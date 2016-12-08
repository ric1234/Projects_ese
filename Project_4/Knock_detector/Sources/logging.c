/*
 * logging.c

 *
 *  Created on: Dec 7, 2016
 *      Author: richa
 */
#include "main.h"

/****The function Prints out the important data on UART****/
void alert(float Axis_value)
{
	extern volatile int seconds_rtc;
	extern int old_time, new_time;
	unsigned char time_difference_ascii[10];
	char time_difference;
	uint16_t num;
	unsigned char * time_difference_ascii_ptr=&time_difference_ascii[0];

	                    print("\n \r \t \t  !!!! ALERT !!!!");                  //Alert messages
						print("\n \r Excess knocking in the engine");
	                    print("\n\r The knocking value is : ");
						ftoa(Axis_value,&Zout_14_bit_in_ascii,1);                    //Printing the knock value
	                    print("\n \r");
						print_string(&Zout_14_bit_in_ascii,4);
						/***************************************/
						print("\n\r The engine temperature is : ");
						 ptr_temp_calc= &temp_calc;
						(*ptr_temp_calc)();                            // Calling the function to give the current engine knock value
						/*****************************************/
						old_time=new_time;
						new_time=seconds_rtc;
						time_difference=new_time-old_time;            //calculating time difference between two knocks
						num=my_itoa(&time_difference_ascii[0],time_difference);
						print("\n\r Seconds since last knock:");
						print_string(&time_difference_ascii[0],num);
						print("seconds\n");
						delay_ms(500);
}

