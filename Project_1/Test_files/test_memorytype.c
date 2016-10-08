#include<stdio.h>
#include<stdint.h>
void dump_memory(uint8_t * start, uint32_t length);
uint32_t big_to_little(uint32_t data);
uint32_t little_to_bit(uint32_t data);
void main()
 {
 uint32_t a=0xDEADBEEF,*c;
 uint8_t *b;
 c=&a;
 b = (uint8_t*)c;
 printf("orignal data:\n");
 dump_memory(b,4);
 a=big_to_little(a);
 printf("\n");
 printf(" After Big to little conversion:\n");
 dump_memory(b,4);
 printf("\n");
 a=little_to_bit(a);
 printf(" After little to big conversion:\n");
 dump_memory(b,4);
 }
  



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

  
