/*
 * buffertest.c
 *
* Created on: Oct 10, 2016
 *     Author: Richard Noronha and Omkar Purandare
 *  University:University of Colorado Boulder
 *      Course: ECEN Fall 2016
 *      */
/*Description: This file contains all the functions to implement the circular buffer*/
#include<stdio.h>
#include<stdint.h>
#include"main.h"
#include"circbuff.h"

int tests()

{
	int i,j,l=5,passes=0,fails=0;
	CB c,*b;																//c is the Circular buffer instance and b is its pointer
	State s;																//s is the enum State
	b=&c;
	print("***TESTING OF THE CIRCULARBUFFER FUCTIONS BEGINS***\n");			//Print output on the terminal

	c.circ_buffer=allocate(c,l);											//Allocate memory to circular buffer
	print("\rAllocate..pass\n");
	passes=passes+1;														//Number of trues
	begin(&c,l);															//The part of beinning the circular buffer



	for(i=0;i<5;i++)														//Add 5 items for the test
		{
		s = add_Item( &c, i);

		}
	if(s==Buffer_available)													//If the buffer is available, print that it has passed the test
		{
		print("\rAdd...pass\n");
		passes=passes+1;
		}
	else if(s==Buffer_full)													//If the buffer is not available, print that it has passed the test
		{
		print("\rAdd...fail\n");
		fails=fails+1;
		}

	for(i=0;i<l;i++)														//Perform a remove item
		{
		s = rem_Item(&c);
		}
	if(s==Buffer_available || Buffer_full)									//If the buffer is available or full, print that it has passed the test
		{
		print("\rRemove...pass\n");
		passes=passes+1;
		}
	else																	//If the buffer is not available nor full, print that it has passed the test
		{
		print("\rRemove...fail\n");
		fails=fails+1;
		}

/*Empty buffer testing*/
	s = check_Buff_empty(&c);												//Assign the state for empty buffer

	if(s==Buffer_available || Buffer_full)									//If the buffer is available or full, print that it has failed the test
		{
		print("\rEmpty...fail\n");
		fails=fails+1;
		}
	else if(s==Buffer_empty)												//If the buffer is empty, print that it has passed the test
		{
		print("\rEmpty...pass\n");
		passes=passes+1;
		}

	s = check_Buff_Full(&c,(c.head)+1);
	if(s==Buffer_available || Buffer_empty)
		{
		print("\rFull...fail\n");
		fails=fails+1;
		}
	else if(s==Buffer_full)
		{
		print("\rFull...pass\n");
		passes=passes+1;
		}

	Destroy(c);																//Frees memory from the heap. Necessary for the malloc()

/*Print the pass or fails*/
	for(j=0;j<l;j++)
		{
			b->circ_buffer++;
		}
	print("\rDestroy..pass\n");
	passes=passes+1;



	printf("Total fails=%d\n",fails);
	printf("Total Passes=%d\n",passes);

}



