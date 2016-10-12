/*
 * circbuff.h
 *
 * Created on: Oct 7, 2016
 *     Author: Richard Noronha and Omkar Purandare
 *  University:University of Colorado Boulder
 *      Course: ECEN Fall 2016
 */

#ifndef SOURCES_CIRCBUFF_H_
#define SOURCES_CIRCBUFF_H_

#include<stdio.h>
#include<stdint.h>
#include<stdint.h>
#include <stdlib.h>
void circBuff ();
typedef enum
	{
                Buffer_full = 0,
                Buffer_empty = 1,
                Buffer_available = 2,
	}State;																//Create an enum for noting the state of the buffer

typedef struct
	{
				uint8_t * circ_buffer;
                uint8_t * head;
                uint8_t * tail;
                uint8_t * Length;
                size_t num_items;
	}CB;																//Defines the Circular buffer

State check_Buff_Full(CB * cb,uint8_t * ahead);                         //Define function for full buffer
State check_Buff_empty(CB * cb);                                        //Define function for empty buffer
State add_Item(CB * cb, uint8_t data);                              	//Define function for adding item
uint8_t rem_Item(CB * cb);                           					//Define function for removing item
void begin(CB *cb1,size_t len);
void* allocate(CB cb,uint8_t len);
void Destroy(CB cb);
#endif
