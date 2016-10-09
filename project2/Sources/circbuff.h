#ifndef _CIRCBUFF_H
#define _MEMORY_H
#include<stdint.h>

typedef enum

{

                Buffer_full,

                Buffer_empty,

                Buffer_available,

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

uint8_t add_Item(CB * cb, uint8_t data);                              //define function for adding item

uint8_t rem_Item(CB * cb);                           //define function for removing item

void begin(CB *cb1,size_t len);

void* allocate(CB cb,uint8_t len);

void Destroy(CB cb);

#endif

