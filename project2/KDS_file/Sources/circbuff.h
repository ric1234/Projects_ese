/*
 * circbuff.h
 *
 *  Created on: 10-Oct-2016
 *      Author: omkar
 */

#ifndef SOURCES_CIRCBUFF_H_
#define SOURCES_CIRCBUFF_H_

#include<stdint.h>
#include <stdlib.h>
void circBuff ();
typedef enum

{

                Buffer_full = 0,

                Buffer_empty = 1,

                Buffer_available = 2,

}State;



typedef struct

{

                uint8_t * circ_buffer;

                uint8_t * head;

                uint8_t * tail;

                uint8_t * Length;

                size_t num_items;

}CB;



State check_Buff_Full(CB * cb,uint8_t * ahead);                               //define function for full buffer

State check_Buff_empty(CB * cb);                                          //define function for empty buffer

State add_Item(CB * cb, uint8_t data);                              //define function for adding item

uint8_t rem_Item(CB * cb);                           //define function for removing item

void begin(CB *cb1,size_t len);

void* allocate(CB cb,uint8_t len);

void Destroy(CB cb);

#endif




