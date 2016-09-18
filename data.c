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
 data=((data>>24)&0xff) //moves bits 24 places right and removes first 8 bits
  |((data<<8)&0xff0000) //moves bits 8 places left and removes 16 to 24 bits
  |((data>>8)&0xff00) //moves bits 8 places right and removes 8 to 16 bits
  |((data<<24)&0xff000000); // moves bits 24 places left and removes last 8 bits
  // ORing all of them gives the new 32bits reversed, which finishes the conversion
    return data;
}




uint32_t little_to_bit(uint32_t data)
{
 
 data=((data>>24)&0xff) //moves bits 24 places right and removes first 8 bits
  |((data<<8)&0xff0000) //moves bits 8 places left and removes 16 to 24 bits
  |((data>>8)&0xff00) //moves bits 8 places right and removes 8 to 16 bits
  |((data<<24)&0xff000000); // moves bits 24 places left and removes last 8 bits
  // ORing all of them gives the new 32bits reversed, which finishes the conversion
    return data;
}




int32_t my_atoi(int8_t * str) //getting the pointer to first character
{
  int32_t* whole; //32 bit interger pointer
   whole=(int32_t*)str; //type casting 8bit pointer to 16 bit
   return *whole; //returning 32 bits
}



int8_t * my_itoa(int8_t * str, int32_t data, int32_t base)
{
 
 int n=0;
 if (base==2) //user gives base as 2
 {
    while(data!=0)  //Using traditional divding way to get binary
    {
      *str= data%2;  //dividing by 2 multiple times and storing reminders to get bits
      data= data/2;  
      str++;
      n++;
    }
    str= str-n;
    return str;
  }
  else if(base==10) //user gives base as 10
  {
   while(data!=0) //Using traditional divding way to get integers seperately
   {
     *str= data%10; //dividing by 10 multiple times and storing reminders to get each integer
     data= data/10;
     str++;
     n++;
   }
   str= str-n;
   return str;
 }
 else if(base==8) //user gives base as 8
 {
   while(data!=0) //Using traditional divding way to get octal digits seperately
   {
     *str= data%8; //dividing by 8 multiple times and storing reminders to get each octal digit
     data= data/8;
     str++;
     n++;
  }
 str= str-n;
 return str;
 }
 else       //user gives base as 8
 {
  while(data!=0) //Using traditional divding way to get hexadecimal digits seperately
  {
    *str= data%16; //dividing by 8 multiple times and storing reminders to get each octal digit
    data= data/16;
    str++;
    n++;
  }
  str= str-n;
  return str;
 }
}



