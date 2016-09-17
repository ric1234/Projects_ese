#include <stdio.h>
#include <stdint.h>
#include "data.h"
#include "memory.h"
#include "project_1.h"
void project_1_report()
{
  int i,j=31;
  int8_t k;
  uint8_t omi[32];
  uint8_t *aptr_1, *aptr_2, *aptr_3;
  aptr_1= &omi[0];
  aptr_2= &omi[8];
  aptr_3= &omi[17];
  for(i=0;i<=15;i++)
  {
     *aptr_1 = j;
     aptr_1++;
     j++;
  }
 aptr_1 = aptr_1 - 16;
 k = my_memzero(aptr_3,16);
 k = my_memmove(aptr_1,aptr_3,8);
 k = my_memmove(aptr_2,aptr_1,16);
 k = my_reverse(aptr_1,32);
 printf("The formated string is:\n");
 for(i=0;i<=31;i++)
  {
    printf("%d\t",*aptr_1);
    aptr_1++;
  }
 return 0;
}



  
 


