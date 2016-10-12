/*
 * processing.c
 *
 * Created on: Sept 10, 2016
 *     Author: Richard Noronha and Omkar Purandare
 *  University:University of Colorado Boulder
 *      Course: ECEN Fall 2016
 */
/*Description:*/
#include <stdio.h>
#include <stdint.h>
#include "main.h"
void processing()
{
	int32_t len=0,i,Arch,size;
	char transfer[20];         //defining an array where you can store your string
	char *b=transfer;
	float n = 233.007;
	ftoa(n, transfer, 3);      //calling ftoa function
	while(*b!='\0')            //calculating length of the string
		{
			len++;
			b++;
		}
	size=sizeof(char);   //Calculating the size of the data type being transfered
	#ifdef FRDM          //Determining architecture
	Arch=1;
	#endif
	#ifdef BBB
	Arch=2;
	#endif
	#if LOGGER             //option to use logger
	log_1(transfer,len,Arch,size);  //passing parameters to log_1
	#else
	print_string(logger.log_data, logger.length);
	#endif
}

 





