#include <stdio.h>
#include <stdint.h>
int8_t my_reverse(uint8_t * src, uint32_t length);
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
 k = my_reverse(aptr_1,32); // calling reverse
 printf("The formated string is:\n");
 for(i=0;i<=31;i++)    //printing out the entire string
  {
    printf("%d\t",*aptr_1);
    aptr_1++;
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

  
 


