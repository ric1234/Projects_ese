/*
 * Circbuff_UART.c
 *
 * Created on: Oct 7, 2016
 *     Author: Richard Noronha and Omkar Purandare
 *  University:University of Colorado Boulder
 *      Course: ECEN Fall 2016
 */
/*Description: This file contains the functions that initialize and operate on the circular buffer*/

#include "circbuff.h"

void begin(CB *cb1,size_t len)
	{
		cb1->head=cb1->circ_buffer;									//Move the pointer of the base to the head
		cb1->tail=cb1->circ_buffer;									//Move the pointer of the base to the tail too. Head, base and tail point to
																	//same memory location
		cb1->Length=cb1->circ_buffer+(len);							//Length of the buffer
		cb1->num_items=0;											//Initialize number of errors as 0
	}

State check_Buff_Full(CB * cb, uint8_t * ahead)
	{

		 if(ahead == (cb-> tail))									//Buffer full if next the tail is after the head
			 return Buffer_full;

		 else
			 return Buffer_available;								//Otherwise the buffer is available
	}

State check_Buff_empty(CB * cb)
	{
		 if(cb->head == cb->tail)                                   //Buffer empty if head and tail point to same data
			  return Buffer_empty;
		 else
			  return Buffer_available;
	}

State add_Item(CB * cb, uint8_t data)
	{
		State status;
		uint8_t *next = (cb -> head)+1;

		if (next >= cb->Length)										//If the buffer is full
			next = cb->circ_buffer;                 				//Wrap around to circ_buffer

		*(cb->head)=data;											//Pass the data to the head
		status=check_Buff_Full(cb, next);							//Output the buffer to the status
		/*Check buffer status*/
		if(status==Buffer_full)
			{
				return Buffer_full;
			}
		/*Adding the data to Head*/
		cb->head = next;                                             //Incrementing the pointer of head

		return Buffer_available;
	}

uint8_t rem_Item(CB * cb)
	{
		State status;                                               //State of buffer
		uint8_t data;
		uint8_t *next = cb -> tail+1;               		        //Points to the next value after tail
		if (next >= cb->Length)						               //Check if tail is on the edge
			next =cb->circ_buffer;

		/*Checks for empty buffer*/
		status=check_Buff_empty(cb);
		if(status==Buffer_empty)
			{
				return 0;
			}
		else														//Extracts data from the tail
			{
			data=*(cb->tail);
			*(cb->tail)=0;
			}
		cb->tail = next;											//Moves the pointer ahead
		return data;
	}

/*Allcocates memory*/
void*allocate(CB cb,uint8_t len)
	{
		return cb.circ_buffer = malloc(len*sizeof(uint8_t));
	}
/*Frees the memory heap after Malloc()*/
void Destroy(CB cb)
	{
		free(cb.circ_buffer);
	}
