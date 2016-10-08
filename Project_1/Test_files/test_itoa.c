#include <stdio.h>
#include <stdint.h>
#include <string.h>
int8_t * my_itoa(int8_t * str, int32_t data, int32_t base);
void main()
{
 int8_t *string,a[10],i;
 string=a;
 int32_t data=245,base=2;
 string = my_itoa(string,data,base);
 for(i=0;i<8;i++)
 {
  printf("%d",*string);
  string++;
 }
 printf("\n");
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
