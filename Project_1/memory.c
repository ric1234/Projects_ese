#include <stdio.h>
#include <stdint.h>
#include "memory.h"
int8_t my_memmove(uint8_t * src, uint8_t * dst, uint32_t length)
{
   int i; 
   if(dst<src) /*address of destination is before the source*/
    {
      for(i=0;i<length;i++) 
      {
         *dst = *src; /*copy directly*/
         src++;
         dst++;
      }
     return 0;
    }
  else if(dst>src) /*address of destination is after the source*/
  {
     src= src+length-1;
     dst= dst+length-1;
     for(i=0;i<length;i++)
    {
       *dst = *src; //copying contents and move back
        src--;
        dst--;
    }
    return 0;
   }
  else
  {
    printf("Error\n"); //error if destiantion and source are the same
    return 1;
  }
   
}


int8_t my_memzero(uint8_t * src, uint32_t length)
 {
    int i;
    if(length<=0) //error for invalid length
    {
      printf("error\n");
      return 1;
    }
   else
    {
      for(i=0;i<length;i++) //changing locations from the memory location to 0
      {
       *src = 0;
        src++;
      }
     return 0;
    }
  
 } 

int8_t my_reverse(uint8_t * src, uint32_t length)
  {
     int i,temp;
     if(length%2==0) //checking if length to convert is even
     {
       for(i=0;i<length/2;i++) //reversing by exchanging first and second half elements
       {
         temp=*(src+i);
         *(src+i)=*(src+length-i-1);
         *(src+length-i-1)=temp;
       }
       return 0;
     }
    else if(length%2!=0) //checking if length to convert is odd
     {
       for(i=0;i<(length-1)/2;i++) //reversing by exchanging first and second half elements
       {
         temp=*(src+i);
         *(src+i)=*(src+length-i-1);
         *(src+length-i-1)=temp;
       }
       return 0;
     }
    else
     {
      printf("Error\n"); //Error if negetive length
      return 1;
     }
  }


