/*
 * logging.c

 *
 *  Created on: Dec 7, 2016
 *      Author: Richard Noronha and Omkar Purandare
 */
#include "main.h"

/****The function Prints out the important data on UART****/
void alert(float Axis_value)
{
	float Tempf;
	extern volatile int seconds_rtc;
	extern int old_time, new_time,structure_item;
	unsigned char time_difference_ascii[10];
	char time_difference;
	char transfer[20];
	char *b=transfer;
	uint16_t num,len=0;
	extern Information info;
	Information* info_ptr=&info;
	unsigned char * time_difference_ascii_ptr=&time_difference_ascii[0];

	print("\n \r \t \t  !!!! ALERT !!!!");                  //Alert messages
	(info_ptr->Knock[structure_item])=Axis_value;
	print("\n \r Excess knocking in the engine");
	print("\n\r The knocking value is: ");
	ftoa(Axis_value,&Zout_14_bit_in_ascii,1);                    //Printing the knock value
	print("\t");
	print_string(&Zout_14_bit_in_ascii,4);
	/***************************************/
	print("\n\r The engine temperature is: ");
	 ptr_temp_calc= &temp_calc;
	Tempf=(*ptr_temp_calc)();                            // Calling the function to give the current engine knock value
	 (info_ptr->Temp[structure_item])=Tempf;
	print("\t");
		ftoa(Tempf, transfer, 2);
			while(*b!='\0')       								//Printing out the temperature
			  {
				  len++;
				  b++;
			  }
			print_string(transfer, len);
			print("C");
	/*****************************************/
	old_time=new_time;
	new_time=seconds_rtc;
	time_difference=new_time-old_time;            //calculating time difference between two knocks
	(info_ptr->time[structure_item])=time_difference;
	num=my_itoa(&time_difference_ascii[0],time_difference);
	print("\n\r Seconds since last knock:");
	print_string(&time_difference_ascii[0],num);
	print("seconds\n");
	delay_ms(500);
	structure_item = structure_item +1;
}

