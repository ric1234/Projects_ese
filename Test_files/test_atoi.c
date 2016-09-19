#include <stdio.h>
#include <stdint.h>
int32_t my_atoi(int8_t * str);
void main()
{
 int8_t string[]="ABC", ;
 int32_t a;
 a= my_atoi(string);
 printf("a=%d\n",a);
}

int32_t my_atoi(int8_t * str)
{
  int32_t* whole;
  whole=(int32_t*)str;
  return *whole;
}
