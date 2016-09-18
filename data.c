#include <stdio.h>
#include <stdint.h>
#include "data.h"

void dump_memory(uint8_t * start, uint32_t length)
{
  int i;
   for(i=0;i<length;i++)
    {
        printf("%x\t",*start); //printing out the hex values of the memory places
        start++;
    }
}

uint32_t big_to_little(uint32_t data)
{
 data=((num>>24)&0xff) //moves bits 24 places right and removes first 8 bits
  |((num<<8)&0xff0000) //moves bits 8 places left and removes 16 to 24 bits
  |((num>>8)&0xff00) //moves bits 8 places right and removes 8 to 16 bits
  |((num<<24)&0xff000000); // moves bits 24 places left and removes last 8 bits
  // ORing all of them gives the new 32bits reversed, which finishes the conversion
    return data;
}

uint32_t little_to_bit(uint32_t data)
{
 
 data=((num>>24)&0xff) //moves bits 24 places right and removes first 8 bits
  |((num<<8)&0xff0000) //moves bits 8 places left and removes 16 to 24 bits
  |((num>>8)&0xff00) //moves bits 8 places right and removes 8 to 16 bits
  |((num<<24)&0xff000000); // moves bits 24 places left and removes last 8 bits
  // ORing all of them gives the new 32bits reversed, which finishes the conversion
    return data;
}

int32_t my_atoi(int8_t * str) //getting the pointer to first character
{
  int32_t* whole; //32 bit interger pointer
   whole=(int32_t*)str; //type casting 8bit pointer to 16 bit
   return *whole; //returning 32 bits
}




