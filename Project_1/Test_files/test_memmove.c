#include <stdio.h>
#include <stdint.h>
int8_t my_memmove(uint8_t * src, uint8_t * dst, uint32_t length);
void main()
{
  int i,j=0;
  int8_t k;
  uint8_t omi[32]; //intialising array
  uint8_t *aptr_1, *aptr_2, *aptr_3;
  aptr_1= &omi[0]; //intialising pointer at various locations
  aptr_2= &omi[8];
  aptr_3= &omi[16];
  for(i=0;i<=31;i++) //giving first 16 values
  {
     *aptr_1 = j;
     aptr_1++;
     j++;
  }
 aptr_1 = aptr_1 - 32;
  printf("The orignal string is:\n");
 for(i=0;i<=31;i++)    //printing out the entire string
  {
    printf("%d\t",*aptr_1);
    aptr_1++;
  }
 aptr_1 = aptr_1 - 32;
 printf("\n");
 k = my_memmove(aptr_1,aptr_3,8); // calling memmove
 printf("The formated string is:\n");
 for(i=0;i<=31;i++)    //printing out the entire string
  {
    printf("%d\t",*aptr_1);
    aptr_1++;
  }
}

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



  
 


