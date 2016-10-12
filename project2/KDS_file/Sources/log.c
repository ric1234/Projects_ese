/*
 * log.c
 *
 * Created on: Oct 8, 2016
 *     Author: Richard Noronha and Omkar Purandare
 *  University:University of Colorado Boulder
 *      Course: ECEN Fall 2016
 */
#include "log.h"

void log_0(char* data, uint32_t l)
{
	/*the logger is described as the a structure*/
	char*b;
	int i;
	for(i=0;i<l;i++)  /*transfering the string into logger*/
	{
		logger.log_data[i]=*data;
		data++;
	}
	b=logger.log_data;
	logger.length=l;    /*storing length in logger*/
#ifdef BBB
for(i=0;i<logger.length;i++)
	{
	printf("%c",*b);
	b++;
	}
printf("\n");
#endif

#ifdef FRDM
	print_string(logger.log_data, logger.length);
#endif
}

void log_1(char* data, uint32_t l,uint32_t arch,uint32_t size)
{
	char*b;
	int i;
	for(i=0;i<l;i++)                    /*transfering the string into logger*/
		{
			logger.log_data[i]=*data;
			data++;
		}
	b=logger.log_data;
	logger.length=l;             /*storing length in logger*/
	logger.DataType_size=size;  //storing data type size
	logger.Architecture= arch;  //storing the architecture type for which code is compiled
	if(logger.Architecture==1)
		Arc=KL25Z;                //using enum to determine the board
	else
		Arc=Beagle;

	logger.DataType_size=size;
#ifdef BBB
	for(i=0;i<logger.length;i++)
	{
		printf("%c",*b);
		b++;
	}
	printf("\n");
#endif

#ifdef FRDM
	print_string(logger.log_data, logger.length);
#endif
}
