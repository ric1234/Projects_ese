#include <stdio.h>
#include <stdint.h>
#include "data.h"

void dump_memory(uint8_t * start, uint32_t length)
{
  int i;
   for(i=0;i<length;i++)
    {
        printf("%x\n",*start);
        start++;
    }
    return 0;
}

uint32_t big_to_little(uint32_t data)
{
 uint8_t * start1,temp,i;
    start1=&data;
    for(i=0;i<2;i++)
    {
        temp=*(start1+i);
     *(start1+i)=*(start1+4-i);
     *(start1+4-i)=temp;
        start1++;
    }
    return data;
}

uint32_t little_to_bit(uint32_t data)
{
 uint8_t * start2,temp,i;
    start2=&data;
    for(i=0;i<2;i++)
    {
        temp=*(start2+i);
     *(start2+i)=*(start2+4-i);
     *(start2+4-i)=temp;
        start2++;
    }
    return data;
}

int32_t my_atoi(int8_t * str)
{
  int32_t* whole;
   whole=str;
   return whole;
}




