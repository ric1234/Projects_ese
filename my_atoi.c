#include<stdio.h>
#include<stdint.h>

int32_t my_atoi(int8_t* str)
{   int32_t length;
    int8_t i;
    int32_t* base;
    int32_t a=0;
    base=&a;
    *base=(int32_t)*str;
    printf("%d \n",*base);
    for(i=0;i<length;i++)
    {
      *base=(int32_t)*str;
      printf("%d \n",*base);
      str++;
      base++;     
    }
    return *base;
}
