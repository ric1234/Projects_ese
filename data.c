#include <stdio.h>
#include <stdint.h>
#include "data.h"

void dump_memory(uint8_t * start, uint32_t length)
{
  int i;
   for(i=0;i<length;i++)
    {
        printf("%x\t",*start);
        start++;
    }
}

uint32_t big_to_little(uint32_t data)
{
 uint8_t * start1,temp,i,j;
    j=(uint8_t)data;
    start1=&j;
    for(i=0;i<2;i++)
    {
        temp=*(start1+i);
     *(start1+i)=*(start1+3-i);
     *(start1+3-i)=temp;
        start1++;
    }
    return data;
}

uint32_t little_to_bit(uint32_t data)
{
 uint8_t * start2,temp,i,j;
    j=(uint8_t)data;
    start2=&j;
    for(i=0;i<2;i++)
    {
        temp=*(start2+i);
     *(start2+i)=*(start2+3-i);
     *(start2+3-i)=temp;
        start2++;
    }
    return data;
}

int32_t my_atoi(int8_t * str)
{
  int32_t* whole,j;
   whole=(int32_t*)str;
   return *whole;
}




