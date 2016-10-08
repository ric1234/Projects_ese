#include <stdio.h>
#include <stdint.h>
int8_t my_memzero(uint8_t * src, uint32_t length);
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
 k = my_memzero(aptr_3,16); //apending zeros by calling function
 printf("The formated string is:\n");
 for(i=0;i<=31;i++)    //printing out the entire string
  {
    printf("%d\t",*aptr_1);
    aptr_1++;
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


  
 


